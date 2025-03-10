// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rlfw_msgs:srv/ComParameter.idl
// generated code does not contain a copyright notice
#include "rlfw_msgs/srv/detail/com_parameter__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `request_communication_center_parameter`
#include "rosidl_runtime_c/string_functions.h"

bool
rlfw_msgs__srv__ComParameter_Request__init(rlfw_msgs__srv__ComParameter_Request * msg)
{
  if (!msg) {
    return false;
  }
  // request_communication_center_parameter
  if (!rosidl_runtime_c__String__init(&msg->request_communication_center_parameter)) {
    rlfw_msgs__srv__ComParameter_Request__fini(msg);
    return false;
  }
  return true;
}

void
rlfw_msgs__srv__ComParameter_Request__fini(rlfw_msgs__srv__ComParameter_Request * msg)
{
  if (!msg) {
    return;
  }
  // request_communication_center_parameter
  rosidl_runtime_c__String__fini(&msg->request_communication_center_parameter);
}

bool
rlfw_msgs__srv__ComParameter_Request__are_equal(const rlfw_msgs__srv__ComParameter_Request * lhs, const rlfw_msgs__srv__ComParameter_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // request_communication_center_parameter
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->request_communication_center_parameter), &(rhs->request_communication_center_parameter)))
  {
    return false;
  }
  return true;
}

bool
rlfw_msgs__srv__ComParameter_Request__copy(
  const rlfw_msgs__srv__ComParameter_Request * input,
  rlfw_msgs__srv__ComParameter_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // request_communication_center_parameter
  if (!rosidl_runtime_c__String__copy(
      &(input->request_communication_center_parameter), &(output->request_communication_center_parameter)))
  {
    return false;
  }
  return true;
}

rlfw_msgs__srv__ComParameter_Request *
rlfw_msgs__srv__ComParameter_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__srv__ComParameter_Request * msg = (rlfw_msgs__srv__ComParameter_Request *)allocator.allocate(sizeof(rlfw_msgs__srv__ComParameter_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rlfw_msgs__srv__ComParameter_Request));
  bool success = rlfw_msgs__srv__ComParameter_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rlfw_msgs__srv__ComParameter_Request__destroy(rlfw_msgs__srv__ComParameter_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rlfw_msgs__srv__ComParameter_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rlfw_msgs__srv__ComParameter_Request__Sequence__init(rlfw_msgs__srv__ComParameter_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__srv__ComParameter_Request * data = NULL;

  if (size) {
    data = (rlfw_msgs__srv__ComParameter_Request *)allocator.zero_allocate(size, sizeof(rlfw_msgs__srv__ComParameter_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rlfw_msgs__srv__ComParameter_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rlfw_msgs__srv__ComParameter_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rlfw_msgs__srv__ComParameter_Request__Sequence__fini(rlfw_msgs__srv__ComParameter_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rlfw_msgs__srv__ComParameter_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rlfw_msgs__srv__ComParameter_Request__Sequence *
rlfw_msgs__srv__ComParameter_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__srv__ComParameter_Request__Sequence * array = (rlfw_msgs__srv__ComParameter_Request__Sequence *)allocator.allocate(sizeof(rlfw_msgs__srv__ComParameter_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rlfw_msgs__srv__ComParameter_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rlfw_msgs__srv__ComParameter_Request__Sequence__destroy(rlfw_msgs__srv__ComParameter_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rlfw_msgs__srv__ComParameter_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rlfw_msgs__srv__ComParameter_Request__Sequence__are_equal(const rlfw_msgs__srv__ComParameter_Request__Sequence * lhs, const rlfw_msgs__srv__ComParameter_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rlfw_msgs__srv__ComParameter_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rlfw_msgs__srv__ComParameter_Request__Sequence__copy(
  const rlfw_msgs__srv__ComParameter_Request__Sequence * input,
  rlfw_msgs__srv__ComParameter_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rlfw_msgs__srv__ComParameter_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rlfw_msgs__srv__ComParameter_Request * data =
      (rlfw_msgs__srv__ComParameter_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rlfw_msgs__srv__ComParameter_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rlfw_msgs__srv__ComParameter_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rlfw_msgs__srv__ComParameter_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `device_name`
// Member `device_type`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
rlfw_msgs__srv__ComParameter_Response__init(rlfw_msgs__srv__ComParameter_Response * msg)
{
  if (!msg) {
    return false;
  }
  // device_name
  if (!rosidl_runtime_c__String__Sequence__init(&msg->device_name, 0)) {
    rlfw_msgs__srv__ComParameter_Response__fini(msg);
    return false;
  }
  // device_type
  if (!rosidl_runtime_c__String__Sequence__init(&msg->device_type, 0)) {
    rlfw_msgs__srv__ComParameter_Response__fini(msg);
    return false;
  }
  return true;
}

void
rlfw_msgs__srv__ComParameter_Response__fini(rlfw_msgs__srv__ComParameter_Response * msg)
{
  if (!msg) {
    return;
  }
  // device_name
  rosidl_runtime_c__String__Sequence__fini(&msg->device_name);
  // device_type
  rosidl_runtime_c__String__Sequence__fini(&msg->device_type);
}

bool
rlfw_msgs__srv__ComParameter_Response__are_equal(const rlfw_msgs__srv__ComParameter_Response * lhs, const rlfw_msgs__srv__ComParameter_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // device_name
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->device_name), &(rhs->device_name)))
  {
    return false;
  }
  // device_type
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->device_type), &(rhs->device_type)))
  {
    return false;
  }
  return true;
}

bool
rlfw_msgs__srv__ComParameter_Response__copy(
  const rlfw_msgs__srv__ComParameter_Response * input,
  rlfw_msgs__srv__ComParameter_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // device_name
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->device_name), &(output->device_name)))
  {
    return false;
  }
  // device_type
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->device_type), &(output->device_type)))
  {
    return false;
  }
  return true;
}

rlfw_msgs__srv__ComParameter_Response *
rlfw_msgs__srv__ComParameter_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__srv__ComParameter_Response * msg = (rlfw_msgs__srv__ComParameter_Response *)allocator.allocate(sizeof(rlfw_msgs__srv__ComParameter_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rlfw_msgs__srv__ComParameter_Response));
  bool success = rlfw_msgs__srv__ComParameter_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rlfw_msgs__srv__ComParameter_Response__destroy(rlfw_msgs__srv__ComParameter_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rlfw_msgs__srv__ComParameter_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rlfw_msgs__srv__ComParameter_Response__Sequence__init(rlfw_msgs__srv__ComParameter_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__srv__ComParameter_Response * data = NULL;

  if (size) {
    data = (rlfw_msgs__srv__ComParameter_Response *)allocator.zero_allocate(size, sizeof(rlfw_msgs__srv__ComParameter_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rlfw_msgs__srv__ComParameter_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rlfw_msgs__srv__ComParameter_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rlfw_msgs__srv__ComParameter_Response__Sequence__fini(rlfw_msgs__srv__ComParameter_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rlfw_msgs__srv__ComParameter_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rlfw_msgs__srv__ComParameter_Response__Sequence *
rlfw_msgs__srv__ComParameter_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__srv__ComParameter_Response__Sequence * array = (rlfw_msgs__srv__ComParameter_Response__Sequence *)allocator.allocate(sizeof(rlfw_msgs__srv__ComParameter_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rlfw_msgs__srv__ComParameter_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rlfw_msgs__srv__ComParameter_Response__Sequence__destroy(rlfw_msgs__srv__ComParameter_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rlfw_msgs__srv__ComParameter_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rlfw_msgs__srv__ComParameter_Response__Sequence__are_equal(const rlfw_msgs__srv__ComParameter_Response__Sequence * lhs, const rlfw_msgs__srv__ComParameter_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rlfw_msgs__srv__ComParameter_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rlfw_msgs__srv__ComParameter_Response__Sequence__copy(
  const rlfw_msgs__srv__ComParameter_Response__Sequence * input,
  rlfw_msgs__srv__ComParameter_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rlfw_msgs__srv__ComParameter_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rlfw_msgs__srv__ComParameter_Response * data =
      (rlfw_msgs__srv__ComParameter_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rlfw_msgs__srv__ComParameter_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rlfw_msgs__srv__ComParameter_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rlfw_msgs__srv__ComParameter_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
