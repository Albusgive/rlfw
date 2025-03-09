// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rlfw_msgs:msg/CanMsg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__CAN_MSG__STRUCT_HPP_
#define RLFW_MSGS__MSG__DETAIL__CAN_MSG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'comname'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rlfw_msgs__msg__CanMsg __attribute__((deprecated))
#else
# define DEPRECATED__rlfw_msgs__msg__CanMsg __declspec(deprecated)
#endif

namespace rlfw_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CanMsg_
{
  using Type = CanMsg_<ContainerAllocator>;

  explicit CanMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : comname(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0ul;
      this->msgtype = 0;
      this->len = 0;
    }
  }

  explicit CanMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : comname(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0ul;
      this->msgtype = 0;
      this->len = 0;
    }
  }

  // field types and members
  using _comname_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _comname_type comname;
  using _id_type =
    uint32_t;
  _id_type id;
  using _msgtype_type =
    uint8_t;
  _msgtype_type msgtype;
  using _len_type =
    uint8_t;
  _len_type len;
  using _data_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__comname(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->comname = _arg;
    return *this;
  }
  Type & set__id(
    const uint32_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__msgtype(
    const uint8_t & _arg)
  {
    this->msgtype = _arg;
    return *this;
  }
  Type & set__len(
    const uint8_t & _arg)
  {
    this->len = _arg;
    return *this;
  }
  Type & set__data(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rlfw_msgs::msg::CanMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const rlfw_msgs::msg::CanMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rlfw_msgs::msg::CanMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rlfw_msgs::msg::CanMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::CanMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::CanMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::CanMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::CanMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rlfw_msgs::msg::CanMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rlfw_msgs::msg::CanMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rlfw_msgs__msg__CanMsg
    std::shared_ptr<rlfw_msgs::msg::CanMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rlfw_msgs__msg__CanMsg
    std::shared_ptr<rlfw_msgs::msg::CanMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CanMsg_ & other) const
  {
    if (this->comname != other.comname) {
      return false;
    }
    if (this->id != other.id) {
      return false;
    }
    if (this->msgtype != other.msgtype) {
      return false;
    }
    if (this->len != other.len) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const CanMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CanMsg_

// alias to use template instance with default allocator
using CanMsg =
  rlfw_msgs::msg::CanMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__CAN_MSG__STRUCT_HPP_
