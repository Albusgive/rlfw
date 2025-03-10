// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rlfw_msgs:srv/ComParameter.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__TRAITS_HPP_
#define RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rlfw_msgs/srv/detail/com_parameter__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rlfw_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const ComParameter_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: request_communication_center_parameter
  {
    out << "request_communication_center_parameter: ";
    rosidl_generator_traits::value_to_yaml(msg.request_communication_center_parameter, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ComParameter_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: request_communication_center_parameter
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "request_communication_center_parameter: ";
    rosidl_generator_traits::value_to_yaml(msg.request_communication_center_parameter, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ComParameter_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rlfw_msgs

namespace rosidl_generator_traits
{

[[deprecated("use rlfw_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rlfw_msgs::srv::ComParameter_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  rlfw_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rlfw_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const rlfw_msgs::srv::ComParameter_Request & msg)
{
  return rlfw_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rlfw_msgs::srv::ComParameter_Request>()
{
  return "rlfw_msgs::srv::ComParameter_Request";
}

template<>
inline const char * name<rlfw_msgs::srv::ComParameter_Request>()
{
  return "rlfw_msgs/srv/ComParameter_Request";
}

template<>
struct has_fixed_size<rlfw_msgs::srv::ComParameter_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rlfw_msgs::srv::ComParameter_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rlfw_msgs::srv::ComParameter_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rlfw_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const ComParameter_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: device_name
  {
    if (msg.device_name.size() == 0) {
      out << "device_name: []";
    } else {
      out << "device_name: [";
      size_t pending_items = msg.device_name.size();
      for (auto item : msg.device_name) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: device_type
  {
    if (msg.device_type.size() == 0) {
      out << "device_type: []";
    } else {
      out << "device_type: [";
      size_t pending_items = msg.device_type.size();
      for (auto item : msg.device_type) {
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
  const ComParameter_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: device_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.device_name.size() == 0) {
      out << "device_name: []\n";
    } else {
      out << "device_name:\n";
      for (auto item : msg.device_name) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: device_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.device_type.size() == 0) {
      out << "device_type: []\n";
    } else {
      out << "device_type:\n";
      for (auto item : msg.device_type) {
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

inline std::string to_yaml(const ComParameter_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rlfw_msgs

namespace rosidl_generator_traits
{

[[deprecated("use rlfw_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rlfw_msgs::srv::ComParameter_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  rlfw_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rlfw_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const rlfw_msgs::srv::ComParameter_Response & msg)
{
  return rlfw_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rlfw_msgs::srv::ComParameter_Response>()
{
  return "rlfw_msgs::srv::ComParameter_Response";
}

template<>
inline const char * name<rlfw_msgs::srv::ComParameter_Response>()
{
  return "rlfw_msgs/srv/ComParameter_Response";
}

template<>
struct has_fixed_size<rlfw_msgs::srv::ComParameter_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rlfw_msgs::srv::ComParameter_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rlfw_msgs::srv::ComParameter_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rlfw_msgs::srv::ComParameter>()
{
  return "rlfw_msgs::srv::ComParameter";
}

template<>
inline const char * name<rlfw_msgs::srv::ComParameter>()
{
  return "rlfw_msgs/srv/ComParameter";
}

template<>
struct has_fixed_size<rlfw_msgs::srv::ComParameter>
  : std::integral_constant<
    bool,
    has_fixed_size<rlfw_msgs::srv::ComParameter_Request>::value &&
    has_fixed_size<rlfw_msgs::srv::ComParameter_Response>::value
  >
{
};

template<>
struct has_bounded_size<rlfw_msgs::srv::ComParameter>
  : std::integral_constant<
    bool,
    has_bounded_size<rlfw_msgs::srv::ComParameter_Request>::value &&
    has_bounded_size<rlfw_msgs::srv::ComParameter_Response>::value
  >
{
};

template<>
struct is_service<rlfw_msgs::srv::ComParameter>
  : std::true_type
{
};

template<>
struct is_service_request<rlfw_msgs::srv::ComParameter_Request>
  : std::true_type
{
};

template<>
struct is_service_response<rlfw_msgs::srv::ComParameter_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__TRAITS_HPP_
