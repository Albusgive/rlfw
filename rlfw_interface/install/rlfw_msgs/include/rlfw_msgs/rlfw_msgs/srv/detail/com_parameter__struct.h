// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rlfw_msgs:srv/ComParameter.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__STRUCT_H_
#define RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'request_communication_center_parameter'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ComParameter in the package rlfw_msgs.
typedef struct rlfw_msgs__srv__ComParameter_Request
{
  rosidl_runtime_c__String request_communication_center_parameter;
} rlfw_msgs__srv__ComParameter_Request;

// Struct for a sequence of rlfw_msgs__srv__ComParameter_Request.
typedef struct rlfw_msgs__srv__ComParameter_Request__Sequence
{
  rlfw_msgs__srv__ComParameter_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__srv__ComParameter_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'device_name'
// Member 'device_type'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ComParameter in the package rlfw_msgs.
typedef struct rlfw_msgs__srv__ComParameter_Response
{
  rosidl_runtime_c__String__Sequence device_name;
  /// 通信类型
  rosidl_runtime_c__String__Sequence device_type;
} rlfw_msgs__srv__ComParameter_Response;

// Struct for a sequence of rlfw_msgs__srv__ComParameter_Response.
typedef struct rlfw_msgs__srv__ComParameter_Response__Sequence
{
  rlfw_msgs__srv__ComParameter_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__srv__ComParameter_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__STRUCT_H_
