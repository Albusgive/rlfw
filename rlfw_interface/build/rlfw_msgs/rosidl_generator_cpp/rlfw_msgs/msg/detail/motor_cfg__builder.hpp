// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rlfw_msgs:msg/MotorCfg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__BUILDER_HPP_
#define RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rlfw_msgs/msg/detail/motor_cfg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rlfw_msgs
{

namespace msg
{

namespace builder
{

class Init_MotorCfg_parameter
{
public:
  explicit Init_MotorCfg_parameter(::rlfw_msgs::msg::MotorCfg & msg)
  : msg_(msg)
  {}
  ::rlfw_msgs::msg::MotorCfg parameter(::rlfw_msgs::msg::MotorCfg::_parameter_type arg)
  {
    msg_.parameter = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCfg msg_;
};

class Init_MotorCfg_parameter_type
{
public:
  explicit Init_MotorCfg_parameter_type(::rlfw_msgs::msg::MotorCfg & msg)
  : msg_(msg)
  {}
  Init_MotorCfg_parameter parameter_type(::rlfw_msgs::msg::MotorCfg::_parameter_type_type arg)
  {
    msg_.parameter_type = std::move(arg);
    return Init_MotorCfg_parameter(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCfg msg_;
};

class Init_MotorCfg_motor_id
{
public:
  explicit Init_MotorCfg_motor_id(::rlfw_msgs::msg::MotorCfg & msg)
  : msg_(msg)
  {}
  Init_MotorCfg_parameter_type motor_id(::rlfw_msgs::msg::MotorCfg::_motor_id_type arg)
  {
    msg_.motor_id = std::move(arg);
    return Init_MotorCfg_parameter_type(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCfg msg_;
};

class Init_MotorCfg_joint
{
public:
  Init_MotorCfg_joint()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorCfg_motor_id joint(::rlfw_msgs::msg::MotorCfg::_joint_type arg)
  {
    msg_.joint = std::move(arg);
    return Init_MotorCfg_motor_id(msg_);
  }

private:
  ::rlfw_msgs::msg::MotorCfg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::msg::MotorCfg>()
{
  return rlfw_msgs::msg::builder::Init_MotorCfg_joint();
}

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__BUILDER_HPP_
