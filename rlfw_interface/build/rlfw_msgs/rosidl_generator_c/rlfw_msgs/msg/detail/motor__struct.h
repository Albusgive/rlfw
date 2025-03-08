// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rlfw_msgs:msg/Motor.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR__STRUCT_H_
#define RLFW_MSGS__MSG__DETAIL__MOTOR__STRUCT_H_

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

/// Struct defined in msg/Motor in the package rlfw_msgs.
typedef struct rlfw_msgs__msg__Motor
{
  std_msgs__msg__Header jointname;
  int8_t motor_id;
  /// angle
  float angle;
  /// 圈数
  float number_laps;
  /// speed
  float ang_vel;
  /// 电机扭矩
  float torque;
  /// 电流
  float current;
  /// 电机温度
  float temperature;
  /// 电机状态
  int8_t state;
} rlfw_msgs__msg__Motor;

// Struct for a sequence of rlfw_msgs__msg__Motor.
typedef struct rlfw_msgs__msg__Motor__Sequence
{
  rlfw_msgs__msg__Motor * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__msg__Motor__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR__STRUCT_H_
