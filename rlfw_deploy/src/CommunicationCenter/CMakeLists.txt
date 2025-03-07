cmake_minimum_required(VERSION 3.8)
project(CommunicationCenter)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(rlfw_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/motor_driver)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MOTOR ${CMAKE_CURRENT_SOURCE_DIR}/motor_driver/*.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/magic_enum)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/motor_cfg.xml" DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(CommunicationCenter
${SRC}
${MOTOR}
)
# 定义宏 PROJECT_NAME，值为当前 CMake 项目名
target_compile_definitions(CommunicationCenter 
  PRIVATE PROJECT_NAME="${PROJECT_NAME}"
)
target_link_libraries(CommunicationCenter udev libpcanbasic.so magic_enum::magic_enum tinyxml2)
ament_target_dependencies(CommunicationCenter rclcpp example_interfaces rlfw_msgs tf2_geometry_msgs std_msgs sensor_msgs)
install(TARGETS
CommunicationCenter
  DESTINATION lib/${PROJECT_NAME}
)
install(FILES motor_cfg.xml DESTINATION share)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
