# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_motor_ctrl_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED motor_ctrl_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(motor_ctrl_FOUND FALSE)
  elseif(NOT motor_ctrl_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(motor_ctrl_FOUND FALSE)
  endif()
  return()
endif()
set(_motor_ctrl_CONFIG_INCLUDED TRUE)

# output package information
if(NOT motor_ctrl_FIND_QUIETLY)
  message(STATUS "Found motor_ctrl: 0.0.0 (${motor_ctrl_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'motor_ctrl' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${motor_ctrl_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(motor_ctrl_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${motor_ctrl_DIR}/${_extra}")
endforeach()
