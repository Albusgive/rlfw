#include "ParallelMechanism.hpp"
#include <cmath>
namespace PM {
// motor1直接控制l4角度(主关节) motor2控制小连杆l1(小关节) theta = motor2角度 +
// 两电机零点偏置角度 - motor1角度 w1 = motor2_w - motor1_w theta1 w1
// 设置内角解算出外角和角速度（观测）
std::pair<float, float> getFourBL(float theta1, float w1, float l1, float l2,
                                  float l3, float l4) {
  float l1_2 = l1 * l1;
  float l2_2 = l2 * l2;
  float l3_2 = l3 * l3;
  float l4_2 = l4 * l4;
  float len_2 = l1_2 + l4_2 - 2 * l1 * l4 * std::cos(theta1);
  float len = std::sqrt(len_2);
  float theta3_1 = std::acos((l1_2 - l4_2 - len_2) / -(2 * l4 * len));
  float theta3_2 = std::acos((l2_2 - l3_2 - len_2) / -(2 * l3 * len));
  // 目标角度
  float theta3 = M_PI - theta3_1 - theta3_2;
  float theta2_ = std::asin(l4 / l1 * std::sin(theta3_1)) +
                  std::asin(l3 / l2 * std::sin(theta3_2));
  float theta2 = theta2_ - (M_PI - theta1);
  // 角速度解算
  float w3 = (l2 * l1 * w1 *
              (std::cos(theta2) * std::sin(theta1) -
               std::sin(theta2) * std::cos(theta1))) /
             (l2 * l3 *
              (std::cos(theta2) * std::sin(theta3) -
               std::sin(theta2) * std::cos(theta3)));
  return {theta3, w3};
}
// 设置外角解算出内角（动作）角速度
std::pair<float, float> setFourBL(float theta3, float w3, float l1, float l2,
                                  float l3, float l4) {
  // 恢复成内角
  float theta3_ = M_PI - theta3;
  float l1_2 = l1 * l1;
  float l2_2 = l2 * l2;
  float l3_2 = l3 * l3;
  float l4_2 = l4 * l4;
  float len_2 = l3_2 + l4_2 - 2 * l3 * l4 * std::cos(theta3_);
  float len = std::sqrt(len_2);

  float theta1_1 = std::acos((l2_2 - l1_2 - len_2) / -(2 * l1 * len));
  float theta1_2 = std::acos((l3_2 - l4_2 - len_2) / -(2 * l4 * len));
  // 目标角度
  float theta1 = theta1_1 + theta1_2;
  float theta2_ = std::acos((len_2 - l1_2 - l2_2) / -(2 * l1 * l2));
  float theta2 = theta2_ - (M_PI - theta1);
  // 角速度
  float w1 = (l2 * l3 * w3 *
              (std::sin(theta2) * std::cos(theta3) -
               std::cos(theta2) * std::sin(theta3))) /
             (l1 * l2 *
              (std::sin(theta2) * std::cos(theta1) -
               std::cos(theta2) * std::sin(theta1)));
  return {theta1, w1};
}
// 长度,角度,角速度,末端线速度  一切坐标系皆以motor1原点
std::vector<float> getFourBLT(float motor1_theta, float motor1_w, float theta3,
                              float w3, float l4, float l5) {
  std::vector<float> terminal_pos;
  float rho = std::sqrt(l4 * l4 + l5 * l5 - 2 * l4 * l5 * std::cos(theta3));
  float theta_t = std::asin((l5 / rho) * std::sin(theta3));
  //角速度解算
  return {rho, motor1_theta - theta_t};
}
} // namespace PM