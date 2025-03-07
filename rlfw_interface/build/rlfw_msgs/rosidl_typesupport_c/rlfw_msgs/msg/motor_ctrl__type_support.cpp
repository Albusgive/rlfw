// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from rlfw_msgs:msg/MotorCtrl.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rlfw_msgs/msg/detail/motor_ctrl__struct.h"
#include "rlfw_msgs/msg/detail/motor_ctrl__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace rlfw_msgs
{

namespace msg
{

namespace rosidl_typesupport_c
{

typedef struct _MotorCtrl_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MotorCtrl_type_support_ids_t;

static const _MotorCtrl_type_support_ids_t _MotorCtrl_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MotorCtrl_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MotorCtrl_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MotorCtrl_type_support_symbol_names_t _MotorCtrl_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rlfw_msgs, msg, MotorCtrl)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rlfw_msgs, msg, MotorCtrl)),
  }
};

typedef struct _MotorCtrl_type_support_data_t
{
  void * data[2];
} _MotorCtrl_type_support_data_t;

static _MotorCtrl_type_support_data_t _MotorCtrl_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MotorCtrl_message_typesupport_map = {
  2,
  "rlfw_msgs",
  &_MotorCtrl_message_typesupport_ids.typesupport_identifier[0],
  &_MotorCtrl_message_typesupport_symbol_names.symbol_name[0],
  &_MotorCtrl_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MotorCtrl_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MotorCtrl_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace msg

}  // namespace rlfw_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, rlfw_msgs, msg, MotorCtrl)() {
  return &::rlfw_msgs::msg::rosidl_typesupport_c::MotorCtrl_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
