#pragma once
#include "MotorDriver.h"
#include "PCAN.hpp"
#include "gamepad.h"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rlfw_msgs/msg/motor.hpp"
#include "rlfw_msgs/msg/motor_cfg.hpp"
#include "rlfw_msgs/msg/motor_ctrl.hpp"
#include "serial.hpp"
#include "tinyxml2.h"
#include <atomic>
#include <string>



class Communication {
public:
  std::string name;

};

class CommunicationCenter : public rclcpp::Node {
public:
  CommunicationCenter(const std::string &node_name);
  ~CommunicationCenter();

  PCAN *pcan;
  USBHubPort<TPCANHandle> hub_port;
  PChannel pc;
  bool can1_flag = false, can2_flag = false, can3_flag = false,
       can4_flag = false;

  // 电机反馈
  rclcpp::Publisher<rlfw_msgs::msg::Motor>::SharedPtr motor_publisher;

  // 接受电机参数配置
  rclcpp::Subscription<rlfw_msgs::msg::MotorCfg>::SharedPtr sub_motor_cfg;
  void sendMotorCfg(std::shared_ptr<rlfw_msgs::msg::MotorCfg> msg);

  // 接受电机控制
  rclcpp::Subscription<rlfw_msgs::msg::MotorCtrl>::SharedPtr sub_motor;
  void sendMotor(std::shared_ptr<rlfw_msgs::msg::MotorCtrl> msg);

private:
  tinyxml2::XMLDocument doc;
  void loadXML(std::string path = "./install/" + std::string(PROJECT_NAME) +
                                  "/share/motor_cfg.xml");

  std::thread th;
  std::atomic<bool> flag{true};

  GamePad *gamepad;
  void initGamePad();
  Serial *serial;
  void timer_callback();
  rclcpp::TimerBase::SharedPtr timer;
};
