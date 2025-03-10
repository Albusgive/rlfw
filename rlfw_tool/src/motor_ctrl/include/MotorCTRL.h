#pragma once
#include "rclcpp/rclcpp.hpp"
#include "rlfw_msgs/msg/can_msg.hpp"
#include "rlfw_msgs/msg/motor.hpp"
#include "rlfw_msgs/msg/motor_ctrl.hpp"
#include "rlfw_msgs/msg/remote.hpp"
#include "rlfw_msgs/msg/serial_msg.hpp"
#include "rlfw_msgs/srv/com_parameter.hpp"
#include <QDebug>
#include <QObject>
#include <QThread>
#include <chrono>
#include <memory>
#include <qchar.h>
#include <qglobal.h>
#include <rclcpp/client.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rlfw_msgs/msg/detail/remote__struct.hpp>
#include <rlfw_msgs/srv/detail/com_parameter__struct.hpp>
using namespace std::chrono_literals;

class MotorCTRL : public QThread {
  Q_OBJECT
public:
  MotorCTRL(const std::string &node_name) {
    int argc = 0;
    char **argv = NULL;
    rclcpp::init(argc, argv);
    node = std::make_shared<rclcpp::Node>(node_name);

    publisher_ =
        node->create_publisher<rlfw_msgs::msg::MotorCtrl>("rlfwMotorCtrl", 2);
    can_pub = node->create_publisher<rlfw_msgs::msg::CanMsg>("rlfwCANSend", 2);
    serial_pub =
        node->create_publisher<rlfw_msgs::msg::SerialMsg>("rlfwSerialSend", 2);
    sub_motor_ = node->create_subscription<rlfw_msgs::msg::Motor>(
        "rlfwMotorBack", 10,
        std::bind(&MotorCTRL::printData, this, std::placeholders::_1));
    sub_remote_ = node->create_subscription<rlfw_msgs::msg::Remote>(
        "rlfwRemoteBack", 10,
        std::bind(&MotorCTRL::printRemoteData, this, std::placeholders::_1));
    client = node->create_client<rlfw_msgs::srv::ComParameter>(
        "CommunicationCenterSrv");

    // this->start();
  }

  void printData(const rlfw_msgs::msg::Motor::SharedPtr msg) {
    emitTopicData(QString("ang_vel:") + QString::number(msg->ang_vel));
  }

  void printRemoteData(const rlfw_msgs::msg::Remote::SharedPtr msg) {
    std::cout<<"RemoteData"<<std::endl;
  }

  void pub() {
    auto stamp = node->now();
    auto msg = rlfw_msgs::msg::MotorCtrl();
    msg.jointname.frame_id =
        "left_calf_joint"; // left_calf_joint left_wheel_joint
    msg.jointname.stamp = stamp;
    msg.ctrl_type = "MIT";
    msg.ang_vel = 1.0;
    msg.kd = 0.7;
    publisher_->publish(msg);

    msg.jointname.frame_id =
        "left_wheel_joint"; // left_calf_joint left_wheel_joint
    msg.jointname.stamp = stamp;
    msg.ctrl_type = "MIT";
    msg.ang_vel = 1.0;
    msg.kd = 0.7;
    publisher_->publish(msg);

    auto can_msg = rlfw_msgs::msg::CanMsg();
    can_msg.comname.frame_id = "com_can_1";
    can_msg.comname.stamp = stamp;
    can_pub->publish(can_msg);
    auto serial_msg = rlfw_msgs::msg::SerialMsg();
    serial_msg.comname.frame_id = "s3";
    serial_msg.comname.stamp = stamp;
    serial_msg.data.push_back(1);
    serial_msg.data.push_back(2);
    serial_msg.data.push_back(3);
    serial_pub->publish(serial_msg);
  }

  void stop() {
    auto stamp = node->now();
    auto msg = rlfw_msgs::msg::MotorCtrl();
    msg.jointname.frame_id =
        "left_calf_joint"; // left_calf_joint left_wheel_joint
    msg.jointname.stamp = stamp;
    msg.ctrl_type = "MIT";
    msg.ang_vel = 0.0;
    msg.kd = 0.0;
    publisher_->publish(msg);

    msg.jointname.frame_id =
        "left_wheel_joint"; // left_calf_joint left_wheel_joint
    msg.jointname.stamp = stamp;
    msg.ctrl_type = "MIT";
    msg.ang_vel = 0.0;
    msg.kd = 0.0;
    publisher_->publish(msg);
  }
  void request() {

    std::cout << "request" << std::endl;
    // 等待服务端上线
    int cnt=0;
    while (!client->wait_for_service(200ms)) {
      RCLCPP_INFO(node->get_logger(),"wait serice");
      if (!rclcpp::ok()) {
        rclcpp::shutdown();
        return;
      }
      cnt++;
      if(cnt>5)
      {
        RCLCPP_WARN(node->get_logger(),"serice long");
        return;
      }
    }
    auto request = std::make_shared<rlfw_msgs::srv::ComParameter::Request>();
    request->request_communication_center_parameter = "MountRmote";

    auto result = client->async_send_request(request);
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS) {
      auto respond = result.get();
      QString emit_str;
      for (auto str : respond->device_name) {
        emit_str.append(QString::fromStdString(str) + " ");
      }
      emitSrvData(emit_str);
    } else {
      std::cout << "no back" << std::endl;
    }
  }
  void enable(int flag) {
    auto stamp = node->now();
    auto msg = rlfw_msgs::msg::MotorCtrl();
    msg.jointname.frame_id =
        "left_calf_joint"; // left_calf_joint left_wheel_joint
    msg.jointname.stamp = stamp;
    msg.ctrl_type = "ENABLE";
    msg.kd = flag;
    publisher_->publish(msg);
    msg.jointname.frame_id =
        "left_wheel_joint"; // left_calf_joint left_wheel_joint
    publisher_->publish(msg);
  }

private:
  rclcpp::Publisher<rlfw_msgs::msg::MotorCtrl>::SharedPtr publisher_;
  rclcpp::Subscription<rlfw_msgs::msg::Motor>::SharedPtr sub_motor_;
  rclcpp::Publisher<rlfw_msgs::msg::CanMsg>::SharedPtr can_pub;
  rclcpp::Publisher<rlfw_msgs::msg::SerialMsg>::SharedPtr serial_pub;
  rclcpp::Client<rlfw_msgs::srv::ComParameter>::SharedPtr client;
  rclcpp::Subscription<rlfw_msgs::msg::Remote>::SharedPtr sub_remote_;

  std::shared_ptr<rclcpp::Node> node;
  void poorer_callback(
      rclcpp::Client<rlfw_msgs::srv::ComParameter>::SharedFuture response) {
    std::cout << "back" << std::endl;
    // 使用response的get()获取
    auto result = response.get();
    QString emit_str;
    for (auto str : result->device_name) {
      std::cout << str << std::endl;
      emit_str.append(QString::fromStdString(str) + " ");
    }
    emitSrvData(emit_str);
  }

protected:
  void run() {
    rclcpp::WallRate loop_rate(1);
    while (rclcpp::ok()) {
      pub();
      rclcpp::spin_some(node);
      loop_rate.sleep();
    }
    rclcpp::shutdown();
  }

signals:
  void emitTopicData(QString);
  void emitSrvData(QString);
};