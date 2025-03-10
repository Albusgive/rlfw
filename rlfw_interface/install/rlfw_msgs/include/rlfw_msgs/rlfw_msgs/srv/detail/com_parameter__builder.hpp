// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rlfw_msgs:srv/ComParameter.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__BUILDER_HPP_
#define RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rlfw_msgs/srv/detail/com_parameter__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rlfw_msgs
{

namespace srv
{

namespace builder
{

class Init_ComParameter_Request_request_communication_center_parameter
{
public:
  Init_ComParameter_Request_request_communication_center_parameter()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rlfw_msgs::srv::ComParameter_Request request_communication_center_parameter(::rlfw_msgs::srv::ComParameter_Request::_request_communication_center_parameter_type arg)
  {
    msg_.request_communication_center_parameter = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::srv::ComParameter_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::srv::ComParameter_Request>()
{
  return rlfw_msgs::srv::builder::Init_ComParameter_Request_request_communication_center_parameter();
}

}  // namespace rlfw_msgs


namespace rlfw_msgs
{

namespace srv
{

namespace builder
{

class Init_ComParameter_Response_device_type
{
public:
  explicit Init_ComParameter_Response_device_type(::rlfw_msgs::srv::ComParameter_Response & msg)
  : msg_(msg)
  {}
  ::rlfw_msgs::srv::ComParameter_Response device_type(::rlfw_msgs::srv::ComParameter_Response::_device_type_type arg)
  {
    msg_.device_type = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::srv::ComParameter_Response msg_;
};

class Init_ComParameter_Response_device_name
{
public:
  Init_ComParameter_Response_device_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ComParameter_Response_device_type device_name(::rlfw_msgs::srv::ComParameter_Response::_device_name_type arg)
  {
    msg_.device_name = std::move(arg);
    return Init_ComParameter_Response_device_type(msg_);
  }

private:
  ::rlfw_msgs::srv::ComParameter_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::srv::ComParameter_Response>()
{
  return rlfw_msgs::srv::builder::Init_ComParameter_Response_device_name();
}

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__BUILDER_HPP_
