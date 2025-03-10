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
#include <rlfw_msgs/msg/detail/remote__struct.hpp>
#include <rlfw_msgs/msg/detail/serial_msg__struct.hpp>
#include <rlfw_msgs/srv/detail/rl_srv__struct.hpp>
#include <utility>
#include <vector>

CommunicationCenter::CommunicationCenter(const std::string &node_name)
    : rclcpp::Node(node_name) {
  // topic发送基础can接收到的数据
  can_publisher = this->create_publisher<rlfw_msgs::msg::CanMsg>(
      "rlfwCANBack", rclcpp::QoS(2));
  // topic发送can电机接收到的数据
  motor_publisher = this->create_publisher<rlfw_msgs::msg::Motor>(
      "rlfwMotorBack", rclcpp::QoS(2));
  // topic接收发送给电机
  sub_motor = this->create_subscription<rlfw_msgs::msg::MotorCtrl>(
      "rlfwMotorCtrl", rclcpp::QoS(2),
      std::bind(&CommunicationCenter::sendMotor, this, _1));
  // topic接收发送给设备
  can_sub = this->create_subscription<rlfw_msgs::msg::CanMsg>(
      "rlfwCANSend", rclcpp::QoS(2),
      std::bind(&CommunicationCenter::sendCAN, this, _1));
  // topic发送基础serial接收到的数据
  serial_publisher = this->create_publisher<rlfw_msgs::msg::SerialMsg>(
      "rlfwSerialBack", rclcpp::QoS(2));
  // serial接收发送给设备
  serial_sub = this->create_subscription<rlfw_msgs::msg::SerialMsg>(
      "rlfwSerialSend", rclcpp::QoS(2),
      std::bind(&CommunicationCenter::sendSerial, this, _1));
  // topic发送基础remote接收到的数据
  remote_publisher = this->create_publisher<rlfw_msgs::msg::Remote>(
      "rlfwRemoteBack", rclcpp::QoS(2));
  // 服务器
  request = this->create_service<rlfw_msgs::srv::ComParameter>(
      "CommunicationCenterSrv",
      std::bind(&CommunicationCenter::handle_request, this, _1, _2));

  xml_decoder.load(motor_cfg_path);
  if (xml_decoder.check())
    std::cout << "xml load check succeed" << std::endl;
  buildMap();
  RunRecv();

  // can_motor_map["left_wheel_joint"]->enableMotor(true);
  // can_motor_map["left_calf_joint"]->enableMotor(true);
  // // can_motor_map["left_wheel_joint"]->ctrl_vel(1.0);
  // can_motor_map["left_wheel_joint"]->locomotion(0.0, 0.0, 1.0, 0.0, 0.3);
  // can_motor_map["left_calf_joint"]->locomotion(0.0, 0.0, 1.0, 0.0, 0.3);
  // while (rclcpp::ok()) {
  //   std::this_thread::sleep_for(std::chrono::microseconds(500));
  // }
  // std::this_thread::sleep_for(std::chrono::seconds(5));
  // can_motor_map["left_wheel_joint"]->enableMotor(false);
  // can_motor_map["left_calf_joint"]->enableMotor(false);

  // initGamePad();

  // // 寻找所有pcan 全部开启
  // pcan = new PCAN();
  // auto available = pcan->initAvailableCAN();
  // std::cout << "available num:" << available.size() << std::endl;
}

CommunicationCenter::~CommunicationCenter() {
  // 电机全部失能
  for (auto m : can_motor_map) {
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
  for (auto deceder : can_moter_decoders) {
    motor_back = deceder->decode(msg);
    for (auto id : device_ids) {
      if (id == motor_back.id) {
        rlfw_msgs::msg::Motor pub_motor_msg;
        pub_motor_msg.set__motor_id(motor_back.id);
        rlfw_msgs::msg::Motor::_jointname_type jointname;
        jointname.frame_id = id2string[motor_back.id];
        jointname.stamp = stamp;
        pub_motor_msg.set__jointname(jointname);
        pub_motor_msg.set__angle(motor_back.angle);
        pub_motor_msg.set__ang_vel(motor_back.ang_vel);
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
                                     std::vector<float> value) {
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

void CommunicationCenter::timer_callback() {}

void CommunicationCenter::sendMotor(
    std::shared_ptr<rlfw_msgs::msg::MotorCtrl> msg) {
  auto joint_name = msg->jointname.frame_id;
  auto can_motor_safe_get =
      [this](const std::string &name) -> std::shared_ptr<CANMotor> {
    std::unique_lock<std::mutex> lock(com_mutex);
    auto it = can_motor_map.find(name);
    lock.unlock();
    if (it == can_motor_map.end()) {
      RCLCPP_WARN(this->get_logger(), "no mount CAN motor: %s", name.c_str());
      return nullptr;
    }
    return it->second;
  };
  // 判断控制类型
  auto motor = can_motor_safe_get(joint_name);
  auto ctrl_type = xml_decoder.string2enum<MotorCtrlType>(msg->ctrl_type);
  if (motor == nullptr)
    return;
  switch (ctrl_type) {
  case MotorCtrlType::MIT: {
    motor->locomotion(msg->torque, msg->angle, msg->ang_vel, msg->kp, msg->kd);
    break;
  }
  case MotorCtrlType::POS: {
    motor->ctrl_pos(msg->angle);
    break;
  }
  case MotorCtrlType::VEL: {
    motor->ctrl_vel(msg->ang_vel);
    break;
  }
  case MotorCtrlType::TORQUE: {
    motor->ctrl_torque(msg->torque);
    break;
  }
  case MotorCtrlType::POS_VEL: {
    motor->ctrl_pos_vel(msg->angle, msg->ang_vel);
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
    send_msg.MSGTYPE = msg->msgtype;
    for (int i = 0; i < (int)msg->data.size(); i++) {
      send_msg.DATA[i] = msg->data[i];
    }
    cans[idx]->send(&send_msg);
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
    if (is == -1)
      RCLCPP_WARN(this->get_logger(), "serials send err:%s",
                  serials[idx]->name.c_str());
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
    for (auto m : can_motor_map)
      response->device_name.push_back(m.first);
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

void CommunicationCenter::registeredCANMotorDecoder(Motortype motor_type) {
  for (auto type : registered_can_types) {
    if (motor_type == type)
      return;
  }
  switch (motor_type) {
  case Motortype::Mi: {
    auto mi = std::make_shared<MiMotor>();
    can_moter_decoders.push_back(mi);
    break;
  }
  case Motortype::DM: {
    auto dm = std::make_shared<DMMotor>();
    can_moter_decoders.push_back(dm);
    break;
  }
  case Motortype::RM: {
    // auto rm = std::make_shared<RMMotor>();
    // can_moter_decoders.push_back(rm);
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
          registeredCANMotorDecoder(motor.type);
          id2string[motor.id] = motor.joint_name;
          pcan->devive_ids.push_back(motor.id);
          if (motor.type == Motortype::Mi) {
            auto mi = std::make_shared<MiMotor>();
            mi->can = pcan;
            mi->id = motor.id;
            initCanMotor(mi, motor);
            mi->ok_fix_parameter(motor.id);
            can_motor_map[motor.joint_name] = mi;
          } else if (motor.type == Motortype::DM) {
            auto dm = std::make_shared<DMMotor>();
            dm->can = pcan;
            dm->id = motor.id;
            initCanMotor(dm, motor);
            can_motor_map[motor.joint_name] = dm;
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
  std::cout << "succeed mount:" << std::endl;
  std::cout << "can device: ";
  for (auto com : cans) {
    std::cout << com->name << " ";
  }
  std::cout << std::endl;
  std::cout << "serial device: ";
  for (auto com : serials) {
    std::cout << com->name << " ";
  }
  std::cout << std::endl;
  std::cout << "remote device: ";
  for (auto remote : remotes) {
    std::cout << remote->name << " ";
  }
  std::cout << std::endl;
}

void CommunicationCenter::initCanMotor(std::shared_ptr<CANMotor> can_motor,
                                       XMLMotor xml_motor) {
  can_motor->enableMotor(true);
  can_motor->setPosKP(xml_motor.PosKP);
  can_motor->setPosKP(xml_motor.PosKD);
  can_motor->setVelKP(xml_motor.VelKP);
  can_motor->setVelKI(xml_motor.VelKI);
  can_motor->setTorqueKP(xml_motor.TorqueKP);
  can_motor->setTorqueKI(xml_motor.TorqueKI);
  can_motor->setSafeTorque(xml_motor.SafeTorque);
  can_motor->setSafePos(xml_motor.SafePos);
  can_motor->setSafeVel(xml_motor.SafeVel);
}

void CommunicationCenter::initGamePad() {
  //     gamepad = new GamePad();
  //     gamepad->showGamePads();
  //     if (gamepad->GamePadpads.empty())
  //         return;
  //     publisher_twist =
  //     this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  //     gimbal_remote_publisher =
  //     this->create_publisher<hongying_ctrl_msg::msg::GimbalRemote>("gimble_cmdv",
  //     2);
  //     // 键位切换云台，操作按键绑定
  //     gamepad->bindGamePadValues([=](GamePadValues map)
  //                                {
  //         geometry_msgs::msg::Twist msg;
  //         msg.linear.x=(double)-map.ly/32767*10;
  //         msg.linear.y=(double)-map.lx/32767*10;
  //         msg.angular.z=(double)(map.rt-map.lt)/65534*8;
  //         std::cout<<"tr:"<<map.rt<<std::endl;
  //         std::cout<<"z:"<<msg.angular.z<<std::endl;

  //         hongying_ctrl_msg::msg::GimbalRemote gimbal_remote_msg;
  //         gimbal_remote_msg.header.frame_id = "left_gimbal_cmd";

  //         if(map.a)
  //         {
  //             std::cout<<"a"<<std::endl;
  //             //gimbal_remote_msg.fire_rate=1.0;
  //             //msg.angular.z=3;
  //         }
  //         if(map.x)
  //         {
  //             std::cout<<"x"<<std::endl;
  //             gimbal_remote_msg.fire_rate=-1;
  //             //msg.angular.z=0;
  //         }
  //         //         if(map.rt>0)
  //         // {
  //         //     gimbal_remote_msg.fire_rate=1.0;
  //         //     std::cout<<"fire"<<std::endl;
  //         // }
  //         gimbal_remote_msg.yaw_speed=-(double)map.rx/32767*50;
  //         gimbal_remote_msg.pitch_speed=-(double)map.ry/32767*50;
  //         gimbal_remote_publisher->publish(gimbal_remote_msg);
  //         publisher_twist->publish(msg);

  //         if(map.b)
  //         {
  //             pcan->~PCAN();
  //         }
  //         });
  //     int is;
  //     std::string opid = gamepad->GamePadpads.begin()->first;
  //     std::cout << "first gamepad id is " << opid << std::endl;
  //     if (gamepad->GamePadpads.size() > 1)
  //     {
  //         std::cout << "more than one gamepad" << std::endl;
  //         while (rclcpp::ok())
  //         {
  //             std::cout << "please input the gamepad id" << std::endl;
  //             std::cin >> opid;
  //             is = gamepad->openGamePad(opid);
  //             if (is >= 0)
  //             {
  //                 break;
  //             }
  //         }
  //     }
  //     else
  //     {
  //         is = gamepad->openGamePad(opid);
  //         if (is < 0)
  //         {
  //             std::cout << "open gamepad fail" << std::endl;
  //             return;
  //         }
  //     }
  //     gamepad->readGamePad();
}
