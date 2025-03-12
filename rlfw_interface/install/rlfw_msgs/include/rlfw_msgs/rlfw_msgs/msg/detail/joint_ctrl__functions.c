// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rlfw_msgs:msg/JointCtrl.idl
// generated code does not contain a copyright notice
#include "rlfw_msgs/msg/detail/joint_ctrl__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `jointname`
#include "std_msgs/msg/detail/header__functions.h"
// Member `ctrl_type`
#include "rosidl_runtime_c/string_functions.h"

bool
rlfw_msgs__msg__JointCtrl__init(rlfw_msgs__msg__JointCtrl * msg)
{
  if (!msg) {
    return false;
  }
  // jointname
  if (!std_msgs__msg__Header__init(&msg->jointname)) {
    rlfw_msgs__msg__JointCtrl__fini(msg);
    return false;
  }
  // ctrl_type
  if (!rosidl_runtime_c__String__init(&msg->ctrl_type)) {
    rlfw_msgs__msg__JointCtrl__fini(msg);
    return false;
  }
  // torque
  // pos
  // vel
  // kp
  // kd
  return true;
}

void
rlfw_msgs__msg__JointCtrl__fini(rlfw_msgs__msg__JointCtrl * msg)
{
  if (!msg) {
    return;
  }
  // jointname
  std_msgs__msg__Header__fini(&msg->jointname);
  // ctrl_type
  rosidl_runtime_c__String__fini(&msg->ctrl_type);
  // torque
  // pos
  // vel
  // kp
  // kd
}

bool
rlfw_msgs__msg__JointCtrl__are_equal(const rlfw_msgs__msg__JointCtrl * lhs, const rlfw_msgs__msg__JointCtrl * rhs)
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
  // ctrl_type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->ctrl_type), &(rhs->ctrl_type)))
  {
    return false;
  }
  // torque
  if (lhs->torque != rhs->torque) {
    return false;
  }
  // pos
  if (lhs->pos != rhs->pos) {
    return false;
  }
  // vel
  if (lhs->vel != rhs->vel) {
    return false;
  }
  // kp
  if (lhs->kp != rhs->kp) {
    return false;
  }
  // kd
  if (lhs->kd != rhs->kd) {
    return false;
  }
  return true;
}

bool
rlfw_msgs__msg__JointCtrl__copy(
  const rlfw_msgs__msg__JointCtrl * input,
  rlfw_msgs__msg__JointCtrl * output)
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
  // ctrl_type
  if (!rosidl_runtime_c__String__copy(
      &(input->ctrl_type), &(output->ctrl_type)))
  {
    return false;
  }
  // torque
  output->torque = input->torque;
  // pos
  output->pos = input->pos;
  // vel
  output->vel = input->vel;
  // kp
  output->kp = input->kp;
  // kd
  output->kd = input->kd;
  return true;
}

rlfw_msgs__msg__JointCtrl *
rlfw_msgs__msg__JointCtrl__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__JointCtrl * msg = (rlfw_msgs__msg__JointCtrl *)allocator.allocate(sizeof(rlfw_msgs__msg__JointCtrl), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rlfw_msgs__msg__JointCtrl));
  bool success = rlfw_msgs__msg__JointCtrl__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rlfw_msgs__msg__JointCtrl__destroy(rlfw_msgs__msg__JointCtrl * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rlfw_msgs__msg__JointCtrl__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rlfw_msgs__msg__JointCtrl__Sequence__init(rlfw_msgs__msg__JointCtrl__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__JointCtrl * data = NULL;

  if (size) {
    data = (rlfw_msgs__msg__JointCtrl *)allocator.zero_allocate(size, sizeof(rlfw_msgs__msg__JointCtrl), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rlfw_msgs__msg__JointCtrl__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rlfw_msgs__msg__JointCtrl__fini(&data[i - 1]);
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
rlfw_msgs__msg__JointCtrl__Sequence__fini(rlfw_msgs__msg__JointCtrl__Sequence * array)
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
      rlfw_msgs__msg__JointCtrl__fini(&array->data[i]);
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

rlfw_msgs__msg__JointCtrl__Sequence *
rlfw_msgs__msg__JointCtrl__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rlfw_msgs__msg__JointCtrl__Sequence * array = (rlfw_msgs__msg__JointCtrl__Sequence *)allocator.allocate(sizeof(rlfw_msgs__msg__JointCtrl__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rlfw_msgs__msg__JointCtrl__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rlfw_msgs__msg__JointCtrl__Sequence__destroy(rlfw_msgs__msg__JointCtrl__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rlfw_msgs__msg__JointCtrl__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rlfw_msgs__msg__JointCtrl__Sequence__are_equal(const rlfw_msgs__msg__JointCtrl__Sequence * lhs, const rlfw_msgs__msg__JointCtrl__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rlfw_msgs__msg__JointCtrl__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rlfw_msgs__msg__JointCtrl__Sequence__copy(
  const rlfw_msgs__msg__JointCtrl__Sequence * input,
  rlfw_msgs__msg__JointCtrl__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rlfw_msgs__msg__JointCtrl);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rlfw_msgs__msg__JointCtrl * data =
      (rlfw_msgs__msg__JointCtrl *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rlfw_msgs__msg__JointCtrl__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rlfw_msgs__msg__JointCtrl__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rlfw_msgs__msg__JointCtrl__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
