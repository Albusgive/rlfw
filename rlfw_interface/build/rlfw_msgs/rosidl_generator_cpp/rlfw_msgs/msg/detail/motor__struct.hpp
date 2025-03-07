// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rlfw_msgs:msg/Motor.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR__STRUCT_HPP_
#define RLFW_MSGS__MSG__DETAIL__MOTOR__STRUCT_HPP_

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
# define DEPRECATED__rlfw_msgs__msg__Motor __attribute__((deprecated))
#else
# define DEPRECATED__rlfw_msgs__msg__Motor __declspec(deprecated)
#endif

namespace rlfw_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Motor_
{
  using Type = Motor_<ContainerAllocator>;

  explicit Motor_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : joint(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->motor_id = 0;
      this->angle = 0.0f;
      this->number_laps = 0.0f;
      this->ang_vel = 0.0f;
      this->torque = 0.0f;
      this->current = 0.0f;
      this->temperature = 0.0f;
      this->state = 0;
    }
  }

  explicit Motor_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : joint(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->motor_id = 0;
      this->angle = 0.0f;
      this->number_laps = 0.0f;
      this->ang_vel = 0.0f;
      this->torque = 0.0f;
      this->current = 0.0f;
      this->temperature = 0.0f;
      this->state = 0;
    }
  }

  // field types and members
  using _joint_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _joint_type joint;
  using _motor_id_type =
    int8_t;
  _motor_id_type motor_id;
  using _angle_type =
    float;
  _angle_type angle;
  using _number_laps_type =
    float;
  _number_laps_type number_laps;
  using _ang_vel_type =
    float;
  _ang_vel_type ang_vel;
  using _torque_type =
    float;
  _torque_type torque;
  using _current_type =
    float;
  _current_type current;
  using _temperature_type =
    float;
  _temperature_type temperature;
  using _state_type =
    int8_t;
  _state_type state;

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
  Type & set__angle(
    const float & _arg)
  {
    this->angle = _arg;
    return *this;
  }
  Type & set__number_laps(
    const float & _arg)
  {
    this->number_laps = _arg;
    return *this;
  }
  Type & set__ang_vel(
    const float & _arg)
  {
    this->ang_vel = _arg;
    return *this;
  }
  Type & set__torque(
    const float & _arg)
  {
    this->torque = _arg;
    return *this;
  }
  Type & set__current(
    const float & _arg)
  {
    this->current = _arg;
    return *this;
  }
  Type & set__temperature(
    const float & _arg)
  {
    this->temperature = _arg;
    return *this;
  }
  Type & set__state(
    const int8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rlfw_msgs::msg::Motor_<ContainerAllocator> *;
  using ConstRawPtr =
    const rlfw_msgs::msg::Motor_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rlfw_msgs::msg::Motor_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rlfw_msgs::msg::Motor_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::Motor_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::Motor_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::msg::Motor_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::msg::Motor_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rlfw_msgs::msg::Motor_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rlfw_msgs::msg::Motor_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rlfw_msgs__msg__Motor
    std::shared_ptr<rlfw_msgs::msg::Motor_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rlfw_msgs__msg__Motor
    std::shared_ptr<rlfw_msgs::msg::Motor_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Motor_ & other) const
  {
    if (this->joint != other.joint) {
      return false;
    }
    if (this->motor_id != other.motor_id) {
      return false;
    }
    if (this->angle != other.angle) {
      return false;
    }
    if (this->number_laps != other.number_laps) {
      return false;
    }
    if (this->ang_vel != other.ang_vel) {
      return false;
    }
    if (this->torque != other.torque) {
      return false;
    }
    if (this->current != other.current) {
      return false;
    }
    if (this->temperature != other.temperature) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    return true;
  }
  bool operator!=(const Motor_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Motor_

// alias to use template instance with default allocator
using Motor =
  rlfw_msgs::msg::Motor_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR__STRUCT_HPP_
