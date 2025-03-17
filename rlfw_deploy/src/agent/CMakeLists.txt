cmake_minimum_required(VERSION 3.8)
project(agent)

#对于AMD GPU 同时使用rocm的libtorch和opengl需要在终端添加
#export ROCM_PATH=/opt/rocm
#export LD_LIBRARY_PATH=$ROCM_PATH/lib:$LD_LIBRARY_PATH
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(PythonInterp REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(rlfw_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(Eigen3 REQUIRED)
# set(TORCH_FOLDER /home/albusgive/libtorch-cxx11-abi-shared-with-deps-2.6.0+rocm6.2.4/libtorch/share/cmake)
set(TORCH_FOLDER /home/albusgive2/libtorch-cxx11-abi-shared-with-deps-2.6.0+cu124/libtorch/share/cmake)
find_package(Torch REQUIRED PATHS ${TORCH_FOLDER} NO_DEFAULT_PATH)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/motor_cfg.xml" DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(agent
${SRC}
)

target_link_libraries(agent ${TORCH_LIBRARIES} ${EIGEN3_LIBS})
ament_target_dependencies(agent rclcpp example_interfaces rlfw_msgs tf2_geometry_msgs std_msgs sensor_msgs)
install(TARGETS
agent
  DESTINATION lib/${PROJECT_NAME}
)

# install(FILES motor_cfg.xml DESTINATION share)

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
