// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rlfw_msgs:msg/SerialMsg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__STRUCT_H_
#define RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__STRUCT_H_

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

/// Struct defined in msg/SerialMsg in the package rlfw_msgs.
typedef struct rlfw_msgs__msg__SerialMsg
{
  std_msgs__msg__Header comname;
  rosidl_runtime_c__uint8__Sequence data;
} rlfw_msgs__msg__SerialMsg;

// Struct for a sequence of rlfw_msgs__msg__SerialMsg.
typedef struct rlfw_msgs__msg__SerialMsg__Sequence
{
  rlfw_msgs__msg__SerialMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__msg__SerialMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__STRUCT_H_
