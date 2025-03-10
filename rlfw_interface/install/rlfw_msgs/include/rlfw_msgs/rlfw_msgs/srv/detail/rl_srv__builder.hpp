// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rlfw_msgs:srv/RLSrv.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__SRV__DETAIL__RL_SRV__BUILDER_HPP_
#define RLFW_MSGS__SRV__DETAIL__RL_SRV__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rlfw_msgs/srv/detail/rl_srv__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rlfw_msgs
{

namespace srv
{

namespace builder
{

class Init_RLSrv_Request_request_communication_center_parameter
{
public:
  Init_RLSrv_Request_request_communication_center_parameter()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rlfw_msgs::srv::RLSrv_Request request_communication_center_parameter(::rlfw_msgs::srv::RLSrv_Request::_request_communication_center_parameter_type arg)
  {
    msg_.request_communication_center_parameter = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::srv::RLSrv_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::srv::RLSrv_Request>()
{
  return rlfw_msgs::srv::builder::Init_RLSrv_Request_request_communication_center_parameter();
}

}  // namespace rlfw_msgs


namespace rlfw_msgs
{

namespace srv
{

namespace builder
{

class Init_RLSrv_Response_joint_name
{
public:
  explicit Init_RLSrv_Response_joint_name(::rlfw_msgs::srv::RLSrv_Response & msg)
  : msg_(msg)
  {}
  ::rlfw_msgs::srv::RLSrv_Response joint_name(::rlfw_msgs::srv::RLSrv_Response::_joint_name_type arg)
  {
    msg_.joint_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::srv::RLSrv_Response msg_;
};

class Init_RLSrv_Response_com_type
{
public:
  explicit Init_RLSrv_Response_com_type(::rlfw_msgs::srv::RLSrv_Response & msg)
  : msg_(msg)
  {}
  Init_RLSrv_Response_joint_name com_type(::rlfw_msgs::srv::RLSrv_Response::_com_type_type arg)
  {
    msg_.com_type = std::move(arg);
    return Init_RLSrv_Response_joint_name(msg_);
  }

private:
  ::rlfw_msgs::srv::RLSrv_Response msg_;
};

class Init_RLSrv_Response_com_name
{
public:
  Init_RLSrv_Response_com_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RLSrv_Response_com_type com_name(::rlfw_msgs::srv::RLSrv_Response::_com_name_type arg)
  {
    msg_.com_name = std::move(arg);
    return Init_RLSrv_Response_com_type(msg_);
  }

private:
  ::rlfw_msgs::srv::RLSrv_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::srv::RLSrv_Response>()
{
  return rlfw_msgs::srv::builder::Init_RLSrv_Response_com_name();
}

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__SRV__DETAIL__RL_SRV__BUILDER_HPP_
