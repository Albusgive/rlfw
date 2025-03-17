#include "AgentNode.h"
#include <chrono>
#include <mutex>
#include <rclcpp/utilities.hpp>
#include <thread>
#include <vector>
AgentNode::AgentNode(std::string node_name) : rclcpp::Node(node_name) {

  rclcpp::QoS control_qos(env_cfg.dof_names.size());
  control_qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
  control_qos.history(RMW_QOS_POLICY_HISTORY_KEEP_ALL);
  rclcpp::QoS remote_qos(10);
  remote_qos.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);

  pub_joint_ = this->create_publisher<rlfw_msgs::msg::JointCtrl>(
      "rlfwJointCtrl", control_qos);
  sub_joint_ = this->create_subscription<rlfw_msgs::msg::Joint>(
      "rlfwJointBack", control_qos,
      std::bind(&AgentNode::JointBack, this, std::placeholders::_1));
  sub_imu_ = this->create_subscription<sensor_msgs::msg::Imu>(
      "/nz_imu", 10,
      std::bind(&AgentNode::imu_callback, this, std::placeholders::_1));
  sub_remote_ = this->create_subscription<rlfw_msgs::msg::Remote>(
      "rlfwRemoteBack", remote_qos,
      std::bind(&AgentNode::RevRemote, this, std::placeholders::_1));

  for (int i = 0; i < static_cast<int>(env_cfg.dof_names.size()); i++) {
    joint_idx_map[i] = env_cfg.dof_names[i];
    joint_map[env_cfg.dof_names[i]] = i;
  }

  history_and_now_obs_buf = new CircularBuffer(env_cfg.history_length + 1);
  std::string model_path =
      "/home/albusgive2/rlfw/rlfw_deploy/src/agent/policy.pt";
  module = torch::jit::load(model_path.c_str(), device);

  dof_pos.resize(env_cfg.dof_names.size() - 2);
  dof_vel.resize(env_cfg.dof_names.size());
  obs_actions.resize(env_cfg.dof_names.size());
  commands.resize(4);
  commands = {0.0, 0.0, 0.0, 0.2};
  runMode();
}

AgentNode::~AgentNode() {}
std::vector<float> AgentNode::world2self(std::vector<float> &quat,
                                         std::vector<float> v) {
  Eigen::Quaterniond q(quat[0], quat[1], quat[2], quat[3]);
  Eigen::Vector3d v_vec(v[0], v[1], v[2]);
  float q_w = q.w();
  Eigen::Vector3d q_vec = q.vec();
  Eigen::Vector3d a = v_vec * (2.0 * q_w * q_w - 1.0);
  Eigen::Vector3d b = q_vec.cross(v_vec) * q_w * 2.0;
  Eigen::Vector3d c = q_vec * (q_vec.dot(v_vec)) * 2.0;
  Eigen::Vector3d result = a - b + c;
  std::vector<float> world_angle_speed = {static_cast<float>(result.x()),
                                          static_cast<float>(result.y()),
                                          static_cast<float>(result.z())};
  return world_angle_speed;
}

void AgentNode::imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg) {
  base_quat[0] = msg->orientation.w;
  base_quat[1] = msg->orientation.x;
  base_quat[2] = msg->orientation.y;
  base_quat[3] = msg->orientation.z;
  std::vector<float> gravity_vec = {0.0, 0.0, -1.0};
  projected_gravity = world2self(base_quat, gravity_vec);
  ang_vel[0] = msg->angular_velocity.x;
  ang_vel[1] = msg->angular_velocity.y;
  ang_vel[2] = msg->angular_velocity.z;
  // cout_vector(projected_gravity,"gravity_vec", Color::Green);
}

void AgentNode::JointBack(const rlfw_msgs::msg::Joint::SharedPtr msg) {
  int idx = joint_map[msg->jointname.frame_id];
  dof_pos[idx] = msg->pos;
  dof_vel[idx] = msg->vel;
}

void AgentNode::RevRemote(const rlfw_msgs::msg::Remote::SharedPtr msg) {
  for (int i = 0; i < static_cast<int>(msg->key.size()); i++) {
    if (msg->key[i] == "ly") {
      commands[0] = -msg->value[i] / 32767.0 * gamepad_scale[0];
    } else if (msg->key[i] == "rx") {
      commands[2] = -msg->value[i] / 32767.0 * gamepad_scale[2];
    } else if (msg->key[i] == "lt") {
      commands[3] += (msg->value[i] + 32767) / 65535.0 * gamepad_scale[3];
    } else if (msg->key[i] == "rt") {
      commands[3] -= (msg->value[i] + 32767) / 65535.0 * gamepad_scale[3];
    } else if (msg->key[i] == "x") {
      // 所有电机失能
      auto stamp = this->now();
      rlfw_msgs::msg::JointCtrl msg;
      msg.jointname.stamp = stamp;
      msg.ctrl_type = "ENABLE";
      msg.kd = 0.0;
      for (auto name : env_cfg.dof_names) {
        msg.jointname.frame_id = name;
        pub_joint_->publish(msg);
      }
    } else if (msg->key[i] == "y") {
      // 所有电机使能
      auto stamp = this->now();
      rlfw_msgs::msg::JointCtrl msg;
      msg.jointname.stamp = stamp;
      msg.ctrl_type = "ENABLE";
      msg.kd = 1.0;
      for (auto name : env_cfg.dof_names) {
        msg.jointname.frame_id = name;
        pub_joint_->publish(msg);
      }
    }
  }
}

std::vector<float> AgentNode::compute_ctrl(std::vector<float> act) {
  // 缩放
  std::vector<float> action(act.size());
  action[0] = act[0] * action_cfg.joint_action_scale;
  action[1] = act[1] * action_cfg.joint_action_scale;
  action[2] = act[2] * action_cfg.joint_action_scale;
  action[3] = act[3] * action_cfg.joint_action_scale;
  action[4] = act[4] * action_cfg.wheel_action_scale;
  action[5] = act[5] * action_cfg.wheel_action_scale;
  // 裁减 在电机端已经做好了
  //   for (int i = 0; i < static_cast<int>(env_cfg.min_joint_angles.size());
  //   i++) {
  //     if (action[i] < env_cfg.min_joint_angles[i])
  //       action[i] = env_cfg.min_joint_angles[i];
  //   }
  //   for (int i = 0; i < static_cast<int>(env_cfg.max_joint_angles.size());
  //   i++) {
  //     if (action[i] > env_cfg.max_joint_angles[i])
  //       action[i] = env_cfg.max_joint_angles[i];
  //   }
  return action;
}

std::vector<float> AgentNode::compute_observations() {
  std::lock_guard<std::mutex> lock(mtx);
  std::vector<float> obs;
  // 角速度---------- num 3
  for (int i = 0; i < static_cast<int>(ang_vel.size()); i++) {
    ang_vel[i] *= obs_sacle.ang_vel;
    obs.push_back(ang_vel[i]);
  }
  // 重力投影---------- num 3
  for (auto &i : projected_gravity) {
    obs.push_back(i);
  }
  // // command---------- num 4
  // if (commands[3] > 0.32) {
  //   commands[3] = 0.32;
  // } else if (commands[3] < 0.2) {
  //   commands[3] = 0.2;
  // }
  commands[3] = 0.2;
  for (int i = 0; i < (int)obs_sacle.command_scale.size(); i++) {
    obs.push_back(commands[i] * obs_sacle.command_scale[i]);
  }
  // dof_pos num 4
  for (auto &i : dof_pos) {
    obs.push_back((i - env_cfg.default_joint_angles[i]) * obs_sacle.dof_pos);
  }
  // dof_vel num 6
  for (auto &i : dof_vel) {
    obs.push_back(i * obs_sacle.dof_vel);
  }
  // action num 6
  for (auto &i : obs_actions)
    obs.push_back(i);

  return obs;
}

void AgentNode::runMode() {
  for (int i = 0; i < env_cfg.history_length; i++) {
    history_and_now_obs_buf->push_back(compute_observations());
  }
  auto mode_thread = std::thread([this]() {
    while (rclcpp::ok()) {
      auto slice_obs_buf = compute_observations();
      history_and_now_obs_buf->push_back(slice_obs_buf);
      auto obs_buf = history_and_now_obs_buf->get_all();
      torch::Tensor obs =
          torch::from_blob(obs_buf.data(), {static_cast<long>(obs_buf.size())},
                           torch::kFloat32)
              .to(device);
      torch::jit::Stack inputs;
      inputs.push_back(obs);
      auto start = std::chrono::high_resolution_clock::now();
      auto output_tensor = module.forward(std::move(inputs)).toTensor().cpu();
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> duration_ms = end - start;
      std::cout << "用时：" << duration_ms.count() << std::endl;
      // 裁减action 观测和输出前
      output_tensor = torch::clip(output_tensor, -action_cfg.clip_actions,
                                  action_cfg.clip_actions);
      std::vector<float> vec(output_tensor.data_ptr<float>(),
                             output_tensor.data_ptr<float>() +
                                 output_tensor.numel());
      obs_actions = vec;
      auto action_ = compute_ctrl(vec);
      sendJoint(action_);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      cout_vector(ang_vel, "ang_vel", Color::Green);
      cout_vector(projected_gravity, "projected_gravity", Color::Green);
      cout_vector(action_, "action_", Color::Green);
      cout_vector(commands, "commands", Color::Blue);
    }
  });
  mode_thread.detach();
}

void AgentNode::sendJoint(std::vector<float> actions) {
  std::lock_guard<std::mutex> lock(mtx);
  for (int i = 0; i < 4; i++) {
    rlfw_msgs::msg::JointCtrl msg;
    msg.jointname.stamp = this->now();
    msg.jointname.frame_id = joint_idx_map[i];
    msg.ctrl_type = "MIT";
    msg.pos = actions[i];
    msg.kp = action_cfg.kp;
    msg.kd = action_cfg.kd;
    pub_joint_->publish(msg);
  }
  for (int i = 4; i < 6; i++) {
    rlfw_msgs::msg::JointCtrl msg;
    msg.jointname.stamp = this->now();
    msg.jointname.frame_id = joint_idx_map[i];
    msg.ctrl_type = "VEL";
    msg.vel = actions[i];
    pub_joint_->publish(msg);
  }
}

template <typename T>
void AgentNode::cout_vector(const T &data, const std::string &name,
                            Color color) {
  // 选择颜色并打印
  std::cout << "\033[" << static_cast<int>(color) << "m" << name << ": ";
  std::cout << std::fixed << std::setprecision(6) << std::endl;

  for (const auto &i : data) {
    std::cout << i << " ";
  }

  // 重置颜色
  std::cout << "\033[" << static_cast<int>(Color::Reset) << "m" << std::endl;
}