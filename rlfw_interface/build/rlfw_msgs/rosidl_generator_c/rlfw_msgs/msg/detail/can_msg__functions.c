// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rlfw_msgs:msg/CanMsg.idl
// generated code does not contain a copyright notice
#include "rlfw_msgs/msg/detail/can_msg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `comname`
#include "std_msgs/msg/detail/header__functions.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
rlfw_msgs__msg__CanMsg__init(rlfw_msgs__msg__CanMsg * msg)
{
  if (!msg) {
    return false;
  }
  // comname
  if (!std_msgs__msg__Header__init(&msg->comname)) {
    rlfw_msgs__msg__CanMsg__fini(msg);
    return false;
  }
  // id
  // msgtype
  // len
  // data
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->data, 0)) {
    rlfw_msgs__msg__CanMsg__fini(msg);
    return false;
  }
  return true;
}

void
rlfw_msgs__msg__CanMsg__fini(rlfw_msgs__msg__CanMsg * msg)
{
  if (!msg) {
    return;
  }
  // comname
  std_msgs__msg__Header__fini(&msg->comname);
  // id
  // msgtype
  // len
  // data
  rosidl_runtime_c__uint8__Sequence__fini(&msg->data);
}

bool
rlfw_msgs__msg__CanMsg__are_equal(const rlfw_msgs__msg__CanMsg * lhs, const rlfw_msgs__msg__CanMsg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // comname
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->comname), &(rhs->comname)))
  {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // msgtype
  if (lhs->msgtype != rhs->msgtype) {
    return false;
  }
  // len
  if (lhs->len != rhs->len) {
    return false;
  }
  // data
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  return true;
}

bool
rlfw_msgs__msg__CanMsg__copy(
  const rlfw_msgs__msg__CanMsg * input,
  rlfw_msgs__msg__CanMsg * output)
{
  if (!input || !output) {
    return false;
  }
  // comname
  if (!std_msgs__msg__Header__copy(
      &(input->comname), &(output->comname)))
  {
    return false;
  }
  // id
  output->id = input->id;
  // msgtype
  output->msgtype = input->msgtype;
  // len
  output->len = input->len;
  // data
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  return true;
}

rlfw_msgs__msg__CanMsg *
rlfw_msgs__msg__CanMsg__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__CanMsg * msg = (rlfw_msgs__msg__CanMsg *)allocator.allocate(sizeof(rlfw_msgs__msg__CanMsg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rlfw_msgs__msg__CanMsg));
  bool success = rlfw_msgs__msg__CanMsg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rlfw_msgs__msg__CanMsg__destroy(rlfw_msgs__msg__CanMsg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rlfw_msgs__msg__CanMsg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rlfw_msgs__msg__CanMsg__Sequence__init(rlfw_msgs__msg__CanMsg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__CanMsg * data = NULL;

  if (size) {
    data = (rlfw_msgs__msg__CanMsg *)allocator.zero_allocate(size, sizeof(rlfw_msgs__msg__CanMsg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rlfw_msgs__msg__CanMsg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rlfw_msgs__msg__CanMsg__fini(&data[i - 1]);
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
rlfw_msgs__msg__CanMsg__Sequence__fini(rlfw_msgs__msg__CanMsg__Sequence * array)
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
      rlfw_msgs__msg__CanMsg__fini(&array->data[i]);
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

rlfw_msgs__msg__CanMsg__Sequence *
rlfw_msgs__msg__CanMsg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__CanMsg__Sequence * array = (rlfw_msgs__msg__CanMsg__Sequence *)allocator.allocate(sizeof(rlfw_msgs__msg__CanMsg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rlfw_msgs__msg__CanMsg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rlfw_msgs__msg__CanMsg__Sequence__destroy(rlfw_msgs__msg__CanMsg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rlfw_msgs__msg__CanMsg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rlfw_msgs__msg__CanMsg__Sequence__are_equal(const rlfw_msgs__msg__CanMsg__Sequence * lhs, const rlfw_msgs__msg__CanMsg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rlfw_msgs__msg__CanMsg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rlfw_msgs__msg__CanMsg__Sequence__copy(
  const rlfw_msgs__msg__CanMsg__Sequence * input,
  rlfw_msgs__msg__CanMsg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rlfw_msgs__msg__CanMsg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rlfw_msgs__msg__CanMsg * data =
      (rlfw_msgs__msg__CanMsg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rlfw_msgs__msg__CanMsg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rlfw_msgs__msg__CanMsg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rlfw_msgs__msg__CanMsg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
