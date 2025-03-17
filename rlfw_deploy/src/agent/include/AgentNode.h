#pragma once
#include "rclcpp/rclcpp.hpp"
#include "rlfw_msgs/msg/joint.hpp"
#include "rlfw_msgs/msg/joint_ctrl.hpp"
#include "rlfw_msgs/msg/remote.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/StdVector>
#include <c10/core/Device.h>
#include <deque>
#include <iostream>
#include <mutex>
#include <rclcpp/node.hpp>
#include <string>
#include <torch/csrc/autograd/generated/variable_factories.h>
#include <torch/script.h>
#include <torch/torch.h>
#include <unordered_map>
#include <vector>
class ENV_CFG {
public:
  int num_actions = 6;
  int history_length = 5;
  int num_obs = 156;
  int num_slice_obs = 26;
  int num_commands = 4;
  std::vector<float> default_joint_angles;
  std::vector<float> min_joint_angles;
  std::vector<float> max_joint_angles;
  std::vector<std::string> dof_names;
  ENV_CFG()
      : default_joint_angles({0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}),
        min_joint_angles({-1.0472, 0, -1.0472, 0, -100, -100}),
        max_joint_angles({0.5236, 1.3963, 0.5236, 1.3963, 100, 100}),
        dof_names({"left_thigh_joint", "left_calf_joint", "right_thigh_joint",
                   "right_calf_joint", "left_wheel_joint",
                   "right_wheel_joint"}) {}
};

class OBS_SCALE {
public:
  float lin_vel = 2.0;
  float ang_vel = 0.5;
  float dof_pos = 1.0;
  float dof_vel = 0.05;
  // command scales
  float height_measurements = 5.0;
  std::vector<float> command_scale;
  OBS_SCALE()
      : command_scale({lin_vel, lin_vel, ang_vel, height_measurements}) {}
};

class ACTION_CFG {
public:
  float joint_action_scale = 0.1; // 0.5
  float wheel_action_scale = 0.5;   // 10
  float clip_actions = 100;
  float kp = 10;
  float kd = 1.5;
};

class CircularBuffer {
public:
  CircularBuffer(size_t max_size) : max_size(max_size) {}

  void push_back(const std::vector<float> &value) {
    if (buffer.size() == max_size) {
      buffer.pop_front(); // 如果超过容量，从前端删除最早的元素
    }
    buffer.push_back(value);
  }

  // 获取所有元素并将它们合并为一个vector
  std::vector<float> get_all() const {
    std::vector<float> all_elements;
    for (const auto &vec : buffer) {
      all_elements.insert(all_elements.end(), vec.begin(), vec.end());
    }
    return all_elements;
  }

private:
  std::deque<std::vector<float>> buffer; // 仅支持 std::vector<doubfloatle>
  size_t max_size;
};

enum class Color {
  Red = 31,
  Green = 32,
  Yellow = 33,
  Blue = 34,
  Magenta = 35,
  Cyan = 36,
  White = 37,
  Reset = 0
};

class AgentNode : public rclcpp::Node {
public:
  AgentNode(std::string nodename);
  ~AgentNode();
  std::string node_name;

  std::vector<float> world2self(std::vector<float> &quat, std::vector<float> v);
  ENV_CFG env_cfg;
  OBS_SCALE obs_sacle;
  ACTION_CFG action_cfg;
  CircularBuffer *history_and_now_obs_buf;

  // std::vector<float> line_vel;
  std::vector<float> ang_vel = {0.0, 0.0, 0.0};
  std::vector<float> dof_pos;
  std::vector<float> dof_vel;
  std::vector<float> base_quat = {1.0, 0.0, 0.0, 0.0};
  std::vector<float> projected_gravity = {0.0, 0.0, 0.0};
  std::vector<float> obs_actions;
  std::vector<float> commands;
  std::unordered_map<std::string, int> joint_map;
  std::unordered_map<int, std::string> joint_idx_map;
  std::vector<float> compute_ctrl(std::vector<float> act);

  std::vector<float> gamepad_scale = {1.0, 1.0, 3.14, 0.05};

  std::vector<float> compute_observations();

  void runMode();
  torch::Device device = torch::kCUDA;
  torch::jit::script::Module module;

private:
  rclcpp::Publisher<rlfw_msgs::msg::JointCtrl>::SharedPtr pub_joint_;
  rclcpp::Subscription<rlfw_msgs::msg::Joint>::SharedPtr sub_joint_;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr sub_imu_;
  rclcpp::Subscription<rlfw_msgs::msg::Remote>::SharedPtr sub_remote_;

  void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg);
  void JointBack(const rlfw_msgs::msg::Joint::SharedPtr msg);
  void RevRemote(const rlfw_msgs::msg::Remote::SharedPtr msg);

  void sendJoint(std::vector<float> actions);

  std::mutex mtx;

  template <typename T>
  void cout_vector(const T &data, const std::string &name,
                   Color color = Color::Reset);
};