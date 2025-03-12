// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rlfw_msgs:msg/Joint.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__JOINT__STRUCT_H_
#define RLFW_MSGS__MSG__DETAIL__JOINT__STRUCT_H_

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
// Member 'other'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/Joint in the package rlfw_msgs.
typedef struct rlfw_msgs__msg__Joint
{
  std_msgs__msg__Header jointname;
  int8_t joint_id;
  /// angle
  float pos;
  /// 圈数
  float number_laps;
  /// speed
  float vel;
  /// 电机扭矩或者力
  float torque;
  /// 电流
  float current;
  /// 温度
  float temperature;
  /// 关节状态
  int8_t state;
  /// 额外信息 虚拟关节的终端位置（ρ，θ）
  rosidl_runtime_c__float__Sequence other;
} rlfw_msgs__msg__Joint;

// Struct for a sequence of rlfw_msgs__msg__Joint.
typedef struct rlfw_msgs__msg__Joint__Sequence
{
  rlfw_msgs__msg__Joint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__msg__Joint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RLFW_MSGS__MSG__DETAIL__JOINT__STRUCT_H_
