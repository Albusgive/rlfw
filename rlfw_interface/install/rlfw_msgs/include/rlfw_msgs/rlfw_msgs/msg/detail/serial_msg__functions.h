// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from rlfw_msgs:msg/SerialMsg.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__FUNCTIONS_H_
#define RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "rlfw_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "rlfw_msgs/msg/detail/serial_msg__struct.h"

/// Initialize msg/SerialMsg message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * rlfw_msgs__msg__SerialMsg
 * )) before or use
 * rlfw_msgs__msg__SerialMsg__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
bool
rlfw_msgs__msg__SerialMsg__init(rlfw_msgs__msg__SerialMsg * msg);

/// Finalize msg/SerialMsg message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
void
rlfw_msgs__msg__SerialMsg__fini(rlfw_msgs__msg__SerialMsg * msg);

/// Create msg/SerialMsg message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * rlfw_msgs__msg__SerialMsg__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
rlfw_msgs__msg__SerialMsg *
rlfw_msgs__msg__SerialMsg__create();

/// Destroy msg/SerialMsg message.
/**
 * It calls
 * rlfw_msgs__msg__SerialMsg__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
void
rlfw_msgs__msg__SerialMsg__destroy(rlfw_msgs__msg__SerialMsg * msg);

/// Check for msg/SerialMsg message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
bool
rlfw_msgs__msg__SerialMsg__are_equal(const rlfw_msgs__msg__SerialMsg * lhs, const rlfw_msgs__msg__SerialMsg * rhs);

/// Copy a msg/SerialMsg message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
bool
rlfw_msgs__msg__SerialMsg__copy(
  const rlfw_msgs__msg__SerialMsg * input,
  rlfw_msgs__msg__SerialMsg * output);

/// Initialize array of msg/SerialMsg messages.
/**
 * It allocates the memory for the number of elements and calls
 * rlfw_msgs__msg__SerialMsg__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
bool
rlfw_msgs__msg__SerialMsg__Sequence__init(rlfw_msgs__msg__SerialMsg__Sequence * array, size_t size);

/// Finalize array of msg/SerialMsg messages.
/**
 * It calls
 * rlfw_msgs__msg__SerialMsg__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
void
rlfw_msgs__msg__SerialMsg__Sequence__fini(rlfw_msgs__msg__SerialMsg__Sequence * array);

/// Create array of msg/SerialMsg messages.
/**
 * It allocates the memory for the array and calls
 * rlfw_msgs__msg__SerialMsg__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
rlfw_msgs__msg__SerialMsg__Sequence *
rlfw_msgs__msg__SerialMsg__Sequence__create(size_t size);

/// Destroy array of msg/SerialMsg messages.
/**
 * It calls
 * rlfw_msgs__msg__SerialMsg__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
void
rlfw_msgs__msg__SerialMsg__Sequence__destroy(rlfw_msgs__msg__SerialMsg__Sequence * array);

/// Check for msg/SerialMsg message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
bool
rlfw_msgs__msg__SerialMsg__Sequence__are_equal(const rlfw_msgs__msg__SerialMsg__Sequence * lhs, const rlfw_msgs__msg__SerialMsg__Sequence * rhs);

/// Copy an array of msg/SerialMsg messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_rlfw_msgs
bool
rlfw_msgs__msg__SerialMsg__Sequence__copy(
  const rlfw_msgs__msg__SerialMsg__Sequence * input,
  rlfw_msgs__msg__SerialMsg__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // RLFW_MSGS__MSG__DETAIL__SERIAL_MSG__FUNCTIONS_H_
