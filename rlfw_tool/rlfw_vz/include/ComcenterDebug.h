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
#include <cstdint>
#include <memory>
#include <qchar.h>
#include <qcontainerfwd.h>
#include <qglobal.h>
#include <qobject.h>
#include <qthread.h>
#include <qtypes.h>
#include <rclcpp/client.hpp>
#include <rclcpp/executors.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/qos.hpp>
#include <rlfw_msgs/msg/detail/can_msg__struct.hpp>
#include <rlfw_msgs/msg/detail/joint__struct.hpp>
#include <rlfw_msgs/msg/detail/joint_ctrl__struct.hpp>
#include <rlfw_msgs/msg/detail/remote__struct.hpp>
#include <rlfw_msgs/msg/detail/serial_msg__struct.hpp>
#include <rlfw_msgs/srv/detail/com_parameter__struct.hpp>
#include <string>
#include <vector>
using namespace std::chrono_literals;

enum class JointDataType {
  None,
  torque,
  pos,
  number_laps,
  vel,
  current,
  temperature,
  state
};

class ComcenterDebug : public QThread {
  Q_OBJECT
public:
  ComcenterDebug(const std::string &node_name);
  ~ComcenterDebug();

  void JointBack(const rlfw_msgs::msg::Joint::SharedPtr msg);
  JointDataType joint_data_type = JointDataType::None;
  void setJointDataType(QString type);

  void ctrlJoint(std::string joint_name, std::string ctrl_type, float torque,
                 float pos, float vel, float kp, float kd);
  void enableJoint(std::string joint_name, bool enable);
  void requestComParameter();
  void enable(int flag);

  void resetQos(int his);

  // com
  void sendCom(int32_t id, std::vector<uint8_t> data);
  void changeCanIDType(int type);
  void changeComName(QString name);
  QString com_type;

private:
  // pub
  rclcpp::Publisher<rlfw_msgs::msg::JointCtrl>::SharedPtr publisher_;
  rclcpp::Subscription<rlfw_msgs::msg::Joint>::SharedPtr sub_motor_;
  rclcpp::Publisher<rlfw_msgs::msg::CanMsg>::SharedPtr can_pub;
  rclcpp::Publisher<rlfw_msgs::msg::SerialMsg>::SharedPtr serial_pub;
  rclcpp::Client<rlfw_msgs::srv::ComParameter>::SharedPtr client;
  // sub
  rclcpp::Subscription<rlfw_msgs::msg::Remote>::SharedPtr sub_remote_;
  rclcpp::Subscription<rlfw_msgs::msg::CanMsg>::SharedPtr sub_can_;
  rclcpp::Subscription<rlfw_msgs::msg::SerialMsg>::SharedPtr sub_serial_;
  void RevCAN(const rlfw_msgs::msg::CanMsg::SharedPtr msg);
  void RevSerial(const rlfw_msgs::msg::SerialMsg::SharedPtr msg);
  void RevRemote(const rlfw_msgs::msg::Remote::SharedPtr msg);
  std::vector<std::string> request_names = {
      "MountCom",
      "MountMotor",
      "MountRmote",
  };
  std::shared_ptr<rclcpp::Node> node;

  // com
  std::string com_name;
  int can_type;

  //remote

protected:
  void run();
signals:
  void emitComParameter(QString, QStringList, QStringList); // type coms types
  void emitJointData(QString, qreal, qreal);                // name time data
  void emitComData(qint32, QByteArray);            // id data
  void emitRemote(QStringList,QVector<float>); //key value
};