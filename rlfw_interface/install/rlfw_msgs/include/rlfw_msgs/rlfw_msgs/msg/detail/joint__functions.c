// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rlfw_msgs:msg/Joint.idl
// generated code does not contain a copyright notice
#include "rlfw_msgs/msg/detail/joint__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `jointname`
#include "std_msgs/msg/detail/header__functions.h"
// Member `other`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
rlfw_msgs__msg__Joint__init(rlfw_msgs__msg__Joint * msg)
{
  if (!msg) {
    return false;
  }
  // jointname
  if (!std_msgs__msg__Header__init(&msg->jointname)) {
    rlfw_msgs__msg__Joint__fini(msg);
    return false;
  }
  // joint_id
  // pos
  // number_laps
  // vel
  // torque
  // current
  // temperature
  // state
  // other
  if (!rosidl_runtime_c__float__Sequence__init(&msg->other, 0)) {
    rlfw_msgs__msg__Joint__fini(msg);
    return false;
  }
  return true;
}

void
rlfw_msgs__msg__Joint__fini(rlfw_msgs__msg__Joint * msg)
{
  if (!msg) {
    return;
  }
  // jointname
  std_msgs__msg__Header__fini(&msg->jointname);
  // joint_id
  // pos
  // number_laps
  // vel
  // torque
  // current
  // temperature
  // state
  // other
  rosidl_runtime_c__float__Sequence__fini(&msg->other);
}

bool
rlfw_msgs__msg__Joint__are_equal(const rlfw_msgs__msg__Joint * lhs, const rlfw_msgs__msg__Joint * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // jointname
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->jointname), &(rhs->jointname)))
  {
    return false;
  }
  // joint_id
  if (lhs->joint_id != rhs->joint_id) {
    return false;
  }
  // pos
  if (lhs->pos != rhs->pos) {
    return false;
  }
  // number_laps
  if (lhs->number_laps != rhs->number_laps) {
    return false;
  }
  // vel
  if (lhs->vel != rhs->vel) {
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
  // other
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->other), &(rhs->other)))
  {
    return false;
  }
  return true;
}

bool
rlfw_msgs__msg__Joint__copy(
  const rlfw_msgs__msg__Joint * input,
  rlfw_msgs__msg__Joint * output)
{
  if (!input || !output) {
    return false;
  }
  // jointname
  if (!std_msgs__msg__Header__copy(
      &(input->jointname), &(output->jointname)))
  {
    return false;
  }
  // joint_id
  output->joint_id = input->joint_id;
  // pos
  output->pos = input->pos;
  // number_laps
  output->number_laps = input->number_laps;
  // vel
  output->vel = input->vel;
  // torque
  output->torque = input->torque;
  // current
  output->current = input->current;
  // temperature
  output->temperature = input->temperature;
  // state
  output->state = input->state;
  // other
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->other), &(output->other)))
  {
    return false;
  }
  return true;
}

rlfw_msgs__msg__Joint *
rlfw_msgs__msg__Joint__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__Joint * msg = (rlfw_msgs__msg__Joint *)allocator.allocate(sizeof(rlfw_msgs__msg__Joint), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rlfw_msgs__msg__Joint));
  bool success = rlfw_msgs__msg__Joint__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rlfw_msgs__msg__Joint__destroy(rlfw_msgs__msg__Joint * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rlfw_msgs__msg__Joint__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rlfw_msgs__msg__Joint__Sequence__init(rlfw_msgs__msg__Joint__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__Joint * data = NULL;

  if (size) {
    data = (rlfw_msgs__msg__Joint *)allocator.zero_allocate(size, sizeof(rlfw_msgs__msg__Joint), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rlfw_msgs__msg__Joint__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rlfw_msgs__msg__Joint__fini(&data[i - 1]);
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
rlfw_msgs__msg__Joint__Sequence__fini(rlfw_msgs__msg__Joint__Sequence * array)
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
      rlfw_msgs__msg__Joint__fini(&array->data[i]);
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

rlfw_msgs__msg__Joint__Sequence *
rlfw_msgs__msg__Joint__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__Joint__Sequence * array = (rlfw_msgs__msg__Joint__Sequence *)allocator.allocate(sizeof(rlfw_msgs__msg__Joint__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rlfw_msgs__msg__Joint__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rlfw_msgs__msg__Joint__Sequence__destroy(rlfw_msgs__msg__Joint__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rlfw_msgs__msg__Joint__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rlfw_msgs__msg__Joint__Sequence__are_equal(const rlfw_msgs__msg__Joint__Sequence * lhs, const rlfw_msgs__msg__Joint__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rlfw_msgs__msg__Joint__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rlfw_msgs__msg__Joint__Sequence__copy(
  const rlfw_msgs__msg__Joint__Sequence * input,
  rlfw_msgs__msg__Joint__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rlfw_msgs__msg__Joint);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rlfw_msgs__msg__Joint * data =
      (rlfw_msgs__msg__Joint *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rlfw_msgs__msg__Joint__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rlfw_msgs__msg__Joint__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rlfw_msgs__msg__Joint__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
