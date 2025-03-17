#include "AgentNode.h"
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/utilities.hpp>
int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<AgentNode>("nz_agent");

  rclcpp::spin(node);
  rclcpp::shutdown();
}