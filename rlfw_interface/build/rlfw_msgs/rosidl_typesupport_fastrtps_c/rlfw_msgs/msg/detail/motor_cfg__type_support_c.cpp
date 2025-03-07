// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from rlfw_msgs:msg/MotorCfg.idl
// generated code does not contain a copyright notice
#include "rlfw_msgs/msg/detail/motor_cfg__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rlfw_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "rlfw_msgs/msg/detail/motor_cfg__struct.h"
#include "rlfw_msgs/msg/detail/motor_cfg__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // parameter_type
#include "rosidl_runtime_c/string_functions.h"  // parameter_type
#include "std_msgs/msg/detail/header__functions.h"  // joint

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rlfw_msgs
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rlfw_msgs
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_rlfw_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _MotorCfg__ros_msg_type = rlfw_msgs__msg__MotorCfg;

static bool _MotorCfg__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _MotorCfg__ros_msg_type * ros_message = static_cast<const _MotorCfg__ros_msg_type *>(untyped_ros_message);
  // Field name: joint
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->joint, cdr))
    {
      return false;
    }
  }

  // Field name: motor_id
  {
    cdr << ros_message->motor_id;
  }

  // Field name: parameter_type
  {
    const rosidl_runtime_c__String * str = &ros_message->parameter_type;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: parameter
  {
    cdr << ros_message->parameter;
  }

  return true;
}

static bool _MotorCfg__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _MotorCfg__ros_msg_type * ros_message = static_cast<_MotorCfg__ros_msg_type *>(untyped_ros_message);
  // Field name: joint
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->joint))
    {
      return false;
    }
  }

  // Field name: motor_id
  {
    cdr >> ros_message->motor_id;
  }

  // Field name: parameter_type
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->parameter_type.data) {
      rosidl_runtime_c__String__init(&ros_message->parameter_type);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->parameter_type,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'parameter_type'\n");
      return false;
    }
  }

  // Field name: parameter
  {
    cdr >> ros_message->parameter;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rlfw_msgs
size_t get_serialized_size_rlfw_msgs__msg__MotorCfg(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _MotorCfg__ros_msg_type * ros_message = static_cast<const _MotorCfg__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name joint

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->joint), current_alignment);
  // field.name motor_id
  {
    size_t item_size = sizeof(ros_message->motor_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name parameter_type
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->parameter_type.size + 1);
  // field.name parameter
  {
    size_t item_size = sizeof(ros_message->parameter);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _MotorCfg__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_rlfw_msgs__msg__MotorCfg(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rlfw_msgs
size_t max_serialized_size_rlfw_msgs__msg__MotorCfg(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: joint
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_std_msgs__msg__Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: motor_id
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: parameter_type
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: parameter
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = rlfw_msgs__msg__MotorCfg;
    is_plain =
      (
      offsetof(DataType, parameter) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _MotorCfg__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_rlfw_msgs__msg__MotorCfg(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_MotorCfg = {
  "rlfw_msgs::msg",
  "MotorCfg",
  _MotorCfg__cdr_serialize,
  _MotorCfg__cdr_deserialize,
  _MotorCfg__get_serialized_size,
  _MotorCfg__max_serialized_size
};

static rosidl_message_type_support_t _MotorCfg__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_MotorCfg,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rlfw_msgs, msg, MotorCfg)() {
  return &_MotorCfg__type_support;
}

#if defined(__cplusplus)
}
#endif
