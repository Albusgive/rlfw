// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rlfw_msgs:msg/CanMsg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__CAN_MSG__STRUCT_H_
#define RLFW_MSGS__MSG__DETAIL__CAN_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'comname'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/CanMsg in the package rlfw_msgs.
typedef struct rlfw_msgs__msg__CanMsg
{
  std_msgs__msg__Header comname;
  uint32_t id;
  uint8_t msgtype;
  uint8_t len;
  /// 长度限制为8
  rosidl_runtime_c__uint8__Sequence data;
} rlfw_msgs__msg__CanMsg;

// Struct for a sequence of rlfw_msgs__msg__CanMsg.
typedef struct rlfw_msgs__msg__CanMsg__Sequence
{
  rlfw_msgs__msg__CanMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__msg__CanMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RLFW_MSGS__MSG__DETAIL__CAN_MSG__STRUCT_H_
