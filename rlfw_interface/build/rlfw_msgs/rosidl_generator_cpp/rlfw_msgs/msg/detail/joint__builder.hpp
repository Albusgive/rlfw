// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rlfw_msgs:msg/Joint.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__JOINT__BUILDER_HPP_
#define RLFW_MSGS__MSG__DETAIL__JOINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rlfw_msgs/msg/detail/joint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rlfw_msgs
{

namespace msg
{

namespace builder
{

class Init_Joint_other
{
public:
  explicit Init_Joint_other(::rlfw_msgs::msg::Joint & msg)
  : msg_(msg)
  {}
  ::rlfw_msgs::msg::Joint other(::rlfw_msgs::msg::Joint::_other_type arg)
  {
    msg_.other = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::msg::Joint msg_;
};

class Init_Joint_state
{
public:
  explicit Init_Joint_state(::rlfw_msgs::msg::Joint & msg)
  : msg_(msg)
  {}
  Init_Joint_other state(::rlfw_msgs::msg::Joint::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_Joint_other(msg_);
  }

private:
  ::rlfw_msgs::msg::Joint msg_;
};

class Init_Joint_temperature
{
public:
  explicit Init_Joint_temperature(::rlfw_msgs::msg::Joint & msg)
  : msg_(msg)
  {}
  Init_Joint_state temperature(::rlfw_msgs::msg::Joint::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return Init_Joint_state(msg_);
  }

private:
  ::rlfw_msgs::msg::Joint msg_;
};

class Init_Joint_current
{
public:
  explicit Init_Joint_current(::rlfw_msgs::msg::Joint & msg)
  : msg_(msg)
  {}
  Init_Joint_temperature current(::rlfw_msgs::msg::Joint::_current_type arg)
  {
    msg_.current = std::move(arg);
    return Init_Joint_temperature(msg_);
  }

private:
  ::rlfw_msgs::msg::Joint msg_;
};

class Init_Joint_torque
{
public:
  explicit Init_Joint_torque(::rlfw_msgs::msg::Joint & msg)
  : msg_(msg)
  {}
  Init_Joint_current torque(::rlfw_msgs::msg::Joint::_torque_type arg)
  {
    msg_.torque = std::move(arg);
    return Init_Joint_current(msg_);
  }

private:
  ::rlfw_msgs::msg::Joint msg_;
};

class Init_Joint_vel
{
public:
  explicit Init_Joint_vel(::rlfw_msgs::msg::Joint & msg)
  : msg_(msg)
  {}
  Init_Joint_torque vel(::rlfw_msgs::msg::Joint::_vel_type arg)
  {
    msg_.vel = std::move(arg);
    return Init_Joint_torque(msg_);
  }

private:
  ::rlfw_msgs::msg::Joint msg_;
};

class Init_Joint_number_laps
{
public:
  explicit Init_Joint_number_laps(::rlfw_msgs::msg::Joint & msg)
  : msg_(msg)
  {}
  Init_Joint_vel number_laps(::rlfw_msgs::msg::Joint::_number_laps_type arg)
  {
    msg_.number_laps = std::move(arg);
    return Init_Joint_vel(msg_);
  }

private:
  ::rlfw_msgs::msg::Joint msg_;
};

class Init_Joint_pos
{
public:
  explicit Init_Joint_pos(::rlfw_msgs::msg::Joint & msg)
  : msg_(msg)
  {}
  Init_Joint_number_laps pos(::rlfw_msgs::msg::Joint::_pos_type arg)
  {
    msg_.pos = std::move(arg);
    return Init_Joint_number_laps(msg_);
  }

private:
  ::rlfw_msgs::msg::Joint msg_;
};

class Init_Joint_joint_id
{
public:
  explicit Init_Joint_joint_id(::rlfw_msgs::msg::Joint & msg)
  : msg_(msg)
  {}
  Init_Joint_pos joint_id(::rlfw_msgs::msg::Joint::_joint_id_type arg)
  {
    msg_.joint_id = std::move(arg);
    return Init_Joint_pos(msg_);
  }

private:
  ::rlfw_msgs::msg::Joint msg_;
};

class Init_Joint_jointname
{
public:
  Init_Joint_jointname()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Joint_joint_id jointname(::rlfw_msgs::msg::Joint::_jointname_type arg)
  {
    msg_.jointname = std::move(arg);
    return Init_Joint_joint_id(msg_);
  }

private:
  ::rlfw_msgs::msg::Joint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::msg::Joint>()
{
  return rlfw_msgs::msg::builder::Init_Joint_jointname();
}

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__JOINT__BUILDER_HPP_
