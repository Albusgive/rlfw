// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rlfw_msgs:msg/Joint.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__JOINT__TRAITS_HPP_
#define RLFW_MSGS__MSG__DETAIL__JOINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rlfw_msgs/msg/detail/joint__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'jointname'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rlfw_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Joint & msg,
  std::ostream & out)
{
  out << "{";
  // member: jointname
  {
    out << "jointname: ";
    to_flow_style_yaml(msg.jointname, out);
    out << ", ";
  }

  // member: joint_id
  {
    out << "joint_id: ";
    rosidl_generator_traits::value_to_yaml(msg.joint_id, out);
    out << ", ";
  }

  // member: pos
  {
    out << "pos: ";
    rosidl_generator_traits::value_to_yaml(msg.pos, out);
    out << ", ";
  }

  // member: number_laps
  {
    out << "number_laps: ";
    rosidl_generator_traits::value_to_yaml(msg.number_laps, out);
    out << ", ";
  }

  // member: vel
  {
    out << "vel: ";
    rosidl_generator_traits::value_to_yaml(msg.vel, out);
    out << ", ";
  }

  // member: torque
  {
    out << "torque: ";
    rosidl_generator_traits::value_to_yaml(msg.torque, out);
    out << ", ";
  }

  // member: current
  {
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
    out << ", ";
  }

  // member: temperature
  {
    out << "temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.temperature, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: other
  {
    if (msg.other.size() == 0) {
      out << "other: []";
    } else {
      out << "other: [";
      size_t pending_items = msg.other.size();
      for (auto item : msg.other) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Joint & msg,
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

  // member: joint_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "joint_id: ";
    rosidl_generator_traits::value_to_yaml(msg.joint_id, out);
    out << "\n";
  }

  // member: pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pos: ";
    rosidl_generator_traits::value_to_yaml(msg.pos, out);
    out << "\n";
  }

  // member: number_laps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "number_laps: ";
    rosidl_generator_traits::value_to_yaml(msg.number_laps, out);
    out << "\n";
  }

  // member: vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vel: ";
    rosidl_generator_traits::value_to_yaml(msg.vel, out);
    out << "\n";
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

  // member: current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
    out << "\n";
  }

  // member: temperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.temperature, out);
    out << "\n";
  }

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }

  // member: other
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.other.size() == 0) {
      out << "other: []\n";
    } else {
      out << "other:\n";
      for (auto item : msg.other) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Joint & msg, bool use_flow_style = false)
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
  const rlfw_msgs::msg::Joint & msg,
  std::ostream & out, size_t indentation = 0)
{
  rlfw_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rlfw_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const rlfw_msgs::msg::Joint & msg)
{
  return rlfw_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rlfw_msgs::msg::Joint>()
{
  return "rlfw_msgs::msg::Joint";
}

template<>
inline const char * name<rlfw_msgs::msg::Joint>()
{
  return "rlfw_msgs/msg/Joint";
}

template<>
struct has_fixed_size<rlfw_msgs::msg::Joint>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rlfw_msgs::msg::Joint>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rlfw_msgs::msg::Joint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RLFW_MSGS__MSG__DETAIL__JOINT__TRAITS_HPP_
