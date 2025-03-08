// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rlfw_msgs:msg/MotorCtrl.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__STRUCT_H_
#define RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'jointname'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/MotorCtrl in the package rlfw_msgs.
/**
  * 需要jointname 剩下的需要什么发什么
 */
typedef struct rlfw_msgs__msg__MotorCtrl
{
  std_msgs__msg__Header jointname;
  /// 扭矩
  float torque;
  /// 位置
  float angle;
  /// 角速度
  float ang_vel;
  float kp;
  float kd;
} rlfw_msgs__msg__MotorCtrl;

// Struct for a sequence of rlfw_msgs__msg__MotorCtrl.
typedef struct rlfw_msgs__msg__MotorCtrl__Sequence
{
  rlfw_msgs__msg__MotorCtrl * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__msg__MotorCtrl__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR_CTRL__STRUCT_H_
