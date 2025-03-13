#include "ComcenterDebug.h"
#include <qcontainerfwd.h>
#include <qobject.h>
ComcenterDebug::ComcenterDebug(const std::string &node_name) {
  int argc = 0;
  char **argv = NULL;
  rclcpp::init(argc, argv);
  node = std::make_shared<rclcpp::Node>(node_name);
  rclcpp::QoS control_qos(1);
  control_qos.reliability(RMW_QOS_POLICY_RELIABILITY_RELIABLE)
      .durability_volatile();
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
      std::bind(&ComcenterDebug::printRemoteData, this, std::placeholders::_1));
  client = node->create_client<rlfw_msgs::srv::ComParameter>(
      "CommunicationCenterSrv");

  // this->start();
}

void ComcenterDebug::JointBack(const rlfw_msgs::msg::Joint::SharedPtr msg) {
  switch (joint_data_type) {
  case JointDataType::pos: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id), msg->pos);
    break;
  }
  case JointDataType::vel: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id), msg->vel);
    break;
  }
  case JointDataType::torque: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id), msg->torque);
    break;
  }
  case JointDataType::current: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  msg->current);
    break;
  }
  case JointDataType::temperature: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  msg->temperature);
    break;
  }
  case JointDataType::number_laps: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id),
                  msg->number_laps);
    break;
  }
  case JointDataType::state: {
    emitJointData(QString::fromStdString(msg->jointname.frame_id), msg->state);
    break;
  }
  case JointDataType::None: {
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

void ComcenterDebug::printRemoteData(
    const rlfw_msgs::msg::Remote::SharedPtr msg) {
  std::cout << "RemoteData" << std::endl;
}

void ComcenterDebug::pub() {
  auto stamp = node->now();
  rlfw_msgs::msg::JointCtrl msg;
  msg.jointname.frame_id =
      "left_calf_joint"; // left_calf_joint left_wheel_joint
  msg.jointname.stamp = stamp;
  msg.ctrl_type = "MIT";
  msg.pos = 1.0;
  msg.kd = 0.7;
  // publisher_->publish(msg);

  msg.jointname.frame_id =
      "left_wheel_joint"; // left_calf_joint left_wheel_joint
  msg.jointname.stamp = stamp;
  msg.ctrl_type = "MIT";
  msg.vel = 1.0;
  msg.kd = 0.5;
  // publisher_->publish(msg);

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

void ComcenterDebug::pub2() {
  auto stamp = node->now();
  rlfw_msgs::msg::JointCtrl msg;
  msg.jointname.frame_id =
      "virtualmotorjoint"; // left_calf_joint left_wheel_joint
                           // virtualmotorjoint
  msg.jointname.stamp = stamp;
  msg.ctrl_type = "MIT";
  msg.pos = 1.0;
  msg.vel = 0.0;
  msg.kp = 10;
  msg.kd = 0.8;
  publisher_->publish(msg);

  msg.jointname.frame_id =
      "left_wheel_joint"; // left_calf_joint left_wheel_joint
  msg.jointname.stamp = stamp;
  msg.ctrl_type = "MIT";
  msg.pos = 0.0;
  msg.vel = 0;
  msg.kp = 0.0;
  msg.kd = 0.0;
  publisher_->publish(msg);
}

void ComcenterDebug::stop() {
  auto stamp = node->now();
  rlfw_msgs::msg::JointCtrl msg;
  msg.jointname.frame_id =
      "left_calf_joint"; // left_calf_joint left_wheel_joint
  msg.jointname.stamp = stamp;
  msg.ctrl_type = "MIT";
  msg.vel = 0.0;
  msg.kd = 0.0;
  publisher_->publish(msg);

  msg.jointname.frame_id =
      "left_wheel_joint"; // left_calf_joint left_wheel_joint
  msg.jointname.stamp = stamp;
  msg.ctrl_type = "MIT";
  msg.vel = 0.0;
  msg.kd = 0.0;
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
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS) {
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
    } else {
      std::cout << "no back" << std::endl;
    }
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

void ComcenterDebug::poorer_callback(
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

void ComcenterDebug::run() {
  rclcpp::WallRate loop_rate(100);
  while (rclcpp::ok()) {
    pub2();
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
}