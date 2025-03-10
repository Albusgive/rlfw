// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rlfw_msgs:srv/ComParameter.idl
// generated code does not contain a copyright notice

#ifndef RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__STRUCT_HPP_
#define RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rlfw_msgs__srv__ComParameter_Request __attribute__((deprecated))
#else
# define DEPRECATED__rlfw_msgs__srv__ComParameter_Request __declspec(deprecated)
#endif

namespace rlfw_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ComParameter_Request_
{
  using Type = ComParameter_Request_<ContainerAllocator>;

  explicit ComParameter_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->request_communication_center_parameter = "";
    }
  }

  explicit ComParameter_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request_communication_center_parameter(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->request_communication_center_parameter = "";
    }
  }

  // field types and members
  using _request_communication_center_parameter_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _request_communication_center_parameter_type request_communication_center_parameter;

  // setters for named parameter idiom
  Type & set__request_communication_center_parameter(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->request_communication_center_parameter = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rlfw_msgs__srv__ComParameter_Request
    std::shared_ptr<rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rlfw_msgs__srv__ComParameter_Request
    std::shared_ptr<rlfw_msgs::srv::ComParameter_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ComParameter_Request_ & other) const
  {
    if (this->request_communication_center_parameter != other.request_communication_center_parameter) {
      return false;
    }
    return true;
  }
  bool operator!=(const ComParameter_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ComParameter_Request_

// alias to use template instance with default allocator
using ComParameter_Request =
  rlfw_msgs::srv::ComParameter_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace rlfw_msgs


#ifndef _WIN32
# define DEPRECATED__rlfw_msgs__srv__ComParameter_Response __attribute__((deprecated))
#else
# define DEPRECATED__rlfw_msgs__srv__ComParameter_Response __declspec(deprecated)
#endif

namespace rlfw_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ComParameter_Response_
{
  using Type = ComParameter_Response_<ContainerAllocator>;

  explicit ComParameter_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit ComParameter_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _device_name_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _device_name_type device_name;
  using _device_type_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _device_type_type device_type;

  // setters for named parameter idiom
  Type & set__device_name(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->device_name = _arg;
    return *this;
  }
  Type & set__device_type(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->device_type = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rlfw_msgs__srv__ComParameter_Response
    std::shared_ptr<rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rlfw_msgs__srv__ComParameter_Response
    std::shared_ptr<rlfw_msgs::srv::ComParameter_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ComParameter_Response_ & other) const
  {
    if (this->device_name != other.device_name) {
      return false;
    }
    if (this->device_type != other.device_type) {
      return false;
    }
    return true;
  }
  bool operator!=(const ComParameter_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ComParameter_Response_

// alias to use template instance with default allocator
using ComParameter_Response =
  rlfw_msgs::srv::ComParameter_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace rlfw_msgs

namespace rlfw_msgs
{

namespace srv
{

struct ComParameter
{
  using Request = rlfw_msgs::srv::ComParameter_Request;
  using Response = rlfw_msgs::srv::ComParameter_Response;
};

}  // namespace srv

}  // namespace rlfw_msgs

#endif  // RLFW_MSGS__SRV__DETAIL__COM_PARAMETER__STRUCT_HPP_
