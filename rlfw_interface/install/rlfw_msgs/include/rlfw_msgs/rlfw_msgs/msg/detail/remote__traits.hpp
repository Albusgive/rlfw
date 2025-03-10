// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rlfw_msgs:msg/Remote.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__REMOTE__TRAITS_HPP_
#define RLFW_MSGS__MSG__DETAIL__REMOTE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rlfw_msgs/msg/detail/remote__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'remotename'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rlfw_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Remote & msg,
  std::ostream & out)
{
  out << "{";
  // member: remotename
  {
    out << "remotename: ";
    to_flow_style_yaml(msg.remotename, out);
    out << ", ";
  }

  // member: key
  {
    if (msg.key.size() == 0) {
      out << "key: []";
    } else {
      out << "key: [";
      size_t pending_items = msg.key.size();
      for (auto item : msg.key) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: value
  {
    if (msg.value.size() == 0) {
      out << "value: []";
    } else {
      out << "value: [";
      size_t pending_items = msg.value.size();
      for (auto item : msg.value) {
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
  const Remote & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: remotename
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "remotename:\n";
    to_block_style_yaml(msg.remotename, out, indentation + 2);
  }

  // member: key
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.key.size() == 0) {
      out << "key: []\n";
    } else {
      out << "key:\n";
      for (auto item : msg.key) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.value.size() == 0) {
      out << "value: []\n";
    } else {
      out << "value:\n";
      for (auto item : msg.value) {
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

inline std::string to_yaml(const Remote & msg, bool use_flow_style = false)
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
  const rlfw_msgs::msg::Remote & msg,
  std::ostream & out, size_t indentation = 0)
{
  rlfw_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rlfw_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const rlfw_msgs::msg::Remote & msg)
{
  return rlfw_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rlfw_msgs::msg::Remote>()
{
  return "rlfw_msgs::msg::Remote";
}

template<>
inline const char * name<rlfw_msgs::msg::Remote>()
{
  return "rlfw_msgs/msg/Remote";
}

template<>
struct has_fixed_size<rlfw_msgs::msg::Remote>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rlfw_msgs::msg::Remote>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rlfw_msgs::msg::Remote>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RLFW_MSGS__MSG__DETAIL__REMOTE__TRAITS_HPP_
