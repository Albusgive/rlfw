// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rlfw_msgs:msg/MotorCfg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__STRUCT_H_
#define RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'joint'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'parameter_type'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/MotorCfg in the package rlfw_msgs.
typedef struct rlfw_msgs__msg__MotorCfg
{
  std_msgs__msg__Header joint;
  int8_t motor_id;
  /// PosKP , PosKD ,
  /// VelKP , VelKI ,
  /// TorqueKP , TorqueKI ,
  /// SafeTorque , SafePos , SafeVel
  rosidl_runtime_c__String parameter_type;
  float parameter;
} rlfw_msgs__msg__MotorCfg;

// Struct for a sequence of rlfw_msgs__msg__MotorCfg.
typedef struct rlfw_msgs__msg__MotorCfg__Sequence
{
  rlfw_msgs__msg__MotorCfg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rlfw_msgs__msg__MotorCfg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RLFW_MSGS__MSG__DETAIL__MOTOR_CFG__STRUCT_H_
