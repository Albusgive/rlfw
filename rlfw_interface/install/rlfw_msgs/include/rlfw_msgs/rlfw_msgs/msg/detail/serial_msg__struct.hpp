// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rlfw_msgs:msg/SerialMsg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__STRUCT_HPP_
#define RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__STRUCT_HPP_

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
# define DEPRECATED__rlfw_msgs__msg__SerialMsg __attribute__((deprecated))
#else
# define DEPRECATED__rlfw_msgs__msg__SerialMsg __declspec(deprecated)
#endif

namespace rlfw_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SerialMsg_
{
  using Type = SerialMsg_<ContainerAllocator>;

  explicit SerialMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : comname(_init)
  {
    (void)_init;
  }

  explicit SerialMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : comname(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _comname_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _comname_type comname;
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
  Type & set__data(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rlfw_msgs::msg::SerialMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const rlfw_msgs::msg::SerialMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rlfw_msgs::msg::SerialMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rlfw_msgs::msg::SerialMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::SerialMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::SerialMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::SerialMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::SerialMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rlfw_msgs::msg::SerialMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rlfw_msgs::msg::SerialMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rlfw_msgs__msg__SerialMsg
    std::shared_ptr<rlfw_msgs::msg::SerialMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rlfw_msgs__msg__SerialMsg
    std::shared_ptr<rlfw_msgs::msg::SerialMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SerialMsg_ & other) const
  {
    if (this->comname != other.comname) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const SerialMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SerialMsg_

// alias to use template instance with default allocator
using SerialMsg =
  rlfw_msgs::msg::SerialMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__STRUCT_HPP_
