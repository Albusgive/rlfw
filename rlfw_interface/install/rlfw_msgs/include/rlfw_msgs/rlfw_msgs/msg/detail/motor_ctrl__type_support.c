// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rlfw_msgs:msg/MotorCtrl.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rlfw_msgs/msg/detail/motor_ctrl__rosidl_typesupport_introspection_c.h"
#include "rlfw_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rlfw_msgs/msg/detail/motor_ctrl__functions.h"
#include "rlfw_msgs/msg/detail/motor_ctrl__struct.h"


// Include directives for member types
// Member `joint`
#include "std_msgs/msg/header.h"
// Member `joint`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `ctrl_type`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rlfw_msgs__msg__MotorCtrl__init(message_memory);
}

void rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_fini_function(void * message_memory)
{
  rlfw_msgs__msg__MotorCtrl__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_message_member_array[8] = {
  {
    "joint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__msg__MotorCtrl, joint),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__msg__MotorCtrl, motor_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ctrl_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__msg__MotorCtrl, ctrl_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "torque",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__msg__MotorCtrl, torque),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "angle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__msg__MotorCtrl, angle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ang_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__msg__MotorCtrl, ang_vel),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "kp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__msg__MotorCtrl, kp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "kd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__msg__MotorCtrl, kd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_message_members = {
  "rlfw_msgs__msg",  // message namespace
  "MotorCtrl",  // message name
  8,  // number of fields
  sizeof(rlfw_msgs__msg__MotorCtrl),
  rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_message_member_array,  // message members
  rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_init_function,  // function to initialize message memory (memory has to be allocated)
  rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_message_type_support_handle = {
  0,
  &rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rlfw_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rlfw_msgs, msg, MotorCtrl)() {
  rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_message_type_support_handle.typesupport_identifier) {
    rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rlfw_msgs__msg__MotorCtrl__rosidl_typesupport_introspection_c__MotorCtrl_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
