# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_rlfw_vz_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED rlfw_vz_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(rlfw_vz_FOUND FALSE)
  elseif(NOT rlfw_vz_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(rlfw_vz_FOUND FALSE)
  endif()
  return()
endif()
set(_rlfw_vz_CONFIG_INCLUDED TRUE)

# output package information
if(NOT rlfw_vz_FIND_QUIETLY)
  message(STATUS "Found rlfw_vz: 0.0.0 (${rlfw_vz_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'rlfw_vz' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${rlfw_vz_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(rlfw_vz_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${rlfw_vz_DIR}/${_extra}")
endforeach()
