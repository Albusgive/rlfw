#include "mappingnode.h"
int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MappingNode>(
      "mujoco_mapping",
      "/home/albusgive2/rlfw/rlfw_deploy/src/mujoco_mapping/nz/scene.xml", 0.02,
      "nz_imu", "B");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
