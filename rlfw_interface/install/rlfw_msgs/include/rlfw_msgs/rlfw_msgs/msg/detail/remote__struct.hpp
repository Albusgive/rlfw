// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rlfw_msgs:msg/Remote.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__REMOTE__STRUCT_HPP_
#define RLFW_MSGS__MSG__DETAIL__REMOTE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'remotename'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rlfw_msgs__msg__Remote __attribute__((deprecated))
#else
# define DEPRECATED__rlfw_msgs__msg__Remote __declspec(deprecated)
#endif

namespace rlfw_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Remote_
{
  using Type = Remote_<ContainerAllocator>;

  explicit Remote_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : remotename(_init)
  {
    (void)_init;
  }

  explicit Remote_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : remotename(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _remotename_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _remotename_type remotename;
  using _key_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _key_type key;
  using _value_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _value_type value;

  // setters for named parameter idiom
  Type & set__remotename(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->remotename = _arg;
    return *this;
  }
  Type & set__key(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->key = _arg;
    return *this;
  }
  Type & set__value(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rlfw_msgs::msg::Remote_<ContainerAllocator> *;
  using ConstRawPtr =
    const rlfw_msgs::msg::Remote_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rlfw_msgs::msg::Remote_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rlfw_msgs::msg::Remote_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::Remote_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::Remote_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::Remote_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::Remote_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rlfw_msgs::msg::Remote_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rlfw_msgs::msg::Remote_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rlfw_msgs__msg__Remote
    std::shared_ptr<rlfw_msgs::msg::Remote_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rlfw_msgs__msg__Remote
    std::shared_ptr<rlfw_msgs::msg::Remote_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Remote_ & other) const
  {
    if (this->remotename != other.remotename) {
      return false;
    }
    if (this->key != other.key) {
      return false;
    }
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const Remote_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Remote_

// alias to use template instance with default allocator
using Remote =
  rlfw_msgs::msg::Remote_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__REMOTE__STRUCT_HPP_
