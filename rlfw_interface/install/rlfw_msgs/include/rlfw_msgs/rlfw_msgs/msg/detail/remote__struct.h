// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rlfw_msgs:msg/Remote.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__REMOTE__STRUCT_H_
#define RLFW_MSGS__MSG__DETAIL__REMOTE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'remotename'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'key'
#include "rosidl_runtime_c/string.h"
// Member 'value'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/Remote in the package rlfw_msgs.
typedef struct rlfw_msgs__msg__Remote
{
  std_msgs__msg__Header remotename;
  /// 对应功能
  rosidl_runtime_c__String__Sequence key;
  /// 数值
  rosidl_runtime_c__float__Sequence value;
} rlfw_msgs__msg__Remote;

// Struct for a sequence of rlfw_msgs__msg__Remote.
typedef struct rlfw_msgs__msg__Remote__Sequence
{
  rlfw_msgs__msg__Remote * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__msg__Remote__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RLFW_MSGS__MSG__DETAIL__REMOTE__STRUCT_H_
