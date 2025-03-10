// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rlfw_msgs:msg/SerialMsg.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rlfw_msgs/msg/detail/serial_msg__rosidl_typesupport_introspection_c.h"
#include "rlfw_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rlfw_msgs/msg/detail/serial_msg__functions.h"
#include "rlfw_msgs/msg/detail/serial_msg__struct.h"


// Include directives for member types
// Member `comname`
#include "std_msgs/msg/header.h"
// Member `comname`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rlfw_msgs__msg__SerialMsg__init(message_memory);
}

void rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_fini_function(void * message_memory)
{
  rlfw_msgs__msg__SerialMsg__fini(message_memory);
}

size_t rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__size_function__SerialMsg__data(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return member->size;
}

const void * rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__get_const_function__SerialMsg__data(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__get_function__SerialMsg__data(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__fetch_function__SerialMsg__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__get_const_function__SerialMsg__data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__assign_function__SerialMsg__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__get_function__SerialMsg__data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

bool rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__resize_function__SerialMsg__data(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  rosidl_runtime_c__uint8__Sequence__fini(member);
  return rosidl_runtime_c__uint8__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_message_member_array[2] = {
  {
    "comname",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__msg__SerialMsg, comname),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__msg__SerialMsg, data),  // bytes offset in struct
    NULL,  // default value
    rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__size_function__SerialMsg__data,  // size() function pointer
    rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__get_const_function__SerialMsg__data,  // get_const(index) function pointer
    rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__get_function__SerialMsg__data,  // get(index) function pointer
    rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__fetch_function__SerialMsg__data,  // fetch(index, &value) function pointer
    rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__assign_function__SerialMsg__data,  // assign(index, value) function pointer
    rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__resize_function__SerialMsg__data  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_message_members = {
  "rlfw_msgs__msg",  // message namespace
  "SerialMsg",  // message name
  2,  // number of fields
  sizeof(rlfw_msgs__msg__SerialMsg),
  rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_message_member_array,  // message members
  rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_init_function,  // function to initialize message memory (memory has to be allocated)
  rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_message_type_support_handle = {
  0,
  &rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rlfw_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rlfw_msgs, msg, SerialMsg)() {
  rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_message_type_support_handle.typesupport_identifier) {
    rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rlfw_msgs__msg__SerialMsg__rosidl_typesupport_introspection_c__SerialMsg_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
