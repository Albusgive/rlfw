#include "mappingnode.h"
#include "mujoco_base.h"
#include <chrono>
#include <functional>
#include <rlfw_msgs/msg/detail/joint__struct.hpp>
#include <rlfw_msgs/msg/detail/joint_ctrl__struct.hpp>
#include <string>
#include <thread>
MappingNode::MappingNode(std::string node_name, std::string file, float dt,
                         std::string imu_topic_name,
                         std::string body_quat_mapping_name,
                         std::string robot_name)
    : rclcpp::Node(node_name), imu_topic_name(imu_topic_name), dt(dt) {
  mj_ = new mujoco_base(file);
  mj_->setDt(dt);
  mj_->setRobotName(robot_name);
  mj_->getQuatBodyIdx(body_quat_mapping_name);
  rclcpp::QoS control_qos(10);
  control_qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
  control_qos.history(RMW_QOS_POLICY_HISTORY_KEEP_ALL);
  imu_sub = this->create_subscription<sensor_msgs::msg::Imu>(
      "nz_imu", 10, std::bind(&MappingNode::imu_back, this, _1));

  joint_sub = this->create_subscription<rlfw_msgs::msg::Joint>(
      "rlfwJointBack", control_qos,
      std::bind(&MappingNode::joint_back, this, _1));
  joint_ctrl_sub = this->create_subscription<rlfw_msgs::msg::JointCtrl>(
      "rlfwJointCtrl", control_qos,
      std::bind(&MappingNode::joint_ctrl, this, _1));

  joint_ask = this->create_publisher<rlfw_msgs::msg::JointCtrl>(
      "rlfwJointCtrl", rclcpp::QoS(control_qos));
  joint_pub = this->create_publisher<rlfw_msgs::msg::Joint>(
      "rlfwJointBack", rclcpp::QoS(control_qos));
  imu_pub = this->create_publisher<sensor_msgs::msg::Imu>(
      "/mj_imu", rclcpp::QoS(control_qos));
  // 服务器
  request = this->create_service<rlfw_msgs::srv::ComParameter>(
      "MappingSrv", std::bind(&MappingNode::handle_request, this, _1, _2));

  mj_->bindJointData(
      std::bind(&MappingNode::send_joint_data, this, _1, _2, _3));
  mj_->bindAskJoint(std::bind(&MappingNode::AskJoint, this, _1));
  mj_->bindImuData(std::bind(&MappingNode::imu_send, this, _1, _2, _3));
  mj_->change_mode("step");
  mj_->render_and_forward_or_step();
}
MappingNode::~MappingNode() {}

void MappingNode::imu_back(const sensor_msgs::msg::Imu::SharedPtr msg) {
  mj_->setBodyQuat(msg->orientation.w, msg->orientation.x, msg->orientation.y,
                   msg->orientation.z);
}

void MappingNode::imu_send(std::vector<mjtNum> &orientation,
                           std::vector<mjtNum> &base_ang_vel,
                           std::vector<mjtNum> &base_acc) {
  sensor_msgs::msg::Imu msg;
  msg.header.stamp = this->now();
  msg.header.frame_id = "mj_imu";
  msg.angular_velocity.x = base_ang_vel[0];
  msg.angular_velocity.y = base_ang_vel[1];
  msg.angular_velocity.z = base_ang_vel[2];
  msg.linear_acceleration.x = base_acc[0];
  msg.linear_acceleration.y = base_acc[1];
  msg.linear_acceleration.z = base_acc[2];
  msg.orientation.w = orientation[0];
  msg.orientation.x = orientation[1];
  msg.orientation.y = orientation[2];
  msg.orientation.z = orientation[3];
  imu_pub->publish(msg);
}

void MappingNode::joint_back(const rlfw_msgs::msg::Joint::SharedPtr msg) {
  mj_->setJointPos(msg->jointname.frame_id, msg->pos);
}

void MappingNode::joint_ctrl(const rlfw_msgs::msg::JointCtrl::SharedPtr msg) {
  if (msg->ctrl_type == "MIT") {
    if (msg->pos != 0.0) {
      mj_->setAction(msg->jointname.frame_id, msg->pos);
    } else if (msg->pos == 0 && msg->vel != 0.0) {
      mj_->setAction(msg->jointname.frame_id, msg->vel);
    } else {
      mj_->setAction(msg->jointname.frame_id, msg->torque);
    }
  } else if (msg->ctrl_type == "POS") {
    mj_->setAction(msg->jointname.frame_id, msg->pos);
  } else if (msg->ctrl_type == "VEL") {
    mj_->setAction(msg->jointname.frame_id, msg->vel);
  } else if (msg->ctrl_type == "TORQUE") {
    mj_->setAction(msg->jointname.frame_id, msg->torque);
  }
}

void MappingNode::send_joint_data(std::vector<std::string> &joint_name,
                                  std::vector<float> &pos,
                                  std::vector<float> &vel) {
  rlfw_msgs::msg::Joint msg;
  for (int i = 0; i < static_cast<int>(joint_name.size()); i++) {
    msg.jointname.frame_id = joint_name[i] + "_mapping";
    msg.jointname.stamp = this->now();
    msg.pos = pos[i];
    msg.vel = vel[i];
    joint_pub->publish(msg);
  }
}

void MappingNode::AskJoint(std::vector<std::string> &joint_names) {
  rlfw_msgs::msg::JointCtrl msg;
  for (auto name : joint_names) {
    msg.jointname.stamp = this->now();
    msg.jointname.frame_id = name;
    msg.ctrl_type = "MIT";
    msg.pos = 0.0;
    msg.vel = 0.0;
    msg.torque = 0.0;
    msg.kp = 0.0;
    msg.kd = 0.0;
    joint_ask->publish(msg);
  }
}

void MappingNode::handle_request(
    const std::shared_ptr<rlfw_msgs::srv::ComParameter::Request> request,
    std::shared_ptr<rlfw_msgs::srv::ComParameter::Response> response) {
  std::string type = request->request_communication_center_parameter;
  if (type == "MountMotor") {
    for (auto jnt : mj_->joint_names) {
      response->device_name.push_back(jnt + "_mapping");
      response->device_type.push_back("mujoco mapping");
    }
    // std::cout << request->request_communication_center_parameter<<
    // response->device_name.size()<< std::endl;
  }
}
