// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rlfw_msgs:srv/RLSrv.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__SRV__DETAIL__RL_SRV__TRAITS_HPP_
#define RLFW_MSGS__SRV__DETAIL__RL_SRV__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rlfw_msgs/srv/detail/rl_srv__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rlfw_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const RLSrv_Request & msg,
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
  const RLSrv_Request & msg,
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

inline std::string to_yaml(const RLSrv_Request & msg, bool use_flow_style = false)
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
  const rlfw_msgs::srv::RLSrv_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  rlfw_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rlfw_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const rlfw_msgs::srv::RLSrv_Request & msg)
{
  return rlfw_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rlfw_msgs::srv::RLSrv_Request>()
{
  return "rlfw_msgs::srv::RLSrv_Request";
}

template<>
inline const char * name<rlfw_msgs::srv::RLSrv_Request>()
{
  return "rlfw_msgs/srv/RLSrv_Request";
}

template<>
struct has_fixed_size<rlfw_msgs::srv::RLSrv_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rlfw_msgs::srv::RLSrv_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rlfw_msgs::srv::RLSrv_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rlfw_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const RLSrv_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: com_name
  {
    if (msg.com_name.size() == 0) {
      out << "com_name: []";
    } else {
      out << "com_name: [";
      size_t pending_items = msg.com_name.size();
      for (auto item : msg.com_name) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: com_type
  {
    if (msg.com_type.size() == 0) {
      out << "com_type: []";
    } else {
      out << "com_type: [";
      size_t pending_items = msg.com_type.size();
      for (auto item : msg.com_type) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: joint_name
  {
    if (msg.joint_name.size() == 0) {
      out << "joint_name: []";
    } else {
      out << "joint_name: [";
      size_t pending_items = msg.joint_name.size();
      for (auto item : msg.joint_name) {
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
  const RLSrv_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: com_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.com_name.size() == 0) {
      out << "com_name: []\n";
    } else {
      out << "com_name:\n";
      for (auto item : msg.com_name) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: com_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.com_type.size() == 0) {
      out << "com_type: []\n";
    } else {
      out << "com_type:\n";
      for (auto item : msg.com_type) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: joint_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.joint_name.size() == 0) {
      out << "joint_name: []\n";
    } else {
      out << "joint_name:\n";
      for (auto item : msg.joint_name) {
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

inline std::string to_yaml(const RLSrv_Response & msg, bool use_flow_style = false)
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
  const rlfw_msgs::srv::RLSrv_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  rlfw_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rlfw_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const rlfw_msgs::srv::RLSrv_Response & msg)
{
  return rlfw_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rlfw_msgs::srv::RLSrv_Response>()
{
  return "rlfw_msgs::srv::RLSrv_Response";
}

template<>
inline const char * name<rlfw_msgs::srv::RLSrv_Response>()
{
  return "rlfw_msgs/srv/RLSrv_Response";
}

template<>
struct has_fixed_size<rlfw_msgs::srv::RLSrv_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rlfw_msgs::srv::RLSrv_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rlfw_msgs::srv::RLSrv_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rlfw_msgs::srv::RLSrv>()
{
  return "rlfw_msgs::srv::RLSrv";
}

template<>
inline const char * name<rlfw_msgs::srv::RLSrv>()
{
  return "rlfw_msgs/srv/RLSrv";
}

template<>
struct has_fixed_size<rlfw_msgs::srv::RLSrv>
  : std::integral_constant<
    bool,
    has_fixed_size<rlfw_msgs::srv::RLSrv_Request>::value &&
    has_fixed_size<rlfw_msgs::srv::RLSrv_Response>::value
  >
{
};

template<>
struct has_bounded_size<rlfw_msgs::srv::RLSrv>
  : std::integral_constant<
    bool,
    has_bounded_size<rlfw_msgs::srv::RLSrv_Request>::value &&
    has_bounded_size<rlfw_msgs::srv::RLSrv_Response>::value
  >
{
};

template<>
struct is_service<rlfw_msgs::srv::RLSrv>
  : std::true_type
{
};

template<>
struct is_service_request<rlfw_msgs::srv::RLSrv_Request>
  : std::true_type
{
};

template<>
struct is_service_response<rlfw_msgs::srv::RLSrv_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // RLFW_MSGS__SRV__DETAIL__RL_SRV__TRAITS_HPP_
