// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rlfw_msgs:msg/CanMsg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__CAN_MSG__BUILDER_HPP_
#define RLFW_MSGS__MSG__DETAIL__CAN_MSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rlfw_msgs/msg/detail/can_msg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rlfw_msgs
{

namespace msg
{

namespace builder
{

class Init_CanMsg_data
{
public:
  explicit Init_CanMsg_data(::rlfw_msgs::msg::CanMsg & msg)
  : msg_(msg)
  {}
  ::rlfw_msgs::msg::CanMsg data(::rlfw_msgs::msg::CanMsg::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rlfw_msgs::msg::CanMsg msg_;
};

class Init_CanMsg_len
{
public:
  explicit Init_CanMsg_len(::rlfw_msgs::msg::CanMsg & msg)
  : msg_(msg)
  {}
  Init_CanMsg_data len(::rlfw_msgs::msg::CanMsg::_len_type arg)
  {
    msg_.len = std::move(arg);
    return Init_CanMsg_data(msg_);
  }

private:
  ::rlfw_msgs::msg::CanMsg msg_;
};

class Init_CanMsg_msgtype
{
public:
  explicit Init_CanMsg_msgtype(::rlfw_msgs::msg::CanMsg & msg)
  : msg_(msg)
  {}
  Init_CanMsg_len msgtype(::rlfw_msgs::msg::CanMsg::_msgtype_type arg)
  {
    msg_.msgtype = std::move(arg);
    return Init_CanMsg_len(msg_);
  }

private:
  ::rlfw_msgs::msg::CanMsg msg_;
};

class Init_CanMsg_id
{
public:
  explicit Init_CanMsg_id(::rlfw_msgs::msg::CanMsg & msg)
  : msg_(msg)
  {}
  Init_CanMsg_msgtype id(::rlfw_msgs::msg::CanMsg::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_CanMsg_msgtype(msg_);
  }

private:
  ::rlfw_msgs::msg::CanMsg msg_;
};

class Init_CanMsg_comname
{
public:
  Init_CanMsg_comname()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CanMsg_id comname(::rlfw_msgs::msg::CanMsg::_comname_type arg)
  {
    msg_.comname = std::move(arg);
    return Init_CanMsg_id(msg_);
  }

private:
  ::rlfw_msgs::msg::CanMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rlfw_msgs::msg::CanMsg>()
{
  return rlfw_msgs::msg::builder::Init_CanMsg_comname();
}

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__CAN_MSG__BUILDER_HPP_
