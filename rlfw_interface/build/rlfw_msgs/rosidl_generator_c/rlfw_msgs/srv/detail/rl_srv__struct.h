// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rlfw_msgs:srv/RLSrv.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__SRV__DETAIL__RL_SRV__STRUCT_H_
#define RLFW_MSGS__SRV__DETAIL__RL_SRV__STRUCT_H_

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

/// Struct defined in srv/RLSrv in the package rlfw_msgs.
typedef struct rlfw_msgs__srv__RLSrv_Request
{
  rosidl_runtime_c__String request_communication_center_parameter;
} rlfw_msgs__srv__RLSrv_Request;

// Struct for a sequence of rlfw_msgs__srv__RLSrv_Request.
typedef struct rlfw_msgs__srv__RLSrv_Request__Sequence
{
  rlfw_msgs__srv__RLSrv_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__srv__RLSrv_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'com_name'
// Member 'com_type'
// Member 'joint_name'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/RLSrv in the package rlfw_msgs.
typedef struct rlfw_msgs__srv__RLSrv_Response
{
  rosidl_runtime_c__String__Sequence com_name;
  /// 通信类型
  rosidl_runtime_c__String__Sequence com_type;
  /// 关节名
  rosidl_runtime_c__String__Sequence joint_name;
} rlfw_msgs__srv__RLSrv_Response;

// Struct for a sequence of rlfw_msgs__srv__RLSrv_Response.
typedef struct rlfw_msgs__srv__RLSrv_Response__Sequence
{
  rlfw_msgs__srv__RLSrv_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__srv__RLSrv_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RLFW_MSGS__SRV__DETAIL__RL_SRV__STRUCT_H_
