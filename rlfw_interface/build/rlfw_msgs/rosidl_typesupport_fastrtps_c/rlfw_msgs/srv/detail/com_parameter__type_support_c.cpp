// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from rlfw_msgs:srv/ComParameter.idl
// generated code does not contain a copyright notice
#include "rlfw_msgs/srv/detail/com_parameter__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rlfw_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "rlfw_msgs/srv/detail/com_parameter__struct.h"
#include "rlfw_msgs/srv/detail/com_parameter__functions.h"
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

#include "rosidl_runtime_c/string.h"  // request_communication_center_parameter
#include "rosidl_runtime_c/string_functions.h"  // request_communication_center_parameter

// forward declare type support functions


using _ComParameter_Request__ros_msg_type = rlfw_msgs__srv__ComParameter_Request;

static bool _ComParameter_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ComParameter_Request__ros_msg_type * ros_message = static_cast<const _ComParameter_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: request_communication_center_parameter
  {
    const rosidl_runtime_c__String * str = &ros_message->request_communication_center_parameter;
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

  return true;
}

static bool _ComParameter_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ComParameter_Request__ros_msg_type * ros_message = static_cast<_ComParameter_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: request_communication_center_parameter
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->request_communication_center_parameter.data) {
      rosidl_runtime_c__String__init(&ros_message->request_communication_center_parameter);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->request_communication_center_parameter,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'request_communication_center_parameter'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rlfw_msgs
size_t get_serialized_size_rlfw_msgs__srv__ComParameter_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ComParameter_Request__ros_msg_type * ros_message = static_cast<const _ComParameter_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name request_communication_center_parameter
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->request_communication_center_parameter.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _ComParameter_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_rlfw_msgs__srv__ComParameter_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rlfw_msgs
size_t max_serialized_size_rlfw_msgs__srv__ComParameter_Request(
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

  // member: request_communication_center_parameter
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

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = rlfw_msgs__srv__ComParameter_Request;
    is_plain =
      (
      offsetof(DataType, request_communication_center_parameter) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ComParameter_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_rlfw_msgs__srv__ComParameter_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ComParameter_Request = {
  "rlfw_msgs::srv",
  "ComParameter_Request",
  _ComParameter_Request__cdr_serialize,
  _ComParameter_Request__cdr_deserialize,
  _ComParameter_Request__get_serialized_size,
  _ComParameter_Request__max_serialized_size
};

static rosidl_message_type_support_t _ComParameter_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ComParameter_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rlfw_msgs, srv, ComParameter_Request)() {
  return &_ComParameter_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "rlfw_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "rlfw_msgs/srv/detail/com_parameter__struct.h"
// already included above
// #include "rlfw_msgs/srv/detail/com_parameter__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

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

// already included above
// #include "rosidl_runtime_c/string.h"  // device_name, device_type
// already included above
// #include "rosidl_runtime_c/string_functions.h"  // device_name, device_type

// forward declare type support functions


using _ComParameter_Response__ros_msg_type = rlfw_msgs__srv__ComParameter_Response;

static bool _ComParameter_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ComParameter_Response__ros_msg_type * ros_message = static_cast<const _ComParameter_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: device_name
  {
    size_t size = ros_message->device_name.size;
    auto array_ptr = ros_message->device_name.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
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
  }

  // Field name: device_type
  {
    size_t size = ros_message->device_type.size;
    auto array_ptr = ros_message->device_type.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
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
  }

  return true;
}

static bool _ComParameter_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ComParameter_Response__ros_msg_type * ros_message = static_cast<_ComParameter_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: device_name
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->device_name.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->device_name);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->device_name, size)) {
      fprintf(stderr, "failed to create array for field 'device_name'");
      return false;
    }
    auto array_ptr = ros_message->device_name.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'device_name'\n");
        return false;
      }
    }
  }

  // Field name: device_type
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->device_type.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->device_type);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->device_type, size)) {
      fprintf(stderr, "failed to create array for field 'device_type'");
      return false;
    }
    auto array_ptr = ros_message->device_type.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'device_type'\n");
        return false;
      }
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rlfw_msgs
size_t get_serialized_size_rlfw_msgs__srv__ComParameter_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ComParameter_Response__ros_msg_type * ros_message = static_cast<const _ComParameter_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name device_name
  {
    size_t array_size = ros_message->device_name.size;
    auto array_ptr = ros_message->device_name.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }
  // field.name device_type
  {
    size_t array_size = ros_message->device_type.size;
    auto array_ptr = ros_message->device_type.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }

  return current_alignment - initial_alignment;
}

static uint32_t _ComParameter_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_rlfw_msgs__srv__ComParameter_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rlfw_msgs
size_t max_serialized_size_rlfw_msgs__srv__ComParameter_Response(
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

  // member: device_name
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: device_type
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = rlfw_msgs__srv__ComParameter_Response;
    is_plain =
      (
      offsetof(DataType, device_type) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ComParameter_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_rlfw_msgs__srv__ComParameter_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ComParameter_Response = {
  "rlfw_msgs::srv",
  "ComParameter_Response",
  _ComParameter_Response__cdr_serialize,
  _ComParameter_Response__cdr_deserialize,
  _ComParameter_Response__get_serialized_size,
  _ComParameter_Response__max_serialized_size
};

static rosidl_message_type_support_t _ComParameter_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ComParameter_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rlfw_msgs, srv, ComParameter_Response)() {
  return &_ComParameter_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rlfw_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "rlfw_msgs/srv/com_parameter.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t ComParameter__callbacks = {
  "rlfw_msgs::srv",
  "ComParameter",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rlfw_msgs, srv, ComParameter_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rlfw_msgs, srv, ComParameter_Response)(),
};

static rosidl_service_type_support_t ComParameter__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &ComParameter__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rlfw_msgs, srv, ComParameter)() {
  return &ComParameter__handle;
}

#if defined(__cplusplus)
}
#endif
