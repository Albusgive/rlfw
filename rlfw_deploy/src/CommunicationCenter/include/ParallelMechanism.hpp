#pragma once
#include <cmath>
#include <utility>
// 并联机构解算
// 一切以逆时针为正 右手坐标系,y轴向外
namespace PM {
  std::pair<float, float> getFourBL(float theta1, float w1, float l1, float l2,
                                    float l3, float l4);
  std::pair<float, float> setFourBL(float theta3, float w3, float l1, float l2,
                                    float l3, float l4);
  }
