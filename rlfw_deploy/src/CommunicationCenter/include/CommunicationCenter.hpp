#pragma once
#include "BaseCAN.h"
#include "BaseRemote.h"
#include "Motor.hpp"
#include "PCAN.hpp"
#include "XMLDecoder.hpp"
#include "gamepad.h"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rlfw_msgs/msg/can_msg.hpp"
#include "rlfw_msgs/msg/joint.hpp"
#include "rlfw_msgs/msg/joint_ctrl.hpp"
#include "rlfw_msgs/msg/remote.hpp"
#include "rlfw_msgs/msg/serial_msg.hpp"
#include "rlfw_msgs/srv/com_parameter.hpp"
#include "serial.hpp"
#include <cstdint>
#include <memory>
#include <mutex>
#include <rclcpp/service.hpp>
#include <rlfw_msgs/msg/detail/joint__struct.hpp>
#include <rlfw_msgs/msg/detail/remote__struct.hpp>
#include <rlfw_msgs/msg/detail/serial_msg__struct.hpp>
#include <rlfw_msgs/srv/detail/com_parameter__struct.hpp>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std::placeholders;

enum class ComeCenterParamType {
  MountCom,   // 通讯接口
  MountMotor, // 电机
  MountRmote, // 遥控器（gamepad）
  ERR
};

class CommunicationCenter : public rclcpp::Node {
public:
  CommunicationCenter(const std::string &node_name);
  ~CommunicationCenter();

  // 接收com信息 无论什么类型全在子线程进行
  rclcpp::Publisher<rlfw_msgs::msg::Joint>::SharedPtr motor_publisher;
  // 任何设备都使用这些读取
  void fromCan(CANMSG &msg, std::vector<int> &device_ids,
               std::string &com_name);
  void fromSerial(std::vector<uint8_t> &msg, std::string com_name);
  void fromSerialMotor() {};
  void fromRemote(std::vector<std::string> &key, std::vector<float>& value);
  // 对于没有独立线程的com(主要是can)统一线程读取，serial独立线程接收
  void RunRecv();

private:
  // 在主线程的端口发送 pcan发送一次约0.14ms(12400f)
  rclcpp::Subscription<rlfw_msgs::msg::JointCtrl>::SharedPtr sub_motor;
  void sendMotor(std::shared_ptr<rlfw_msgs::msg::JointCtrl> msg);
  std::shared_ptr<BaseMotor> motor_safe_get(const std::string &name);
  std::shared_ptr<BaseMotor> virtual_motor_safe_get(const std::string &name);

  // 基础can通讯
  rclcpp::Publisher<rlfw_msgs::msg::CanMsg>::SharedPtr can_publisher;
  rclcpp::Subscription<rlfw_msgs::msg::CanMsg>::SharedPtr can_sub;
  void sendCAN(std::shared_ptr<rlfw_msgs::msg::CanMsg> msg);

  // 在子线程的端口发送 serial
  rclcpp::Publisher<rlfw_msgs::msg::SerialMsg>::SharedPtr serial_publisher;
  rclcpp::Subscription<rlfw_msgs::msg::SerialMsg>::SharedPtr serial_sub;
  void sendSerial(std::shared_ptr<rlfw_msgs::msg::SerialMsg> msg);

  // 在子线程的端口发送 remote
  rclcpp::Publisher<rlfw_msgs::msg::Remote>::SharedPtr remote_publisher;

  // 通讯中心参数服务器
  rclcpp::Service<rlfw_msgs::srv::ComParameter>::SharedPtr request;
  void handle_request(
      const std::shared_ptr<rlfw_msgs::srv::ComParameter::Request> request,
      std::shared_ptr<rlfw_msgs::srv::ComParameter::Response> response);

  std::string motor_cfg_path =
      "./install/" + std::string(PROJECT_NAME) + "/share/motor_cfg.xml";
  // 加载配置
  XMLDecoder xml_decoder;
  // 注册电机解码器
  std::vector<std::shared_ptr<BaseMotor>> moter_decoders;
  std::vector<Motortype> registered_motor_types; // 已经注册的电机类型
  std::unordered_map<int, std::shared_ptr<BaseMotor>> motorID_map;
  void registeredMotorDecoder(Motortype motor_type);
  // 字符串映射
  std::unordered_map<std::string, std::shared_ptr<BaseMotor>> motor_map;
  std::unordered_map<std::string, std::shared_ptr<BaseMotor>> virtual_motor_map;
  std::vector<std::shared_ptr<BaseCAN>> cans;
  std::unordered_map<std::string, int> cans_map;
  std::vector<std::shared_ptr<Serial>> serials;
  std::unordered_map<std::string, int> serials_map;
  std::vector<std::shared_ptr<BaseRemote>> remotes;
  void buildMap();
  // 电机使能和参数写入
  void initMotor(std::shared_ptr<BaseMotor> _motor, XMLMotor xml_motor);
  // 对不同通讯子线程处理CommunicationCenter的函数使用
  // 接受电机消息，接受串口消息
  std::mutex com_mutex;
};
