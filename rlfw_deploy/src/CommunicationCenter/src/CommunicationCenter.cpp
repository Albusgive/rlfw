#include "CommunicationCenter.hpp"
#include "BaseCAN.h"
#include "ComCfg.hpp"
#include "PCAN.hpp"
#include "STWMotor.h"
#include "SocketCAN.h"
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
  remote_qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
  // topic发送基础remote接收到的数据
  remote_publisher = this->create_publisher<rlfw_msgs::msg::Remote>(
      "rlfwRemoteBack", remote_qos);
  xml_decoder.load(robot_cfg_path);
  int his_size = 0;
  for (auto com : xml_decoder.coms) {
    for (auto m : com.xml_motors)
      his_size++;
  }
  rclcpp::QoS control_qos(his_size);
  control_qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
  control_qos.history(RMW_QOS_POLICY_HISTORY_KEEP_ALL);
  // topic发送基础can接收到的数据
  can_publisher = this->create_publisher<rlfw_msgs::msg::CanMsg>("rlfwCANBack",
                                                                 control_qos);
  // topic发送电机接收到的数据
  motor_publisher = this->create_publisher<rlfw_msgs::msg::Joint>(
      "rlfwJointBack", control_qos);
  // topic发送基础serial接收到的数据
  serial_publisher = this->create_publisher<rlfw_msgs::msg::SerialMsg>(
      "rlfwSerialBack", control_qos);
  // topic接收发送给电机
  sub_motor = this->create_subscription<rlfw_msgs::msg::JointCtrl>(
      "rlfwJointCtrl", control_qos,
      std::bind(&CommunicationCenter::sendMotor, this, _1));
  // topic接收发送给设备
  can_sub = this->create_subscription<rlfw_msgs::msg::CanMsg>(
      "rlfwCANSend", control_qos,
      std::bind(&CommunicationCenter::sendCAN, this, _1));

  // serial接收发送给设备
  serial_sub = this->create_subscription<rlfw_msgs::msg::SerialMsg>(
      "rlfwSerialSend", control_qos,
      std::bind(&CommunicationCenter::sendSerial, this, _1));
  // 服务器
  request = this->create_service<rlfw_msgs::srv::ComParameter>(
      "CommunicationCenterSrv",
      std::bind(&CommunicationCenter::handle_request, this, _1, _2));
  // 状态观测器 TODO
  if (xml_decoder.check()) {
    std::cout << "xml load check succeed" << std::endl;
    buildMap();
  }
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
                                  std::string &com_name, int decoder_idx) {
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
  for (auto deceder : com_moter_decoders[decoder_idx]) {
    motor_back = deceder->decode(msg);
    for (auto id : device_ids) {
      if (id == motor_back.id) {
        if (!motor_back.is_update)
          return;
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
        pub_motor_msg.set__vel(motor_back.vel);
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
      motor_msg.set__vel(motor->motorback.vel);
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
    motor->clearErr(); //stw需要单独清除错误
    motor->enableMotor(true,true);
  }break;
  case MotorCtrlType::DISABLE: {
    motor->enableMotor(false);
    break;
  }
  case MotorCtrlType::SETZERO: {
    motor->setZeroPoint();
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
      response->device_type.push_back(
          m.second->motor_type + "-----ctrl_type:" +
          std::string(magic_enum::enum_name(m.second->ctrl_type)));
    }
    // virtual motor
    for (auto m : virtual_motor_map) {
      response->device_name.push_back(m.first);
      response->device_type.push_back("virtual_motor");
    }
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

void CommunicationCenter::buildMap() {
  for (auto com : xml_decoder.coms) {
    switch (com.type) {
    case ComType::pcan: {
      auto pcan = std::make_shared<PCAN>();
      pcan->channel = PCAN1 + com.channel - 1;
      pcan->name = com.name;
      CANBps bps = xml_decoder.string2enum<CANBps>("Brt_" + com.brt);
      if (pcan->initPCAN( bps)) {
        // 增加电机
        addCanMotor(pcan, com);
      } else {
        std::cout << "init pcan false" << std::endl;
      }
      break;
    }
    case ComType::serial: {
      auto serial = std::make_shared<Serial>();
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
    case ComType::socketcan: {
      auto socketcan = std::make_shared<SocketCan>();
      socketcan->name = com.name;
      socketcan->channel = com.channel;
      if (socketcan->connect()) {
        addCanMotor(socketcan, com);
      } else {
        std::cout << "init socket false" << std::endl;
      }
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
    virtualmotor->motor_name = vm.joint_name;
    virtualmotor->default_ = vm.default_;
    virtualmotor->setTorqueRange(vm.torque_range[0], vm.torque_range[1]);
    virtualmotor->setVelRange(vm.vel_range[0], vm.vel_range[1]);
    virtualmotor->setPosRange(vm.pos_range[0], vm.pos_range[1]);
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

void CommunicationCenter::addCanMotor(std::shared_ptr<BaseCAN> can,
                                      ComCfg com_cfg) {
  std::vector<std::shared_ptr<BaseMotor>> motor_decoders;
  for (auto motor : com_cfg.xml_motors) {
    can->devive_ids.push_back(motor.id);
    switch (motor.type) {
    case Motortype::Mi: {
      auto mi = std::make_shared<MiMotor>();
      mi->can = can;
      initMotor(mi, motor);
      mi->ok_fix_parameter(motor.id);
      motor_map[motor.joint_name] = mi;
      motorID_map[motor.id] = mi;
      bool is = true;
      for (auto decode : motor_decoders) {
        if (decode->motor_type == mi->motor_type)
          is = false;
      }
      if (is)
        motor_decoders.push_back(mi);
    } break;
    case (Motortype::DM): {
      auto dm = std::make_shared<DMMotor>();
      dm->can = can;
      initMotor(dm, motor);
      motor_map[motor.joint_name] = dm;
      motorID_map[motor.id] = dm;
      bool is = true;
      for (auto decode : motor_decoders) {
        if (decode->motor_type == dm->motor_type)
          is = false;
      }
      if (is)
        motor_decoders.push_back(dm);
    } break;
    case (Motortype::STW): {
      auto stw = std::make_shared<STWMotor>();
      stw->can = can;
      initMotor(stw, motor);
      //清除数据
      motor_map[motor.joint_name] = stw;
      motorID_map[motor.id] = stw;
      bool is = true;
      for (auto decode : motor_decoders) {
        if (decode->motor_type == stw->motor_type)
          is = false;
      }
      if (is)
        motor_decoders.push_back(stw);
    } break;
    case (Motortype::RM):
      break;
    case (Motortype::ERR):
      break;
    case (Motortype::UNITREE):
      break;
    }
  }
  // usb2can独立线程接收数据并解码
  can->connectDecode(
      std::bind(&CommunicationCenter::fromCan, this, _1, _2, _3, _4));
  can->RunRecv();

  cans_map[com_cfg.name] = cans.size();
  cans.push_back(can);
  can->decoder_idx = com_moter_decoders.size();
  com_moter_decoders.push_back(motor_decoders);
  std::cout << "motor_decoders size:" << motor_decoders.size() << std::endl;
};

void CommunicationCenter::initMotor(std::shared_ptr<BaseMotor> _motor,
                                    XMLMotor xml_motor) {
  _motor->id = xml_motor.id;
  _motor->ctrl_type = xml_motor.ctrl_type;
  _motor->clearErr();
  _motor->setCtrlType();
  _motor->setPosKP(xml_motor.PosKP);
  _motor->setPosKP(xml_motor.PosKD);
  _motor->setVelKP(xml_motor.VelKP);
  _motor->setVelKI(xml_motor.VelKI);
  _motor->setTorqueKP(xml_motor.TorqueKP);
  _motor->setTorqueKI(xml_motor.TorqueKI);
  _motor->setSafeTorque(xml_motor.SafeTorque);
  _motor->setSafePos(xml_motor.SafePos);
  _motor->setSafeVel(xml_motor.SafeVel);
  _motor->invert = xml_motor.invert;
  _motor->motor_name = xml_motor.joint_name;
  _motor->default_ = xml_motor.default_;
  _motor->setTorqueRange(xml_motor.torque_range[0], xml_motor.torque_range[1]);
  _motor->setVelRange(xml_motor.vel_range[0], xml_motor.vel_range[1]);
  _motor->setPosRange(xml_motor.pos_range[0], xml_motor.pos_range[1]);
  _motor->enableMotor(true,true);
}
