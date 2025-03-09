#include "QApplication"
#include "QLabel"
#include "rclcpp/rclcpp.hpp"
#include "rlfw_msgs/msg/motor.hpp"
#include "rlfw_msgs/msg/motor_ctrl.hpp"
#include "rlfw_msgs/msg/can_msg.hpp"
#include "rlfw_msgs/msg/serial_msg.hpp"
#include <chrono>
#include <qcoreapplication.h>
#include <rlfw_msgs/msg/detail/can_msg__struct.hpp>
#include <rlfw_msgs/msg/detail/serial_msg__struct.hpp>
#include <thread>

using namespace std::chrono_literals;

class MotorCTRL : public rclcpp::Node {
public:
  MotorCTRL(const std::string &node_name, int publish_interval_ms)
      : rclcpp::Node(node_name) {
    // 1. 创建 ROS 2 定时器（单位：毫秒）
    timer_ = create_wall_timer(std::chrono::milliseconds(publish_interval_ms),
                               std::bind(&MotorCTRL::pub, this));

    // 2. 初始化发布者和订阅者
    publisher_ = create_publisher<rlfw_msgs::msg::MotorCtrl>("rlfwMotorCtrl", 2);
    can_pub = create_publisher<rlfw_msgs::msg::CanMsg>("rlfwCANSend", 2);
    serial_pub = create_publisher<rlfw_msgs::msg::SerialMsg>("rlfwSerialSend", 2);
    sub_motor_ = create_subscription<rlfw_msgs::msg::Motor>(
        "rlfwMotorBack", 10,
        std::bind(&MotorCTRL::printData, this, std::placeholders::_1));

    // 3. 初始化 Qt 标签
    label_ = new QLabel;
    label_->resize(640, 480);
    label_->show();
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<rlfw_msgs::msg::MotorCtrl>::SharedPtr publisher_;
  rclcpp::Subscription<rlfw_msgs::msg::Motor>::SharedPtr sub_motor_;
  rclcpp::Publisher<rlfw_msgs::msg::CanMsg>::SharedPtr can_pub;
  rclcpp::Publisher<rlfw_msgs::msg::SerialMsg>::SharedPtr serial_pub;
  QLabel *label_;

  void pub() {
    auto stamp = this->now();
    auto msg = rlfw_msgs::msg::MotorCtrl();
    msg.jointname.frame_id = "left_calf_joint";//left_calf_joint left_wheel_joint
    msg.jointname.stamp = stamp;
    msg.ctrl_type = "MIT";
    msg.ang_vel = 1.0;
    msg.kd = 0.7;
    publisher_->publish(msg);

    msg.jointname.frame_id = "left_wheel_joint";//left_calf_joint left_wheel_joint
    msg.jointname.stamp = stamp;
    msg.ctrl_type = "MIT";
    msg.ang_vel = 1.0;
    msg.kd = 0.7;
    publisher_->publish(msg);

    auto can_msg = rlfw_msgs::msg::CanMsg();
    can_msg.comname.frame_id="com_can_1";
    can_msg.comname.stamp = stamp;
    can_pub->publish(can_msg);
    auto serial_msg = rlfw_msgs::msg::SerialMsg();
    serial_msg.comname.frame_id="s3";
    serial_msg.comname.stamp = stamp;
    serial_msg.data.push_back(1);
    serial_msg.data.push_back(2);
    serial_msg.data.push_back(3);
    serial_pub->publish(serial_msg);
  }

  void printData(const rlfw_msgs::msg::Motor::SharedPtr msg) {
    // 使用 Qt 信号槽安全更新 UI
    QMetaObject::invokeMethod(label_, [this, msg]() {
      label_->setText(QString("ang_vel:") + QString::number(msg->ang_vel));
    });
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  QApplication app(argc, argv);

  // 参数化定时器间隔
  const int publish_interval_ms = 1;
  auto node =
      std::make_shared<MotorCTRL>("motor_ctrl_test", publish_interval_ms);
  std::thread ros_thread([node]() { rclcpp::spin(node); });
  ros_thread.detach(); // 分离线程
  return app.exec();
}