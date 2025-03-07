// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rlfw_msgs:msg/Motor.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR__BUILDER_HPP_
#define RLFW_MSGS__MSG__DETAIL__MOTOR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rlfw_msgs/msg/detail/motor__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rlfw_msgs
{

namespace msg
{

namespace builder
{

class Init_Motor_state
{
public:
  explicit Init_Motor_state(::rlfw_msgs::msg::Motor & msg)
  : msg_(msg)
  {}
  ::rlfw_msgs::msg::Motor state(::rlfw_msgs::msg::Motor::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::msg::Motor msg_;
};

class Init_Motor_temperature
{
public:
  explicit Init_Motor_temperature(::rlfw_msgs::msg::Motor & msg)
  : msg_(msg)
  {}
  Init_Motor_state temperature(::rlfw_msgs::msg::Motor::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return Init_Motor_state(msg_);
  }

private:
  ::rlfw_msgs::msg::Motor msg_;
};

class Init_Motor_current
{
public:
  explicit Init_Motor_current(::rlfw_msgs::msg::Motor & msg)
  : msg_(msg)
  {}
  Init_Motor_temperature current(::rlfw_msgs::msg::Motor::_current_type arg)
  {
    msg_.current = std::move(arg);
    return Init_Motor_temperature(msg_);
  }

private:
  ::rlfw_msgs::msg::Motor msg_;
};

class Init_Motor_torque
{
public:
  explicit Init_Motor_torque(::rlfw_msgs::msg::Motor & msg)
  : msg_(msg)
  {}
  Init_Motor_current torque(::rlfw_msgs::msg::Motor::_torque_type arg)
  {
    msg_.torque = std::move(arg);
    return Init_Motor_current(msg_);
  }

private:
  ::rlfw_msgs::msg::Motor msg_;
};

class Init_Motor_ang_vel
{
public:
  explicit Init_Motor_ang_vel(::rlfw_msgs::msg::Motor & msg)
  : msg_(msg)
  {}
  Init_Motor_torque ang_vel(::rlfw_msgs::msg::Motor::_ang_vel_type arg)
  {
    msg_.ang_vel = std::move(arg);
    return Init_Motor_torque(msg_);
  }

private:
  ::rlfw_msgs::msg::Motor msg_;
};

class Init_Motor_number_laps
{
public:
  explicit Init_Motor_number_laps(::rlfw_msgs::msg::Motor & msg)
  : msg_(msg)
  {}
  Init_Motor_ang_vel number_laps(::rlfw_msgs::msg::Motor::_number_laps_type arg)
  {
    msg_.number_laps = std::move(arg);
    return Init_Motor_ang_vel(msg_);
  }

private:
  ::rlfw_msgs::msg::Motor msg_;
};

class Init_Motor_angle
{
public:
  explicit Init_Motor_angle(::rlfw_msgs::msg::Motor & msg)
  : msg_(msg)
  {}
  Init_Motor_number_laps angle(::rlfw_msgs::msg::Motor::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return Init_Motor_number_laps(msg_);
  }

private:
  ::rlfw_msgs::msg::Motor msg_;
};

class Init_Motor_motor_id
{
public:
  explicit Init_Motor_motor_id(::rlfw_msgs::msg::Motor & msg)
  : msg_(msg)
  {}
  Init_Motor_angle motor_id(::rlfw_msgs::msg::Motor::_motor_id_type arg)
  {
    msg_.motor_id = std::move(arg);
    return Init_Motor_angle(msg_);
  }

private:
  ::rlfw_msgs::msg::Motor msg_;
};

class Init_Motor_joint
{
public:
  Init_Motor_joint()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Motor_motor_id joint(::rlfw_msgs::msg::Motor::_joint_type arg)
  {
    msg_.joint = std::move(arg);
    return Init_Motor_motor_id(msg_);
  }

private:
  ::rlfw_msgs::msg::Motor msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::msg::Motor>()
{
  return rlfw_msgs::msg::builder::Init_Motor_joint();
}

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR__BUILDER_HPP_
