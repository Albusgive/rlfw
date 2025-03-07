// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rlfw_msgs:msg/MotorCtrl.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__BUILDER_HPP_
#define RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rlfw_msgs/msg/detail/motor_ctrl__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rlfw_msgs
{

namespace msg
{

namespace builder
{

class Init_MotorCtrl_kd
{
public:
  explicit Init_MotorCtrl_kd(::rlfw_msgs::msg::MotorCtrl & msg)
  : msg_(msg)
  {}
  ::rlfw_msgs::msg::MotorCtrl kd(::rlfw_msgs::msg::MotorCtrl::_kd_type arg)
  {
    msg_.kd = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCtrl msg_;
};

class Init_MotorCtrl_kp
{
public:
  explicit Init_MotorCtrl_kp(::rlfw_msgs::msg::MotorCtrl & msg)
  : msg_(msg)
  {}
  Init_MotorCtrl_kd kp(::rlfw_msgs::msg::MotorCtrl::_kp_type arg)
  {
    msg_.kp = std::move(arg);
    return Init_MotorCtrl_kd(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCtrl msg_;
};

class Init_MotorCtrl_ang_vel
{
public:
  explicit Init_MotorCtrl_ang_vel(::rlfw_msgs::msg::MotorCtrl & msg)
  : msg_(msg)
  {}
  Init_MotorCtrl_kp ang_vel(::rlfw_msgs::msg::MotorCtrl::_ang_vel_type arg)
  {
    msg_.ang_vel = std::move(arg);
    return Init_MotorCtrl_kp(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCtrl msg_;
};

class Init_MotorCtrl_angle
{
public:
  explicit Init_MotorCtrl_angle(::rlfw_msgs::msg::MotorCtrl & msg)
  : msg_(msg)
  {}
  Init_MotorCtrl_ang_vel angle(::rlfw_msgs::msg::MotorCtrl::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return Init_MotorCtrl_ang_vel(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCtrl msg_;
};

class Init_MotorCtrl_torque
{
public:
  explicit Init_MotorCtrl_torque(::rlfw_msgs::msg::MotorCtrl & msg)
  : msg_(msg)
  {}
  Init_MotorCtrl_angle torque(::rlfw_msgs::msg::MotorCtrl::_torque_type arg)
  {
    msg_.torque = std::move(arg);
    return Init_MotorCtrl_angle(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCtrl msg_;
};

class Init_MotorCtrl_ctrl_type
{
public:
  explicit Init_MotorCtrl_ctrl_type(::rlfw_msgs::msg::MotorCtrl & msg)
  : msg_(msg)
  {}
  Init_MotorCtrl_torque ctrl_type(::rlfw_msgs::msg::MotorCtrl::_ctrl_type_type arg)
  {
    msg_.ctrl_type = std::move(arg);
    return Init_MotorCtrl_torque(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCtrl msg_;
};

class Init_MotorCtrl_motor_id
{
public:
  explicit Init_MotorCtrl_motor_id(::rlfw_msgs::msg::MotorCtrl & msg)
  : msg_(msg)
  {}
  Init_MotorCtrl_ctrl_type motor_id(::rlfw_msgs::msg::MotorCtrl::_motor_id_type arg)
  {
    msg_.motor_id = std::move(arg);
    return Init_MotorCtrl_ctrl_type(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCtrl msg_;
};

class Init_MotorCtrl_joint
{
public:
  Init_MotorCtrl_joint()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorCtrl_motor_id joint(::rlfw_msgs::msg::MotorCtrl::_joint_type arg)
  {
    msg_.joint = std::move(arg);
    return Init_MotorCtrl_motor_id(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCtrl msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::msg::MotorCtrl>()
{
  return rlfw_msgs::msg::builder::Init_MotorCtrl_joint();
}

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__BUILDER_HPP_
