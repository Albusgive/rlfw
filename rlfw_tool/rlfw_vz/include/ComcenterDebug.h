#pragma once
#include "rclcpp/rclcpp.hpp"
#include "rlfw_msgs/msg/can_msg.hpp"
#include "rlfw_msgs/msg/joint.hpp"
#include "rlfw_msgs/msg/joint_ctrl.hpp"
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
#include <rclcpp/qos.hpp>
#include <rlfw_msgs/msg/detail/joint__struct.hpp>
#include <rlfw_msgs/msg/detail/joint_ctrl__struct.hpp>
#include <rlfw_msgs/msg/detail/remote__struct.hpp>
#include <rlfw_msgs/srv/detail/com_parameter__struct.hpp>
#include <string>
#include <vector>
using namespace std::chrono_literals;

enum class JointDataType{None,torque,pos,number_laps,vel,current,temperature,state};

class ComcenterDebug : public QThread {
  Q_OBJECT
public:
  ComcenterDebug(const std::string &node_name);

  void JointBack(const rlfw_msgs::msg::Joint::SharedPtr msg);
  JointDataType joint_data_type = JointDataType::pos;
  void setJointDataType(QString type);
  void printRemoteData(const rlfw_msgs::msg::Remote::SharedPtr msg);
  void pub();
  void pub2();
  void stop();
  void requestComParameter();
  void enable(int flag);


private:
  rclcpp::Publisher<rlfw_msgs::msg::JointCtrl>::SharedPtr publisher_;
  rclcpp::Subscription<rlfw_msgs::msg::Joint>::SharedPtr sub_motor_;
  rclcpp::Publisher<rlfw_msgs::msg::CanMsg>::SharedPtr can_pub;
  rclcpp::Publisher<rlfw_msgs::msg::SerialMsg>::SharedPtr serial_pub;
  rclcpp::Client<rlfw_msgs::srv::ComParameter>::SharedPtr client;
  rclcpp::Subscription<rlfw_msgs::msg::Remote>::SharedPtr sub_remote_;
  std::vector<std::string> request_names = {
      "MountCom",
      "MountMotor",
      "MountRmote",
  };

  std::shared_ptr<rclcpp::Node> node;
  void poorer_callback(
      rclcpp::Client<rlfw_msgs::srv::ComParameter>::SharedFuture response);

protected:
  void run();

signals:
  void emitComParameter(QString, QStringList,QStringList);
  void emitJointData(QString,float);
  void emitSrvData(QString);
};