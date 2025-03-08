// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rlfw_msgs:msg/MotorCtrl.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__TRAITS_HPP_
#define RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rlfw_msgs/msg/detail/motor_ctrl__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'jointname'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rlfw_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorCtrl & msg,
  std::ostream & out)
{
  out << "{";
  // member: jointname
  {
    out << "jointname: ";
    to_flow_style_yaml(msg.jointname, out);
    out << ", ";
  }

  // member: torque
  {
    out << "torque: ";
    rosidl_generator_traits::value_to_yaml(msg.torque, out);
    out << ", ";
  }

  // member: angle
  {
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
    out << ", ";
  }

  // member: ang_vel
  {
    out << "ang_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.ang_vel, out);
    out << ", ";
  }

  // member: kp
  {
    out << "kp: ";
    rosidl_generator_traits::value_to_yaml(msg.kp, out);
    out << ", ";
  }

  // member: kd
  {
    out << "kd: ";
    rosidl_generator_traits::value_to_yaml(msg.kd, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorCtrl & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: jointname
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "jointname:\n";
    to_block_style_yaml(msg.jointname, out, indentation + 2);
  }

  // member: torque
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "torque: ";
    rosidl_generator_traits::value_to_yaml(msg.torque, out);
    out << "\n";
  }

  // member: angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
    out << "\n";
  }

  // member: ang_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ang_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.ang_vel, out);
    out << "\n";
  }

  // member: kp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "kp: ";
    rosidl_generator_traits::value_to_yaml(msg.kp, out);
    out << "\n";
  }

  // member: kd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "kd: ";
    rosidl_generator_traits::value_to_yaml(msg.kd, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorCtrl & msg, bool use_flow_style = false)
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
  const rlfw_msgs::msg::MotorCtrl & msg,
  std::ostream & out, size_t indentation = 0)
{
  rlfw_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rlfw_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const rlfw_msgs::msg::MotorCtrl & msg)
{
  return rlfw_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rlfw_msgs::msg::MotorCtrl>()
{
  return "rlfw_msgs::msg::MotorCtrl";
}

template<>
inline const char * name<rlfw_msgs::msg::MotorCtrl>()
{
  return "rlfw_msgs/msg/MotorCtrl";
}

template<>
struct has_fixed_size<rlfw_msgs::msg::MotorCtrl>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<rlfw_msgs::msg::MotorCtrl>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<rlfw_msgs::msg::MotorCtrl>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__TRAITS_HPP_
