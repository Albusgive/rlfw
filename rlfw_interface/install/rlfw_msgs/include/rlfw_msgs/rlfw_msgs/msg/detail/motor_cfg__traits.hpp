// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rlfw_msgs:msg/MotorCfg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__TRAITS_HPP_
#define RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rlfw_msgs/msg/detail/motor_cfg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'joint'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rlfw_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorCfg & msg,
  std::ostream & out)
{
  out << "{";
  // member: joint
  {
    out << "joint: ";
    to_flow_style_yaml(msg.joint, out);
    out << ", ";
  }

  // member: motor_id
  {
    out << "motor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_id, out);
    out << ", ";
  }

  // member: parameter_type
  {
    out << "parameter_type: ";
    rosidl_generator_traits::value_to_yaml(msg.parameter_type, out);
    out << ", ";
  }

  // member: parameter
  {
    out << "parameter: ";
    rosidl_generator_traits::value_to_yaml(msg.parameter, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorCfg & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: joint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "joint:\n";
    to_block_style_yaml(msg.joint, out, indentation + 2);
  }

  // member: motor_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_id, out);
    out << "\n";
  }

  // member: parameter_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "parameter_type: ";
    rosidl_generator_traits::value_to_yaml(msg.parameter_type, out);
    out << "\n";
  }

  // member: parameter
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "parameter: ";
    rosidl_generator_traits::value_to_yaml(msg.parameter, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorCfg & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace rlfw_msgs

namespace rosidl_generator_traits
{

[[deprecated("use rlfw_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rlfw_msgs::msg::MotorCfg & msg,
  std::ostream & out, size_t indentation = 0)
{
  rlfw_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rlfw_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const rlfw_msgs::msg::MotorCfg & msg)
{
  return rlfw_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rlfw_msgs::msg::MotorCfg>()
{
  return "rlfw_msgs::msg::MotorCfg";
}

template<>
inline const char * name<rlfw_msgs::msg::MotorCfg>()
{
  return "rlfw_msgs/msg/MotorCfg";
}

template<>
struct has_fixed_size<rlfw_msgs::msg::MotorCfg>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rlfw_msgs::msg::MotorCfg>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rlfw_msgs::msg::MotorCfg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__TRAITS_HPP_
