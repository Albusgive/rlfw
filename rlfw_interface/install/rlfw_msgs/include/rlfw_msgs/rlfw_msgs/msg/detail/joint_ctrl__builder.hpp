// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rlfw_msgs:msg/JointCtrl.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__JOINT_CTRL__BUILDER_HPP_
#define RLFW_MSGS__MSG__DETAIL__JOINT_CTRL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rlfw_msgs/msg/detail/joint_ctrl__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rlfw_msgs
{

namespace msg
{

namespace builder
{

class Init_JointCtrl_kd
{
public:
  explicit Init_JointCtrl_kd(::rlfw_msgs::msg::JointCtrl & msg)
  : msg_(msg)
  {}
  ::rlfw_msgs::msg::JointCtrl kd(::rlfw_msgs::msg::JointCtrl::_kd_type arg)
  {
    msg_.kd = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::msg::JointCtrl msg_;
};

class Init_JointCtrl_kp
{
public:
  explicit Init_JointCtrl_kp(::rlfw_msgs::msg::JointCtrl & msg)
  : msg_(msg)
  {}
  Init_JointCtrl_kd kp(::rlfw_msgs::msg::JointCtrl::_kp_type arg)
  {
    msg_.kp = std::move(arg);
    return Init_JointCtrl_kd(msg_);
  }

private:
  ::rlfw_msgs::msg::JointCtrl msg_;
};

class Init_JointCtrl_vel
{
public:
  explicit Init_JointCtrl_vel(::rlfw_msgs::msg::JointCtrl & msg)
  : msg_(msg)
  {}
  Init_JointCtrl_kp vel(::rlfw_msgs::msg::JointCtrl::_vel_type arg)
  {
    msg_.vel = std::move(arg);
    return Init_JointCtrl_kp(msg_);
  }

private:
  ::rlfw_msgs::msg::JointCtrl msg_;
};

class Init_JointCtrl_pos
{
public:
  explicit Init_JointCtrl_pos(::rlfw_msgs::msg::JointCtrl & msg)
  : msg_(msg)
  {}
  Init_JointCtrl_vel pos(::rlfw_msgs::msg::JointCtrl::_pos_type arg)
  {
    msg_.pos = std::move(arg);
    return Init_JointCtrl_vel(msg_);
  }

private:
  ::rlfw_msgs::msg::JointCtrl msg_;
};

class Init_JointCtrl_torque
{
public:
  explicit Init_JointCtrl_torque(::rlfw_msgs::msg::JointCtrl & msg)
  : msg_(msg)
  {}
  Init_JointCtrl_pos torque(::rlfw_msgs::msg::JointCtrl::_torque_type arg)
  {
    msg_.torque = std::move(arg);
    return Init_JointCtrl_pos(msg_);
  }

private:
  ::rlfw_msgs::msg::JointCtrl msg_;
};

class Init_JointCtrl_ctrl_type
{
public:
  explicit Init_JointCtrl_ctrl_type(::rlfw_msgs::msg::JointCtrl & msg)
  : msg_(msg)
  {}
  Init_JointCtrl_torque ctrl_type(::rlfw_msgs::msg::JointCtrl::_ctrl_type_type arg)
  {
    msg_.ctrl_type = std::move(arg);
    return Init_JointCtrl_torque(msg_);
  }

private:
  ::rlfw_msgs::msg::JointCtrl msg_;
};

class Init_JointCtrl_jointname
{
public:
  Init_JointCtrl_jointname()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointCtrl_ctrl_type jointname(::rlfw_msgs::msg::JointCtrl::_jointname_type arg)
  {
    msg_.jointname = std::move(arg);
    return Init_JointCtrl_ctrl_type(msg_);
  }

private:
  ::rlfw_msgs::msg::JointCtrl msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::msg::JointCtrl>()
{
  return rlfw_msgs::msg::builder::Init_JointCtrl_jointname();
}

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__JOINT_CTRL__BUILDER_HPP_
