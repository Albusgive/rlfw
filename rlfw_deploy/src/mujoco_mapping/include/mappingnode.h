#pragma once
#include "mujoco_base.h"
#include "rclcpp/rclcpp.hpp"
#include "rlfw_msgs/msg/joint.hpp"
#include "rlfw_msgs/msg/joint_ctrl.hpp"
#include "rlfw_msgs/srv/com_parameter.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include <rclcpp/node.hpp>
#include <rlfw_msgs/msg/detail/joint__struct.hpp>
#include <rlfw_msgs/msg/detail/joint_ctrl__struct.hpp>
#include <string>
#include <atomic>
using namespace std::placeholders;

class MappingNode : public rclcpp::Node {
public:
  MappingNode(std::string node_name, std::string file, float dt,
              std::string imu_topic_name = "",
              std::string body_quat_mapping_name = "",
              std::string robot_name = "");
  ~MappingNode();
  std::string imu_topic_name;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub;
  rclcpp::Subscription<rlfw_msgs::msg::Joint>::SharedPtr joint_sub;
  rclcpp::Subscription<rlfw_msgs::msg::JointCtrl>::SharedPtr joint_ctrl_sub;
  rclcpp::Publisher<rlfw_msgs::msg::JointCtrl>::SharedPtr joint_ask;
  rclcpp::Publisher<rlfw_msgs::msg::Joint>::SharedPtr joint_pub;
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub;
  // 通讯中心参数服务器
  rclcpp::Service<rlfw_msgs::srv::ComParameter>::SharedPtr request;
  void handle_request(
      const std::shared_ptr<rlfw_msgs::srv::ComParameter::Request> request,
      std::shared_ptr<rlfw_msgs::srv::ComParameter::Response> response);

  mujoco_base *mj_;
  void imu_back(const sensor_msgs::msg::Imu::SharedPtr msg);
  void imu_send(std::vector<mjtNum> &orientation, std::vector<mjtNum> &base_ang_vel,
    std::vector<mjtNum> &base_acc);
  void joint_back(const rlfw_msgs::msg::Joint::SharedPtr msg);
  void joint_ctrl(const rlfw_msgs::msg::JointCtrl::SharedPtr msg);
  void send_joint_data(std::vector<std::string>& joint_name,
                       std::vector<float>& pos, std::vector<float>& vel);
  void AskJoint(std::vector<std::string> &joint_names);
  std::atomic_bool is_ask{false};

private:
  float dt;
  std::thread askjoint_thread; 
};
