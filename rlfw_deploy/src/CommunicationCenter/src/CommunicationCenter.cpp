#include "CommunicationCenter.h"
#include "BaseCAN.h"
#include "ComCfg.hpp"
#include "DMMotor.h"
#include "MiMotor.h"
#include "Motor.hpp"
#include "PCAN.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <ratio>
#include <vector>

CommunicationCenter::CommunicationCenter(const std::string &node_name)
    : rclcpp::Node(node_name) {
  motor_publisher = this->create_publisher<rlfw_msgs::msg::Motor>(
      "Com2Motor", rclcpp::QoS(2));
  xml_decoder.load(motor_cfg_path);
  if (xml_decoder.check())
    std::cout << "xml load check succeed" << std::endl;
  buildMap();
  RunRecv();

  can_motor_map["left_wheel_joint"]->enableMotor(true);
  can_motor_map["left_calf_joint"]->enableMotor(true);
  // can_motor_map["left_wheel_joint"]->ctrl_vel(1.0);
  can_motor_map["left_wheel_joint"]->locomotion(0.0, 0.0, 1.0, 0.0, 0.3);
  can_motor_map["left_calf_joint"]->locomotion(0.0, 0.0, 1.0, 0.0, 0.3);
  while (rclcpp::ok()) {
    can_motor_map["left_wheel_joint"]->locomotion(0.0, 0.0, 2.0, 0.0, 0.3);
    can_motor_map["left_calf_joint"]->locomotion(0.0, 0.0, 2.0, 0.0, 0.3);
    std::this_thread::sleep_for(std::chrono::microseconds(500));
  }
  std::this_thread::sleep_for(std::chrono::seconds(2));
  can_motor_map["left_wheel_joint"]->enableMotor(false);
  can_motor_map["left_calf_joint"]->enableMotor(false);

  // initGamePad();

  // sub_motor = this->create_subscription<rlfw_msgs::msg::MotorCtrl>(
  //     "MotorCtrl", 2,
  //     std::bind(&CommunicationCenter::sendMotor, this,
  //     std::placeholders::_1));

  // // 寻找所有pcan 全部开启
  // pcan = new PCAN();
  // auto available = pcan->initAvailableCAN();
  // std::cout << "available num:" << available.size() << std::endl;
}

CommunicationCenter::~CommunicationCenter() {}

void CommunicationCenter::fromCanMotor(CANMSG msg, std::vector<int> motor_ids) {
  std::lock_guard<std::mutex> lock(com_mutex);
  // 解码器
  MotorBack motor_back;
  for (auto deceder : can_moter_decoders) {
    motor_back = deceder->decode(msg);
    for (auto id : motor_ids) {
      if (id == motor_back.id) {
        rlfw_msgs::msg::Motor pub_msg;
        pub_msg.set__motor_id(motor_back.id);
        rlfw_msgs::msg::Motor::_jointname_type jointname;
        jointname.frame_id = id2string[motor_back.id];
        jointname.stamp = this->now();
        pub_msg.set__jointname(jointname);
        pub_msg.set__angle(motor_back.angle);
        pub_msg.set__ang_vel(motor_back.ang_vel);
        pub_msg.set__current(motor_back.current);
        pub_msg.set__number_laps(motor_back.number_laps);
        pub_msg.set__temperature(motor_back.temperature);
        pub_msg.set__torque(motor_back.torque);
        pub_msg.set__state(static_cast<int>(motor_back.warning));
        motor_publisher->publish(pub_msg);
        return;
      }
    }
  }
}

void CommunicationCenter::RunRecv() {
  int cnt = 0;
  for (auto it : cans) {
    if (!it->only_thread) {
      cnt += 1;
    }
  }
  for (auto it : serials) {
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
          fromCanMotor(can_msg, it->devive_ids);
      }
      for (auto it : serials) {
        // TODO
      }
      // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }};
  ThRecv.detach();
}

void CommunicationCenter::timer_callback() {}

void CommunicationCenter::sendMotor(
    std::shared_ptr<rlfw_msgs::msg::MotorCtrl> msg) {}

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
          pcan->connectDecode(std::bind(&CommunicationCenter::fromCanMotor,
                                        this, std::placeholders::_1,
                                        std::placeholders::_2));
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
      std::cout << "Serial type not implemented yet" << std::endl;
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
}

void CommunicationCenter::initCanMotor(std::shared_ptr<CANMotor> can_motor,
                                       XMLMotor xml_motor) {
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
