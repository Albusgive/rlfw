// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rlfw_msgs:msg/SerialMsg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__BUILDER_HPP_
#define RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rlfw_msgs/msg/detail/serial_msg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rlfw_msgs
{

namespace msg
{

namespace builder
{

class Init_SerialMsg_data
{
public:
  explicit Init_SerialMsg_data(::rlfw_msgs::msg::SerialMsg & msg)
  : msg_(msg)
  {}
  ::rlfw_msgs::msg::SerialMsg data(::rlfw_msgs::msg::SerialMsg::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::msg::SerialMsg msg_;
};

class Init_SerialMsg_comname
{
public:
  Init_SerialMsg_comname()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SerialMsg_data comname(::rlfw_msgs::msg::SerialMsg::_comname_type arg)
  {
    msg_.comname = std::move(arg);
    return Init_SerialMsg_data(msg_);
  }

private:
  ::rlfw_msgs::msg::SerialMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::msg::SerialMsg>()
{
  return rlfw_msgs::msg::builder::Init_SerialMsg_comname();
}

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__BUILDER_HPP_
