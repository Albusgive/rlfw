// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rlfw_msgs:msg/MotorCfg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__STRUCT_HPP_
#define RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'joint'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rlfw_msgs__msg__MotorCfg __attribute__((deprecated))
#else
# define DEPRECATED__rlfw_msgs__msg__MotorCfg __declspec(deprecated)
#endif

namespace rlfw_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorCfg_
{
  using Type = MotorCfg_<ContainerAllocator>;

  explicit MotorCfg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : joint(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->motor_id = 0;
      this->parameter_type = "";
      this->parameter = 0.0f;
    }
  }

  explicit MotorCfg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : joint(_alloc, _init),
    parameter_type(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->motor_id = 0;
      this->parameter_type = "";
      this->parameter = 0.0f;
    }
  }

  // field types and members
  using _joint_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _joint_type joint;
  using _motor_id_type =
    int8_t;
  _motor_id_type motor_id;
  using _parameter_type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _parameter_type_type parameter_type;
  using _parameter_type =
    float;
  _parameter_type parameter;

  // setters for named parameter idiom
  Type & set__joint(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->joint = _arg;
    return *this;
  }
  Type & set__motor_id(
    const int8_t & _arg)
  {
    this->motor_id = _arg;
    return *this;
  }
  Type & set__parameter_type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->parameter_type = _arg;
    return *this;
  }
  Type & set__parameter(
    const float & _arg)
  {
    this->parameter = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rlfw_msgs::msg::MotorCfg_<ContainerAllocator> *;
  using ConstRawPtr =
    const rlfw_msgs::msg::MotorCfg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rlfw_msgs::msg::MotorCfg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rlfw_msgs::msg::MotorCfg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::MotorCfg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::MotorCfg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::MotorCfg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::MotorCfg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rlfw_msgs::msg::MotorCfg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rlfw_msgs::msg::MotorCfg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rlfw_msgs__msg__MotorCfg
    std::shared_ptr<rlfw_msgs::msg::MotorCfg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rlfw_msgs__msg__MotorCfg
    std::shared_ptr<rlfw_msgs::msg::MotorCfg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorCfg_ & other) const
  {
    if (this->joint != other.joint) {
      return false;
    }
    if (this->motor_id != other.motor_id) {
      return false;
    }
    if (this->parameter_type != other.parameter_type) {
      return false;
    }
    if (this->parameter != other.parameter) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorCfg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorCfg_

// alias to use template instance with default allocator
using MotorCfg =
  rlfw_msgs::msg::MotorCfg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__STRUCT_HPP_
