// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rlfw_msgs:srv/ComParameter.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rlfw_msgs/srv/detail/com_parameter__rosidl_typesupport_introspection_c.h"
#include "rlfw_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rlfw_msgs/srv/detail/com_parameter__functions.h"
#include "rlfw_msgs/srv/detail/com_parameter__struct.h"


// Include directives for member types
// Member `request_communication_center_parameter`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rlfw_msgs__srv__ComParameter_Request__init(message_memory);
}

void rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_fini_function(void * message_memory)
{
  rlfw_msgs__srv__ComParameter_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_message_member_array[1] = {
  {
    "request_communication_center_parameter",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__srv__ComParameter_Request, request_communication_center_parameter),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_message_members = {
  "rlfw_msgs__srv",  // message namespace
  "ComParameter_Request",  // message name
  1,  // number of fields
  sizeof(rlfw_msgs__srv__ComParameter_Request),
  rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_message_member_array,  // message members
  rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_message_type_support_handle = {
  0,
  &rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rlfw_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rlfw_msgs, srv, ComParameter_Request)() {
  if (!rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_message_type_support_handle.typesupport_identifier) {
    rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rlfw_msgs__srv__ComParameter_Request__rosidl_typesupport_introspection_c__ComParameter_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "rlfw_msgs/srv/detail/com_parameter__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rlfw_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "rlfw_msgs/srv/detail/com_parameter__functions.h"
// already included above
// #include "rlfw_msgs/srv/detail/com_parameter__struct.h"


// Include directives for member types
// Member `device_name`
// Member `device_type`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rlfw_msgs__srv__ComParameter_Response__init(message_memory);
}

void rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_fini_function(void * message_memory)
{
  rlfw_msgs__srv__ComParameter_Response__fini(message_memory);
}

size_t rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__size_function__ComParameter_Response__device_name(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_const_function__ComParameter_Response__device_name(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_function__ComParameter_Response__device_name(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__fetch_function__ComParameter_Response__device_name(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_const_function__ComParameter_Response__device_name(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__assign_function__ComParameter_Response__device_name(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_function__ComParameter_Response__device_name(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__resize_function__ComParameter_Response__device_name(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__size_function__ComParameter_Response__device_type(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_const_function__ComParameter_Response__device_type(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_function__ComParameter_Response__device_type(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__fetch_function__ComParameter_Response__device_type(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_const_function__ComParameter_Response__device_type(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__assign_function__ComParameter_Response__device_type(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_function__ComParameter_Response__device_type(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__resize_function__ComParameter_Response__device_type(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_message_member_array[2] = {
  {
    "device_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__srv__ComParameter_Response, device_name),  // bytes offset in struct
    NULL,  // default value
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__size_function__ComParameter_Response__device_name,  // size() function pointer
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_const_function__ComParameter_Response__device_name,  // get_const(index) function pointer
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_function__ComParameter_Response__device_name,  // get(index) function pointer
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__fetch_function__ComParameter_Response__device_name,  // fetch(index, &value) function pointer
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__assign_function__ComParameter_Response__device_name,  // assign(index, value) function pointer
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__resize_function__ComParameter_Response__device_name  // resize(index) function pointer
  },
  {
    "device_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rlfw_msgs__srv__ComParameter_Response, device_type),  // bytes offset in struct
    NULL,  // default value
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__size_function__ComParameter_Response__device_type,  // size() function pointer
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_const_function__ComParameter_Response__device_type,  // get_const(index) function pointer
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__get_function__ComParameter_Response__device_type,  // get(index) function pointer
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__fetch_function__ComParameter_Response__device_type,  // fetch(index, &value) function pointer
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__assign_function__ComParameter_Response__device_type,  // assign(index, value) function pointer
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__resize_function__ComParameter_Response__device_type  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_message_members = {
  "rlfw_msgs__srv",  // message namespace
  "ComParameter_Response",  // message name
  2,  // number of fields
  sizeof(rlfw_msgs__srv__ComParameter_Response),
  rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_message_member_array,  // message members
  rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_message_type_support_handle = {
  0,
  &rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rlfw_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rlfw_msgs, srv, ComParameter_Response)() {
  if (!rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_message_type_support_handle.typesupport_identifier) {
    rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rlfw_msgs__srv__ComParameter_Response__rosidl_typesupport_introspection_c__ComParameter_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rlfw_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rlfw_msgs/srv/detail/com_parameter__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers rlfw_msgs__srv__detail__com_parameter__rosidl_typesupport_introspection_c__ComParameter_service_members = {
  "rlfw_msgs__srv",  // service namespace
  "ComParameter",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // rlfw_msgs__srv__detail__com_parameter__rosidl_typesupport_introspection_c__ComParameter_Request_message_type_support_handle,
  NULL  // response message
  // rlfw_msgs__srv__detail__com_parameter__rosidl_typesupport_introspection_c__ComParameter_Response_message_type_support_handle
};

static rosidl_service_type_support_t rlfw_msgs__srv__detail__com_parameter__rosidl_typesupport_introspection_c__ComParameter_service_type_support_handle = {
  0,
  &rlfw_msgs__srv__detail__com_parameter__rosidl_typesupport_introspection_c__ComParameter_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rlfw_msgs, srv, ComParameter_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rlfw_msgs, srv, ComParameter_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rlfw_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rlfw_msgs, srv, ComParameter)() {
  if (!rlfw_msgs__srv__detail__com_parameter__rosidl_typesupport_introspection_c__ComParameter_service_type_support_handle.typesupport_identifier) {
    rlfw_msgs__srv__detail__com_parameter__rosidl_typesupport_introspection_c__ComParameter_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)rlfw_msgs__srv__detail__com_parameter__rosidl_typesupport_introspection_c__ComParameter_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rlfw_msgs, srv, ComParameter_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rlfw_msgs, srv, ComParameter_Response)()->data;
  }

  return &rlfw_msgs__srv__detail__com_parameter__rosidl_typesupport_introspection_c__ComParameter_service_type_support_handle;
}
