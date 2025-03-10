// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rlfw_msgs:msg/Remote.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__REMOTE__BUILDER_HPP_
#define RLFW_MSGS__MSG__DETAIL__REMOTE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rlfw_msgs/msg/detail/remote__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rlfw_msgs
{

namespace msg
{

namespace builder
{

class Init_Remote_value
{
public:
  explicit Init_Remote_value(::rlfw_msgs::msg::Remote & msg)
  : msg_(msg)
  {}
  ::rlfw_msgs::msg::Remote value(::rlfw_msgs::msg::Remote::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::msg::Remote msg_;
};

class Init_Remote_key
{
public:
  explicit Init_Remote_key(::rlfw_msgs::msg::Remote & msg)
  : msg_(msg)
  {}
  Init_Remote_value key(::rlfw_msgs::msg::Remote::_key_type arg)
  {
    msg_.key = std::move(arg);
    return Init_Remote_value(msg_);
  }

private:
  ::rlfw_msgs::msg::Remote msg_;
};

class Init_Remote_remotename
{
public:
  Init_Remote_remotename()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Remote_key remotename(::rlfw_msgs::msg::Remote::_remotename_type arg)
  {
    msg_.remotename = std::move(arg);
    return Init_Remote_key(msg_);
  }

private:
  ::rlfw_msgs::msg::Remote msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::msg::Remote>()
{
  return rlfw_msgs::msg::builder::Init_Remote_remotename();
}

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__REMOTE__BUILDER_HPP_
