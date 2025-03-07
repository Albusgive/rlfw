#include "CommunicationCenter.h"
#include "PCAN.hpp"

CommunicationCenter::CommunicationCenter(const std::string &node_name)
    : rclcpp::Node(node_name) {

  loadXML();
  initGamePad();
  motor_publisher = this->create_publisher<rlfw_msgs::msg::Motor>(
      "Com2Motor", rclcpp::QoS(2));

  sub_motor = this->create_subscription<rlfw_msgs::msg::MotorCtrl>(
      "MotorCtrl", 2,
      std::bind(&CommunicationCenter::sendMotor, this, std::placeholders::_1));

  // 寻找所有pcan 全部开启
  pcan = new PCAN();
  auto available = pcan->initAvailableCAN();
  std::cout << "available num:" << available.size() << std::endl;
}

CommunicationCenter::~CommunicationCenter() {}

void CommunicationCenter::timer_callback() {}

void CommunicationCenter::sendMotor(
    std::shared_ptr<rlfw_msgs::msg::MotorCtrl> msg) {}

void CommunicationCenter::loadXML(std::string path) {
  tinyxml2::XMLError error = doc.LoadFile(path.c_str());
  if (error != tinyxml2::XML_SUCCESS) {
    std::cerr << "加载失败: " << doc.ErrorStr() << std::endl;
    return;
  }
  tinyxml2::XMLElement *root = doc.RootElement();
  if (!root || strcmp(root->Name(), "rlfw") != 0) {
    std::cerr << "无效的根节点" << std::endl;
    return;
  }
  for (auto *motor = root->FirstChildElement("motor"); motor;
       motor = motor->NextSiblingElement("motor")) {
    const char *type = motor->Attribute("type");
    const char *joint = motor->Attribute("jointname");
    const char *invert = motor->Attribute("invert");

    if (type && joint && invert) {
      std::cout << "发现电机配置: "
                << "\n  类型: " << type << "\n  关节名: " << joint
                << "\n  反转: " << invert << std::endl;
    } else {
      std::cerr << "缺失必要属性" << std::endl;
    }
  }
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
