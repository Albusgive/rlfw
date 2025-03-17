#include "ComcenterDebug.h"
#include <qcontainerfwd.h>
#include <qdebug.h>
#include <qlogging.h>
#include <qobject.h>
#include <rclcpp/executors.hpp>
#include <rlfw_msgs/msg/detail/can_msg__struct.hpp>
#include <rlfw_msgs/msg/detail/serial_msg__struct.hpp>
ComcenterDebug::ComcenterDebug(const std::string &node_name) {
  int argc = 0;
  char **argv = NULL;
  rclcpp::init(argc, argv);
  node = std::make_shared<rclcpp::Node>(node_name);
  client = node->create_client<rlfw_msgs::srv::ComParameter>(
      "CommunicationCenterSrv");
}
ComcenterDebug::~ComcenterDebug() { rclcpp::shutdown(); }

void ComcenterDebug::JointBack(const rlfw_msgs::msg::Joint::SharedPtr msg) {
  switch (joint_data_type) {
  case JointDataType::pos: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  node->now().seconds(), msg->pos);
    break;
  }
  case JointDataType::vel: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  node->now().seconds(), msg->vel);
    break;
  }
  case JointDataType::torque: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  node->now().seconds(), msg->torque);
    break;
  }
  case JointDataType::current: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  node->now().seconds(), msg->current);
    break;
  }
  case JointDataType::temperature: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  node->now().seconds(), msg->temperature);
    break;
  }
  case JointDataType::number_laps: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  node->now().seconds(), msg->number_laps);
    break;
  }
  case JointDataType::state: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  node->now().seconds(), msg->state);
    break;
  }
  case JointDataType::None: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  node->now().seconds(), 0.0);
    break;
  }
  }
}

void ComcenterDebug::setJointDataType(QString type) {
  if (type == "pos") {
    joint_data_type = JointDataType::pos;
  } else if (type == "number_laps") {
    joint_data_type = JointDataType::number_laps;
  } else if (type == "vel") {
    joint_data_type = JointDataType::vel;
  } else if (type == "torque") {
    joint_data_type = JointDataType::torque;
  } else if (type == "current") {
    joint_data_type = JointDataType::current;
  } else if (type == "temperature") {
    joint_data_type = JointDataType::temperature;
  } else if (type == "state") {
    joint_data_type = JointDataType::state;
  } else if (type == "None") {
    joint_data_type = JointDataType::None;
  }
}

void ComcenterDebug::ctrlJoint(std::string joint_name, std::string ctrl_type,
                               float torque, float pos, float vel, float kp,
                               float kd) {
  rlfw_msgs::msg::JointCtrl msg;
  msg.jointname.stamp = node->now();
  msg.jointname.frame_id = joint_name;
  msg.ctrl_type = ctrl_type;
  msg.pos = pos;
  msg.vel = vel;
  msg.torque = torque;
  msg.kp = kp;
  msg.kd = kd;
  publisher_->publish(msg);
}

void ComcenterDebug::enableJoint(std::string joint_name, bool enable) {
  auto stamp = node->now();
  rlfw_msgs::msg::JointCtrl msg;
  msg.jointname.frame_id = joint_name;
  msg.jointname.stamp = stamp;
  msg.ctrl_type = "ENABLE";
  msg.kd = enable;
  publisher_->publish(msg);
}

void ComcenterDebug::requestComParameter() {
  // 等待服务端上线
  int cnt = 0;
  while (!client->wait_for_service(200ms)) {
    RCLCPP_INFO(node->get_logger(), "wait serice");
    if (!rclcpp::ok()) {
      rclcpp::shutdown();
      return;
    }
    cnt++;
    if (cnt > 5) {
      RCLCPP_WARN(node->get_logger(), "serice long");
      return;
    }
  }
  auto request = std::make_shared<rlfw_msgs::srv::ComParameter::Request>();
  // 请求类型
  for (auto devices : request_names) {
    request->request_communication_center_parameter = devices;
    auto result = client->async_send_request(request);
    auto respond = result.get();
    QStringList names, types;
    int cnt = static_cast<int>(respond->device_name.size());
    switch (cnt) {
    case 0: {
      names.push_back("None");
      types.push_back("None");
      break;
    }
    default: {
      for (int i = 0; i < cnt; i++) {
        QString joint_name = QString::fromStdString(respond->device_name[i]);
        QString type = QString::fromStdString(respond->device_type[i]);
        names.append(joint_name);
        types.append(type);
      }
      break;
    }
    }
    emitComParameter(QString::fromStdString(devices), names, types);
  }
}

void ComcenterDebug::enable(int flag) {
  auto stamp = node->now();
  rlfw_msgs::msg::JointCtrl msg;
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

void ComcenterDebug::resetQos(int his) {
  rclcpp::QoS control_qos(his);
  control_qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE);
  control_qos.history(RMW_QOS_POLICY_HISTORY_KEEP_ALL);
  rclcpp::QoS remote_qos(10);
  remote_qos.reliability(RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT);

  publisher_ = node->create_publisher<rlfw_msgs::msg::JointCtrl>(
      "rlfwJointCtrl", rclcpp::QoS(2));
  can_pub = node->create_publisher<rlfw_msgs::msg::CanMsg>("rlfwCANSend",
                                                           control_qos);
  serial_pub = node->create_publisher<rlfw_msgs::msg::SerialMsg>(
      "rlfwSerialSend", control_qos);

  sub_motor_ = node->create_subscription<rlfw_msgs::msg::Joint>(
      "rlfwJointBack", control_qos,
      std::bind(&ComcenterDebug::JointBack, this, std::placeholders::_1));
  sub_remote_ = node->create_subscription<rlfw_msgs::msg::Remote>(
      "rlfwRemoteBack", remote_qos,
      std::bind(&ComcenterDebug::RevRemote, this, std::placeholders::_1));
  sub_can_ = node->create_subscription<rlfw_msgs::msg::CanMsg>(
      "rlfwCANBack", control_qos,
      std::bind(&ComcenterDebug::RevCAN, this, std::placeholders::_1));
  sub_serial_ = node->create_subscription<rlfw_msgs::msg::SerialMsg>(
      "rlfwSerialBack", control_qos,
      std::bind(&ComcenterDebug::RevSerial, this, std::placeholders::_1));
}

void ComcenterDebug::sendCom(int32_t id, std::vector<uint8_t> data) {
  if (com_type.contains("can")) {
    rlfw_msgs::msg::CanMsg send_msg;
    send_msg.comname.set__stamp(node->now());
    send_msg.comname.set__frame_id(com_name);
    send_msg.id = id;
    send_msg.len = 8;
    send_msg.msgtype = can_type;
    send_msg.data = data;
    can_pub->publish(send_msg);
  } else if (com_type == "serial") {
    rlfw_msgs::msg::SerialMsg send_msg;
    send_msg.comname.set__stamp(node->now());
    send_msg.comname.set__frame_id(com_name);
    send_msg.data = data;
    serial_pub->publish(send_msg);
  }
}

void ComcenterDebug::changeCanIDType(int type) { can_type = type; }
void ComcenterDebug::changeComName(QString name) {
  com_name = name.toStdString();
}

void ComcenterDebug::RevCAN(const rlfw_msgs::msg::CanMsg::SharedPtr msg) {
  if (com_name == msg->comname.frame_id) {
    QByteArray data;
    for (auto it : msg->data)
      data.append(it);
    emitComData(msg->id, data);
  }
}

void ComcenterDebug::RevSerial(const rlfw_msgs::msg::SerialMsg::SharedPtr msg) {
  if (com_name == msg->comname.frame_id) {
    QByteArray data;
    for (auto it : msg->data)
      data.append(it);
    emitComData(0, data);
  }
}

void ComcenterDebug::RevRemote(const rlfw_msgs::msg::Remote::SharedPtr msg) {
  QStringList key;
  QVector<float> value;
  for (int i = 0; i < static_cast<int>(msg->key.size()) &&
                  i < static_cast<int>(msg->value.size());
       i++) {
    key.push_back(QString::fromStdString(msg->key[i]));
    value.push_back(msg->value[i]);
  }
  emitRemote(key, value);
}
void ComcenterDebug::run() { rclcpp::spin(node); }