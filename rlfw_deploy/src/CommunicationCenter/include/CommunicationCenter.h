#pragma once
#include "BaseCAN.h"
#include "Motor.hpp"
#include "PCAN.hpp"
#include "XMLDecoder.hpp"
#include "gamepad.h"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rlfw_msgs/msg/motor.hpp"
#include "rlfw_msgs/msg/motor_ctrl.hpp"
#include "serial.hpp"
#include <atomic>
#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>

class CommunicationCenter : public rclcpp::Node {
public:
  CommunicationCenter(const std::string &node_name);
  ~CommunicationCenter();

  // 电机反馈
  rclcpp::Publisher<rlfw_msgs::msg::Motor>::SharedPtr motor_publisher;
  void fromCanMotor(CANMSG msg,std::vector<int> motor_ids);
  void fromSerialMotor(){};
  //对于没有独立线程的com统一线程读取
  void RunRecv();

  // 接受电机控制
  rclcpp::Subscription<rlfw_msgs::msg::MotorCtrl>::SharedPtr sub_motor;
  void sendMotor(std::shared_ptr<rlfw_msgs::msg::MotorCtrl> msg);

private:
  std::string motor_cfg_path =
      "./install/" + std::string(PROJECT_NAME) + "/share/motor_cfg.xml";
  //加载配置
  XMLDecoder xml_decoder;
  //注册电机解码器
  std::vector<std::shared_ptr<CANMotor>> can_moter_decoders;
  std::vector<Motortype> registered_can_types;
  std::unordered_map<int,std::string> id2string;
  void registeredCANMotorDecoder(Motortype motor_type);
  //字符串映射
  std::unordered_map<std::string, std::shared_ptr<CANMotor>> can_motor_map;
  std::vector<std::shared_ptr<BaseCAN>> cans;
  std::unordered_map<std::string, int> cans_map;
  std::vector<std::shared_ptr<Serial>> serials;
  std::unordered_map<std::string, int> serials_map;
  void buildMap();
  void initCanMotor(std::shared_ptr<CANMotor> can_motor,XMLMotor xml_motor);
  //对不同通讯子线程处理CommunicationCenter的函数使用 接受电机消息，接受串口消息
  std::mutex com_mutex; 

  GamePad *gamepad;
  void initGamePad();
  void timer_callback();
  rclcpp::TimerBase::SharedPtr timer;
};
