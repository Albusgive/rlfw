// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rlfw_msgs:msg/Remote.idl
// generated code does not contain a copyright notice
#include "rlfw_msgs/msg/detail/remote__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `remotename`
#include "std_msgs/msg/detail/header__functions.h"
// Member `key`
#include "rosidl_runtime_c/string_functions.h"
// Member `value`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
rlfw_msgs__msg__Remote__init(rlfw_msgs__msg__Remote * msg)
{
  if (!msg) {
    return false;
  }
  // remotename
  if (!std_msgs__msg__Header__init(&msg->remotename)) {
    rlfw_msgs__msg__Remote__fini(msg);
    return false;
  }
  // key
  if (!rosidl_runtime_c__String__Sequence__init(&msg->key, 0)) {
    rlfw_msgs__msg__Remote__fini(msg);
    return false;
  }
  // value
  if (!rosidl_runtime_c__float__Sequence__init(&msg->value, 0)) {
    rlfw_msgs__msg__Remote__fini(msg);
    return false;
  }
  return true;
}

void
rlfw_msgs__msg__Remote__fini(rlfw_msgs__msg__Remote * msg)
{
  if (!msg) {
    return;
  }
  // remotename
  std_msgs__msg__Header__fini(&msg->remotename);
  // key
  rosidl_runtime_c__String__Sequence__fini(&msg->key);
  // value
  rosidl_runtime_c__float__Sequence__fini(&msg->value);
}

bool
rlfw_msgs__msg__Remote__are_equal(const rlfw_msgs__msg__Remote * lhs, const rlfw_msgs__msg__Remote * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // remotename
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->remotename), &(rhs->remotename)))
  {
    return false;
  }
  // key
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->key), &(rhs->key)))
  {
    return false;
  }
  // value
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->value), &(rhs->value)))
  {
    return false;
  }
  return true;
}

bool
rlfw_msgs__msg__Remote__copy(
  const rlfw_msgs__msg__Remote * input,
  rlfw_msgs__msg__Remote * output)
{
  if (!input || !output) {
    return false;
  }
  // remotename
  if (!std_msgs__msg__Header__copy(
      &(input->remotename), &(output->remotename)))
  {
    return false;
  }
  // key
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->key), &(output->key)))
  {
    return false;
  }
  // value
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->value), &(output->value)))
  {
    return false;
  }
  return true;
}

rlfw_msgs__msg__Remote *
rlfw_msgs__msg__Remote__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__Remote * msg = (rlfw_msgs__msg__Remote *)allocator.allocate(sizeof(rlfw_msgs__msg__Remote), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rlfw_msgs__msg__Remote));
  bool success = rlfw_msgs__msg__Remote__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rlfw_msgs__msg__Remote__destroy(rlfw_msgs__msg__Remote * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rlfw_msgs__msg__Remote__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rlfw_msgs__msg__Remote__Sequence__init(rlfw_msgs__msg__Remote__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__Remote * data = NULL;

  if (size) {
    data = (rlfw_msgs__msg__Remote *)allocator.zero_allocate(size, sizeof(rlfw_msgs__msg__Remote), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rlfw_msgs__msg__Remote__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rlfw_msgs__msg__Remote__fini(&data[i - 1]);
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
rlfw_msgs__msg__Remote__Sequence__fini(rlfw_msgs__msg__Remote__Sequence * array)
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
      rlfw_msgs__msg__Remote__fini(&array->data[i]);
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

rlfw_msgs__msg__Remote__Sequence *
rlfw_msgs__msg__Remote__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__Remote__Sequence * array = (rlfw_msgs__msg__Remote__Sequence *)allocator.allocate(sizeof(rlfw_msgs__msg__Remote__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rlfw_msgs__msg__Remote__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rlfw_msgs__msg__Remote__Sequence__destroy(rlfw_msgs__msg__Remote__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rlfw_msgs__msg__Remote__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rlfw_msgs__msg__Remote__Sequence__are_equal(const rlfw_msgs__msg__Remote__Sequence * lhs, const rlfw_msgs__msg__Remote__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rlfw_msgs__msg__Remote__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rlfw_msgs__msg__Remote__Sequence__copy(
  const rlfw_msgs__msg__Remote__Sequence * input,
  rlfw_msgs__msg__Remote__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rlfw_msgs__msg__Remote);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rlfw_msgs__msg__Remote * data =
      (rlfw_msgs__msg__Remote *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rlfw_msgs__msg__Remote__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rlfw_msgs__msg__Remote__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rlfw_msgs__msg__Remote__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
