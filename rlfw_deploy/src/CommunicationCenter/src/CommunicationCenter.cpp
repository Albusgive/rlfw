#include "CommunicationCenter.hpp"
#include "BaseCAN.h"
#include "ComCfg.hpp"
#include "DMMotor.h"
#include "MiMotor.h"
#include "Motor.hpp"
#include "PCAN.hpp"
#include "gamepad.h"
#include "magic_enum/magic_enum.hpp"
#include "serial.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <rclcpp/logging.hpp>
#include <rlfw_msgs/msg/detail/can_msg__struct.hpp>
#include <rlfw_msgs/msg/detail/joint__struct.hpp>
#include <rlfw_msgs/msg/detail/joint_ctrl__struct.hpp>
#include <rlfw_msgs/msg/detail/remote__struct.hpp>
#include <rlfw_msgs/msg/detail/serial_msg__struct.hpp>
#include <utility>
#include <vector>

CommunicationCenter::CommunicationCenter(const std::string &node_name)
    : rclcpp::Node(node_name) {

  rclcpp::QoS remote_qos(10);
  remote_qos.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);
  // topic发送基础remote接收到的数据
  remote_publisher = this->create_publisher<rlfw_msgs::msg::Remote>(
      "rlfwRemoteBack", remote_qos);

  xml_decoder.load(motor_cfg_path);
  if (xml_decoder.check()) {
    std::cout << "xml load check succeed" << std::endl;
    buildMap();
  }
  rclcpp::QoS control_qos(motorID_map.size());
  control_qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE)
      .durability_volatile();

  // topic发送基础can接收到的数据
  can_publisher = this->create_publisher<rlfw_msgs::msg::CanMsg>("rlfwCANBack",
                                                                 control_qos);
  // topic发送电机接收到的数据
  motor_publisher = this->create_publisher<rlfw_msgs::msg::Joint>(
      "rlfwJointBack", control_qos);
  // topic接收发送给电机
  sub_motor = this->create_subscription<rlfw_msgs::msg::JointCtrl>(
      "rlfwJointCtrl", control_qos,
      std::bind(&CommunicationCenter::sendMotor, this, _1));
  // topic接收发送给设备
  can_sub = this->create_subscription<rlfw_msgs::msg::CanMsg>(
      "rlfwCANSend", control_qos,
      std::bind(&CommunicationCenter::sendCAN, this, _1));
  // topic发送基础serial接收到的数据
  serial_publisher = this->create_publisher<rlfw_msgs::msg::SerialMsg>(
      "rlfwSerialBack", control_qos);
  // serial接收发送给设备
  serial_sub = this->create_subscription<rlfw_msgs::msg::SerialMsg>(
      "rlfwSerialSend", control_qos,
      std::bind(&CommunicationCenter::sendSerial, this, _1));
  // 服务器
  request = this->create_service<rlfw_msgs::srv::ComParameter>(
      "CommunicationCenterSrv",
      std::bind(&CommunicationCenter::handle_request, this, _1, _2));
  // 状态观测器 TODO

  RunRecv();
}

CommunicationCenter::~CommunicationCenter() {
  // 电机全部失能
  for (auto m : motor_map) {
    m.second->enableMotor(false);
  }
  // 关闭全部串口
  for (auto s : serials) {
    s->Close();
  }
}

void CommunicationCenter::fromCan(CANMSG &msg, std::vector<int> &device_ids,
                                  std::string &com_name) {
  std::lock_guard<std::mutex> lock(com_mutex);
  auto stamp = this->now();
  rlfw_msgs::msg::CanMsg pub_can_msg;
  pub_can_msg.comname.set__frame_id(com_name);
  pub_can_msg.comname.set__stamp(stamp);
  pub_can_msg.id = msg.ID;
  pub_can_msg.len = msg.LEN;
  for (int i = 0; i < 8; i++) {
    pub_can_msg.data.push_back(msg.DATA[i]);
  }
  can_publisher->publish(pub_can_msg);
  // 电机（设备）解码器
  MotorBack motor_back;
  for (auto deceder : moter_decoders) {
    motor_back = deceder->decode(msg);
    for (auto id : device_ids) {
      if (id == motor_back.id) {
        rlfw_msgs::msg::Joint pub_motor_msg;
        pub_motor_msg.set__joint_id(motor_back.id);
        rlfw_msgs::msg::Joint::_jointname_type jointname;
        // 找到电机
        auto motor = motorID_map[motor_back.id];
        // 电机是否取反
        if (motor->invert)
          motor_back.invertMotor(); // 取反
        motor->motorback = motor_back;
        jointname.stamp = stamp;
        jointname.frame_id = motor->motor_name;
        pub_motor_msg.set__jointname(jointname);
        pub_motor_msg.set__pos(motor_back.angle);
        pub_motor_msg.set__vel(motor_back.ang_vel);
        pub_motor_msg.set__current(motor_back.current);
        pub_motor_msg.set__number_laps(motor_back.number_laps);
        pub_motor_msg.set__temperature(motor_back.temperature);
        pub_motor_msg.set__torque(motor_back.torque);
        pub_motor_msg.set__state(static_cast<int>(motor_back.warning));
        motor_publisher->publish(pub_motor_msg);
        return;
      }
    }
  }
}

void CommunicationCenter::fromSerial(std::vector<uint8_t> &msg,
                                     std::string com_name) {
  std::lock_guard<std::mutex> lock(com_mutex);
  rlfw_msgs::msg::SerialMsg pub_serial_msg;
  auto stamp = this->now();
  pub_serial_msg.comname.set__frame_id(com_name);
  pub_serial_msg.comname.set__stamp(stamp);
  pub_serial_msg.data = msg;
  serial_publisher->publish(pub_serial_msg);
}

void CommunicationCenter::fromRemote(std::vector<std::string> &key,
                                     std::vector<float> &value) {
  std::lock_guard<std::mutex> lock(com_mutex);
  rlfw_msgs::msg::Remote msg;
  msg.set__key(key);
  msg.set__value(value);
  remote_publisher->publish(msg);
}

void CommunicationCenter::RunRecv() {
  int cnt = 0;
  for (auto it : cans) {
    if (!it->only_thread) {
      cnt += 1;
    }
  }
  if (cnt == 0)
    return;
  std::thread ThRecv = std::thread{[&]() {
    while (rclcpp::ok()) {
      // can设备
      for (auto it : cans) {
        auto [is, can_msg] = it->read(it->channel);
        if (is)
          fromCan(can_msg, it->devive_ids, it->name);
      }
      // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }};
  ThRecv.detach();
}

void CommunicationCenter::sendMotor(
    std::shared_ptr<rlfw_msgs::msg::JointCtrl> msg) {
  auto joint_name = msg->jointname.frame_id;
  // 从物理电机中寻找
  auto motor = motor_safe_get(joint_name);
  if (motor == nullptr) {
    motor = virtual_motor_safe_get(joint_name);
    if (motor == nullptr) {
      RCLCPP_WARN(this->get_logger(), "no mount motor: %s", joint_name.c_str());
      return;
    } else {
      // 原来是虚拟电机啊
      rlfw_msgs::msg::Joint motor_msg;
      motor_msg.jointname.set__frame_id(motor->motor_name);
      motor_msg.jointname.set__stamp(this->now());
      motor_msg.set__pos(motor->motorback.angle);
      motor_msg.set__vel(motor->motorback.ang_vel);
      motor_msg.set__current(0);
      motor_msg.set__torque(0);
      motor_msg.set__temperature(0);
      motor_msg.other = motor->other();
      motor_publisher->publish(motor_msg);
    }
  }
  // 判断控制类型
  auto ctrl_type = xml_decoder.string2enum<MotorCtrlType>(msg->ctrl_type);
  switch (ctrl_type) {
  case MotorCtrlType::MIT: {
    motor->locomotion(msg->torque, msg->pos, msg->vel, msg->kp, msg->kd);
    break;
  }
  case MotorCtrlType::POS: {
    motor->ctrl_pos(msg->pos);
    break;
  }
  case MotorCtrlType::VEL: {
    motor->ctrl_vel(msg->vel);
    break;
  }
  case MotorCtrlType::TORQUE: {
    motor->ctrl_torque(msg->torque);
    break;
  }
  case MotorCtrlType::POS_VEL: {
    motor->ctrl_pos_vel(msg->pos, msg->vel);
    break;
  }
  case MotorCtrlType::ENABLE: {
    if (msg->kd == 0)
      motor->enableMotor(false);
    else
      motor->enableMotor(true);
    break;
  }
  case MotorCtrlType::ERR: {
    std::cout << "MotorCtrlType is ERR:\n"
              << "please use: MIT, POS, VEL, TORQUE, POS_VEL, ENABLE"
              << std::endl;
    break;
  }
  }
}

std::shared_ptr<BaseMotor>
CommunicationCenter::motor_safe_get(const std::string &name) {
  std::unique_lock<std::mutex> lock(com_mutex);
  auto it = motor_map.find(name);
  lock.unlock();
  if (it == motor_map.end()) {
    return nullptr;
  }
  return it->second;
}

std::shared_ptr<BaseMotor>
CommunicationCenter::virtual_motor_safe_get(const std::string &name) {
  std::unique_lock<std::mutex> lock(com_mutex);
  auto it = virtual_motor_map.find(name);
  lock.unlock();
  if (it == virtual_motor_map.end()) {
    return nullptr;
  }
  return it->second;
}

void CommunicationCenter::sendCAN(std::shared_ptr<rlfw_msgs::msg::CanMsg> msg) {
  auto can_safe_get = [this](const std::string &name) -> int {
    std::unique_lock<std::mutex> lock(com_mutex);
    auto it = cans_map.find(name);
    lock.unlock();
    if (it == cans_map.end()) {
      RCLCPP_WARN(this->get_logger(), "no mount CAN device: %s", name.c_str());
      return -1;
    }
    return it->second;
  };
  int idx = can_safe_get(msg->comname.frame_id);
  if (idx == -1) {
    return;
  } else {
    CANMSG send_msg;
    send_msg.ID = msg->id;
    send_msg.LEN = msg->len;
    send_msg.MSGTYPE = BaseCAN::getCANtype(msg->msgtype);
    for (int i = 0; i < (int)msg->data.size(); i++) {
      send_msg.DATA[i] = msg->data[i];
    }
    if (!cans[idx]->send(&send_msg)) {
      RCLCPP_WARN(this->get_logger(), "can send err:%s",
                  serials[idx]->name.c_str());
      rlfw_msgs::msg::CanMsg back;
      back.comname.set__frame_id(msg->comname.frame_id + "  err");
      can_publisher->publish(back);
    }
  }
}

void CommunicationCenter::sendSerial(
    std::shared_ptr<rlfw_msgs::msg::SerialMsg> msg) {
  auto serial_safe_get = [this](const std::string &name) -> int {
    std::unique_lock<std::mutex> lock(com_mutex);
    auto it = serials_map.find(name);
    lock.unlock();
    if (it == serials_map.end()) {
      RCLCPP_WARN(this->get_logger(), "no mount Serial device: %s",
                  name.c_str());
      return -1;
    }
    return it->second;
  };
  int idx = serial_safe_get(msg->comname.frame_id);
  if (idx == -1) {
    return;
  } else {
    int is = serials[idx]->Send(msg->data);
    if (is == -1) {
      RCLCPP_WARN(this->get_logger(), "serials send err:%s",
                  serials[idx]->name.c_str());
      rlfw_msgs::msg::SerialMsg back;
      back.comname.set__frame_id(msg->comname.frame_id + "  err");
    }
  }
  return;
}

void CommunicationCenter::handle_request(
    const std::shared_ptr<rlfw_msgs::srv::ComParameter::Request> request,
    std::shared_ptr<rlfw_msgs::srv::ComParameter::Response> response) {
  // std::cout << request->request_communication_center_parameter << std::endl;
  auto type = xml_decoder.string2enum<ComeCenterParamType>(
      request->request_communication_center_parameter);
  switch (type) {
  case ComeCenterParamType::MountCom: {
    for (auto com : xml_decoder.coms) {
      response->device_name.push_back(com.name);
      response->device_type.push_back(
          std::string(magic_enum::enum_name(com.type)));
    }
    break;
  }
  case ComeCenterParamType::MountMotor: {
    for (auto m : motor_map) {
      response->device_name.push_back(m.first);
      response->device_type.push_back(m.second->motor_type);
    }
    // serial motor
    break;
  }
  case ComeCenterParamType::MountRmote: {
    // gamepad
    for (auto remote : xml_decoder.remotes) {
      response->device_name.push_back(remote.name);
      response->device_type.push_back(
          std::string(magic_enum::enum_name(remote.type)));
    }
    // other
    break;
  }
  case ComeCenterParamType::ERR: {
    response->device_name.push_back("What are you looking for?");
    response->device_type.push_back("ERR");
    break;
  }
  }
}

void CommunicationCenter::registeredMotorDecoder(Motortype motor_type) {
  for (auto type : registered_motor_types) {
    if (motor_type == type)
      return;
  }
  registered_motor_types.push_back(motor_type);
  switch (motor_type) {
  case Motortype::Mi: {
    auto mi = std::make_shared<MiMotor>();
    moter_decoders.push_back(mi);
    break;
  }
  case Motortype::DM: {
    auto dm = std::make_shared<DMMotor>();
    moter_decoders.push_back(dm);
    break;
  }
  case Motortype::RM: {
    // auto rm = std::make_shared<RMMotor>();
    // moter_decoders.push_back(rm);
    break;
  }
  case Motortype::ERR: {
    std::cout << "can't registered ERR" << std::endl;
    break;
  }
  case Motortype::UNITREE: {
    break;
  }
  }
}

void CommunicationCenter::buildMap() {
  for (auto com : xml_decoder.coms) {
    switch (com.type) {
    case ComType::pcan: {
      auto pcan = std::make_shared<PCAN>();
      pcan->channel = PCAN1 + com.channel - 1;
      pcan->name = com.name;
      if (pcan->initPCAN(pcan->channel, BAUD_1MBPS)) {
        // 增加电机
        for (auto motor : com.xml_motors) {
          registeredMotorDecoder(motor.type);
          pcan->devive_ids.push_back(motor.id);
          if (motor.type == Motortype::Mi) {
            auto mi = std::make_shared<MiMotor>();
            mi->can = pcan;
            mi->id = motor.id;
            mi->invert = motor.invert;
            mi->motor_type = "Mi";
            mi->motor_name = motor.joint_name;
            initMotor(mi, motor);
            mi->ok_fix_parameter(motor.id);
            motor_map[motor.joint_name] = mi;
            motorID_map[motor.id] = mi;
          } else if (motor.type == Motortype::DM) {
            auto dm = std::make_shared<DMMotor>();
            dm->can = pcan;
            dm->id = motor.id;
            dm->invert = motor.invert;
            dm->motor_type = "DM";
            dm->motor_name = motor.joint_name;
            initMotor(dm, motor);
            motor_map[motor.joint_name] = dm;
            motorID_map[motor.id] = dm;
          }
        }
        if (com.only_thred) {
          pcan->connectDecode(
              std::bind(&CommunicationCenter::fromCan, this, _1, _2, _3));
          pcan->RunRecv();
        }
        cans_map[com.name] = cans.size();
        cans.push_back(pcan);
      } else {
        std::cout << "init pcan false" << std::endl;
      }
      break;
    }
    case ComType::serial: {
      auto serial = std::make_shared<Serial>();
      serial->only_thread = com.only_thred;
      serial->name = com.name;
      bool is = serial->OpenSerial(com.port, com.bps, com.datasize, com.parity,
                                   com.stopbit);
      if (!is)
        RCLCPP_ERROR(this->get_logger(), "serials open err %s ,port%s",
                     com.name.c_str(), com.port.c_str());
      serial->connectDecode(
          std::bind(&CommunicationCenter::fromSerial, this, _1, _2));
      serial->RunRecv();
      serials_map[com.name] = serials.size();
      serials.push_back(serial);
      break;
    }
    case ComType::canable: {
      std::cout << "Canable type not implemented yet" << std::endl;
      break;
    }
    case ComType::ERR: {
      std::cout << "ERR" << std::endl;
      break;
    }
    }
  }
  for (auto remote : xml_decoder.remotes) {
    switch (remote.type) {
    case RemoteType::gamepad: {
      auto gamepad = std::make_shared<GamePad>();
      gamepad->channel = remote.channel;
      gamepad->name = remote.name;
      // if (remote.key.size() == gamepad->key.size())
      //   gamepad->key = remote.key;
      gamepad->showGamePads();
      if (gamepad->GamePadpads.empty()) {
        RCLCPP_ERROR(this->get_logger(), "no gamepad ,name:%s ,channel:%d",
                     gamepad->name.c_str(), gamepad->channel);
      } else if (gamepad->channel <
                 static_cast<int>(gamepad->GamePadpads.size())) {
        gamepad->bindKeyValue(
            std::bind(&CommunicationCenter::fromRemote, this, _1, _2));
        gamepad->openRemote();
        remotes.push_back(gamepad);
      }
      break;
    }
    case RemoteType::keyboard: {
      break;
    }
    case RemoteType::custom: {
      break;
    }
    case RemoteType::ERR: {
      break;
    }
    }
  }
  // 虚拟电机
  std::cout << "add virtualmotor: ";
  for (auto vm : xml_decoder.virtualmotors) {
    std::shared_ptr<VirtualMotor> virtualmotor =
        std::make_shared<VirtualMotor>();
    virtualmotor->motor1 = motor_safe_get(vm.motor1);
    virtualmotor->motor2 = motor_safe_get(vm.motor2);
    virtualmotor->terminal = vm.terminal;
    virtualmotor->type = vm.type;
    int n = vm.ln.size() >= 5 ? 5 : vm.ln.size();
    for (int i = 0; i < n; i++) {
      virtualmotor->l[i] = vm.ln[i];
    }
    virtual_motor_map[vm.joint_name] = virtualmotor;
    std::cout << vm.joint_name << " ";
  }
  std::cout << std::endl;

  std::cout << "succeed mount:" << std::endl;
  std::cout << "  can device: ";
  for (auto com : cans) {
    std::cout << com->name << " ";
  }
  std::cout << std::endl;
  std::cout << "  serial device: ";
  for (auto com : serials) {
    std::cout << com->name << " ";
  }
  std::cout << std::endl;
  std::cout << "  remote device: ";
  for (auto remote : remotes) {
    std::cout << remote->name << " ";
  }
  std::cout << std::endl;
}

void CommunicationCenter::initMotor(std::shared_ptr<BaseMotor> _motor,
                                    XMLMotor xml_motor) {
  _motor->enableMotor(true);
  _motor->setPosKP(xml_motor.PosKP);
  _motor->setPosKP(xml_motor.PosKD);
  _motor->setVelKP(xml_motor.VelKP);
  _motor->setVelKI(xml_motor.VelKI);
  _motor->setTorqueKP(xml_motor.TorqueKP);
  _motor->setTorqueKI(xml_motor.TorqueKI);
  _motor->setSafeTorque(xml_motor.SafeTorque);
  _motor->setSafePos(xml_motor.SafePos);
  _motor->setSafeVel(xml_motor.SafeVel);
}
