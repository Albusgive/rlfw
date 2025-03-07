// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rlfw_msgs:msg/MotorCfg.idl
// generated code does not contain a copyright notice
#include "rlfw_msgs/msg/detail/motor_cfg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `joint`
#include "std_msgs/msg/detail/header__functions.h"
// Member `parameter_type`
#include "rosidl_runtime_c/string_functions.h"

bool
rlfw_msgs__msg__MotorCfg__init(rlfw_msgs__msg__MotorCfg * msg)
{
  if (!msg) {
    return false;
  }
  // joint
  if (!std_msgs__msg__Header__init(&msg->joint)) {
    rlfw_msgs__msg__MotorCfg__fini(msg);
    return false;
  }
  // motor_id
  // parameter_type
  if (!rosidl_runtime_c__String__init(&msg->parameter_type)) {
    rlfw_msgs__msg__MotorCfg__fini(msg);
    return false;
  }
  // parameter
  return true;
}

void
rlfw_msgs__msg__MotorCfg__fini(rlfw_msgs__msg__MotorCfg * msg)
{
  if (!msg) {
    return;
  }
  // joint
  std_msgs__msg__Header__fini(&msg->joint);
  // motor_id
  // parameter_type
  rosidl_runtime_c__String__fini(&msg->parameter_type);
  // parameter
}

bool
rlfw_msgs__msg__MotorCfg__are_equal(const rlfw_msgs__msg__MotorCfg * lhs, const rlfw_msgs__msg__MotorCfg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // joint
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->joint), &(rhs->joint)))
  {
    return false;
  }
  // motor_id
  if (lhs->motor_id != rhs->motor_id) {
    return false;
  }
  // parameter_type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->parameter_type), &(rhs->parameter_type)))
  {
    return false;
  }
  // parameter
  if (lhs->parameter != rhs->parameter) {
    return false;
  }
  return true;
}

bool
rlfw_msgs__msg__MotorCfg__copy(
  const rlfw_msgs__msg__MotorCfg * input,
  rlfw_msgs__msg__MotorCfg * output)
{
  if (!input || !output) {
    return false;
  }
  // joint
  if (!std_msgs__msg__Header__copy(
      &(input->joint), &(output->joint)))
  {
    return false;
  }
  // motor_id
  output->motor_id = input->motor_id;
  // parameter_type
  if (!rosidl_runtime_c__String__copy(
      &(input->parameter_type), &(output->parameter_type)))
  {
    return false;
  }
  // parameter
  output->parameter = input->parameter;
  return true;
}

rlfw_msgs__msg__MotorCfg *
rlfw_msgs__msg__MotorCfg__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__MotorCfg * msg = (rlfw_msgs__msg__MotorCfg *)allocator.allocate(sizeof(rlfw_msgs__msg__MotorCfg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rlfw_msgs__msg__MotorCfg));
  bool success = rlfw_msgs__msg__MotorCfg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rlfw_msgs__msg__MotorCfg__destroy(rlfw_msgs__msg__MotorCfg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rlfw_msgs__msg__MotorCfg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rlfw_msgs__msg__MotorCfg__Sequence__init(rlfw_msgs__msg__MotorCfg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__MotorCfg * data = NULL;

  if (size) {
    data = (rlfw_msgs__msg__MotorCfg *)allocator.zero_allocate(size, sizeof(rlfw_msgs__msg__MotorCfg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rlfw_msgs__msg__MotorCfg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rlfw_msgs__msg__MotorCfg__fini(&data[i - 1]);
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
rlfw_msgs__msg__MotorCfg__Sequence__fini(rlfw_msgs__msg__MotorCfg__Sequence * array)
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
      rlfw_msgs__msg__MotorCfg__fini(&array->data[i]);
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

rlfw_msgs__msg__MotorCfg__Sequence *
rlfw_msgs__msg__MotorCfg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__MotorCfg__Sequence * array = (rlfw_msgs__msg__MotorCfg__Sequence *)allocator.allocate(sizeof(rlfw_msgs__msg__MotorCfg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rlfw_msgs__msg__MotorCfg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rlfw_msgs__msg__MotorCfg__Sequence__destroy(rlfw_msgs__msg__MotorCfg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rlfw_msgs__msg__MotorCfg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rlfw_msgs__msg__MotorCfg__Sequence__are_equal(const rlfw_msgs__msg__MotorCfg__Sequence * lhs, const rlfw_msgs__msg__MotorCfg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rlfw_msgs__msg__MotorCfg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rlfw_msgs__msg__MotorCfg__Sequence__copy(
  const rlfw_msgs__msg__MotorCfg__Sequence * input,
  rlfw_msgs__msg__MotorCfg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rlfw_msgs__msg__MotorCfg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rlfw_msgs__msg__MotorCfg * data =
      (rlfw_msgs__msg__MotorCfg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rlfw_msgs__msg__MotorCfg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rlfw_msgs__msg__MotorCfg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rlfw_msgs__msg__MotorCfg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
