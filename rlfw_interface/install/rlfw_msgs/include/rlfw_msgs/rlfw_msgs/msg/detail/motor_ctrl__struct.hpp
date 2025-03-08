// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rlfw_msgs:msg/MotorCtrl.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__STRUCT_HPP_
#define RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'jointname'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rlfw_msgs__msg__MotorCtrl __attribute__((deprecated))
#else
# define DEPRECATED__rlfw_msgs__msg__MotorCtrl __declspec(deprecated)
#endif

namespace rlfw_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorCtrl_
{
  using Type = MotorCtrl_<ContainerAllocator>;

  explicit MotorCtrl_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : jointname(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->torque = 0.0f;
      this->angle = 0.0f;
      this->ang_vel = 0.0f;
      this->kp = 0.0f;
      this->kd = 0.0f;
    }
  }

  explicit MotorCtrl_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : jointname(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->torque = 0.0f;
      this->angle = 0.0f;
      this->ang_vel = 0.0f;
      this->kp = 0.0f;
      this->kd = 0.0f;
    }
  }

  // field types and members
  using _jointname_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _jointname_type jointname;
  using _torque_type =
    float;
  _torque_type torque;
  using _angle_type =
    float;
  _angle_type angle;
  using _ang_vel_type =
    float;
  _ang_vel_type ang_vel;
  using _kp_type =
    float;
  _kp_type kp;
  using _kd_type =
    float;
  _kd_type kd;

  // setters for named parameter idiom
  Type & set__jointname(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->jointname = _arg;
    return *this;
  }
  Type & set__torque(
    const float & _arg)
  {
    this->torque = _arg;
    return *this;
  }
  Type & set__angle(
    const float & _arg)
  {
    this->angle = _arg;
    return *this;
  }
  Type & set__ang_vel(
    const float & _arg)
  {
    this->ang_vel = _arg;
    return *this;
  }
  Type & set__kp(
    const float & _arg)
  {
    this->kp = _arg;
    return *this;
  }
  Type & set__kd(
    const float & _arg)
  {
    this->kd = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rlfw_msgs::msg::MotorCtrl_<ContainerAllocator> *;
  using ConstRawPtr =
    const rlfw_msgs::msg::MotorCtrl_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rlfw_msgs::msg::MotorCtrl_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rlfw_msgs::msg::MotorCtrl_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::MotorCtrl_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::MotorCtrl_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::MotorCtrl_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::MotorCtrl_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rlfw_msgs::msg::MotorCtrl_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rlfw_msgs::msg::MotorCtrl_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rlfw_msgs__msg__MotorCtrl
    std::shared_ptr<rlfw_msgs::msg::MotorCtrl_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rlfw_msgs__msg__MotorCtrl
    std::shared_ptr<rlfw_msgs::msg::MotorCtrl_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorCtrl_ & other) const
  {
    if (this->jointname != other.jointname) {
      return false;
    }
    if (this->torque != other.torque) {
      return false;
    }
    if (this->angle != other.angle) {
      return false;
    }
    if (this->ang_vel != other.ang_vel) {
      return false;
    }
    if (this->kp != other.kp) {
      return false;
    }
    if (this->kd != other.kd) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorCtrl_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorCtrl_

// alias to use template instance with default allocator
using MotorCtrl =
  rlfw_msgs::msg::MotorCtrl_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__STRUCT_HPP_
