// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rlfw_msgs:msg/Motor.idl
// generated code does not contain a copyright notice
#include "rlfw_msgs/msg/detail/motor__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `joint`
#include "std_msgs/msg/detail/header__functions.h"

bool
rlfw_msgs__msg__Motor__init(rlfw_msgs__msg__Motor * msg)
{
  if (!msg) {
    return false;
  }
  // joint
  if (!std_msgs__msg__Header__init(&msg->joint)) {
    rlfw_msgs__msg__Motor__fini(msg);
    return false;
  }
  // motor_id
  // angle
  // number_laps
  // ang_vel
  // torque
  // current
  // temperature
  // state
  return true;
}

void
rlfw_msgs__msg__Motor__fini(rlfw_msgs__msg__Motor * msg)
{
  if (!msg) {
    return;
  }
  // joint
  std_msgs__msg__Header__fini(&msg->joint);
  // motor_id
  // angle
  // number_laps
  // ang_vel
  // torque
  // current
  // temperature
  // state
}

bool
rlfw_msgs__msg__Motor__are_equal(const rlfw_msgs__msg__Motor * lhs, const rlfw_msgs__msg__Motor * rhs)
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
  // angle
  if (lhs->angle != rhs->angle) {
    return false;
  }
  // number_laps
  if (lhs->number_laps != rhs->number_laps) {
    return false;
  }
  // ang_vel
  if (lhs->ang_vel != rhs->ang_vel) {
    return false;
  }
  // torque
  if (lhs->torque != rhs->torque) {
    return false;
  }
  // current
  if (lhs->current != rhs->current) {
    return false;
  }
  // temperature
  if (lhs->temperature != rhs->temperature) {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  return true;
}

bool
rlfw_msgs__msg__Motor__copy(
  const rlfw_msgs__msg__Motor * input,
  rlfw_msgs__msg__Motor * output)
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
  // angle
  output->angle = input->angle;
  // number_laps
  output->number_laps = input->number_laps;
  // ang_vel
  output->ang_vel = input->ang_vel;
  // torque
  output->torque = input->torque;
  // current
  output->current = input->current;
  // temperature
  output->temperature = input->temperature;
  // state
  output->state = input->state;
  return true;
}

rlfw_msgs__msg__Motor *
rlfw_msgs__msg__Motor__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__Motor * msg = (rlfw_msgs__msg__Motor *)allocator.allocate(sizeof(rlfw_msgs__msg__Motor), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rlfw_msgs__msg__Motor));
  bool success = rlfw_msgs__msg__Motor__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rlfw_msgs__msg__Motor__destroy(rlfw_msgs__msg__Motor * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rlfw_msgs__msg__Motor__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rlfw_msgs__msg__Motor__Sequence__init(rlfw_msgs__msg__Motor__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__Motor * data = NULL;

  if (size) {
    data = (rlfw_msgs__msg__Motor *)allocator.zero_allocate(size, sizeof(rlfw_msgs__msg__Motor), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rlfw_msgs__msg__Motor__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rlfw_msgs__msg__Motor__fini(&data[i - 1]);
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
rlfw_msgs__msg__Motor__Sequence__fini(rlfw_msgs__msg__Motor__Sequence * array)
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
      rlfw_msgs__msg__Motor__fini(&array->data[i]);
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

rlfw_msgs__msg__Motor__Sequence *
rlfw_msgs__msg__Motor__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__Motor__Sequence * array = (rlfw_msgs__msg__Motor__Sequence *)allocator.allocate(sizeof(rlfw_msgs__msg__Motor__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rlfw_msgs__msg__Motor__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rlfw_msgs__msg__Motor__Sequence__destroy(rlfw_msgs__msg__Motor__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rlfw_msgs__msg__Motor__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rlfw_msgs__msg__Motor__Sequence__are_equal(const rlfw_msgs__msg__Motor__Sequence * lhs, const rlfw_msgs__msg__Motor__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rlfw_msgs__msg__Motor__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rlfw_msgs__msg__Motor__Sequence__copy(
  const rlfw_msgs__msg__Motor__Sequence * input,
  rlfw_msgs__msg__Motor__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rlfw_msgs__msg__Motor);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rlfw_msgs__msg__Motor * data =
      (rlfw_msgs__msg__Motor *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rlfw_msgs__msg__Motor__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rlfw_msgs__msg__Motor__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rlfw_msgs__msg__Motor__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
