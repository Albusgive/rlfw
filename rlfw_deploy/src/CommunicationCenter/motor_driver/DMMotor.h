#pragma once
#include "Motor.hpp"
#include "PCANBasic.h"
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <cmath>

#define DM_P_MIN -12.5
#define DM_P_MAX 12.5
#define DM_V_MIN -45
#define DM_V_MAX 45
#define DM_KP_MIN 0
#define DM_KP_MAX 500
#define DM_KI_MIN 0
#define DM_KI_MAX 5
#define DM_KD_MIN 0
#define DM_KD_MAX 5
#define DM_T_MAX 18
#define DM_T_MIN -18

// CAN数据
class DMCANMsg : public TPCANMsg {
public:
  DMCANMsg() = default;
  DMCANMsg(const TPCANMsg &base_msg) : TPCANMsg(base_msg) {}
  void print() {
    std::cout << "Data: ";
    for (size_t i = 0; i < 8; i++) {
      std::cout << " 0x" << std::hex << std::uppercase << std::setw(2)
                << std::setfill('0') << static_cast<int>(this->DATA[i]);
    }
    std::cout << std::dec << std::endl;
  }
};

class DMMotor : public Motor {
public:
  DMMotor();
  ~DMMotor();

  DMCANMsg *enableMotor(uint8_t motor_id, bool enable, bool clear_fault = false) override;
  MotorBack decode(TPCANMsg msg) override;
  // 运动控制
  DMCANMsg *locomotion(uint8_t motor_id, float torque, float pos, float ang_vel,
                       float kp, float kd) override;

private:
  uint16_t float_to_uint(float x, float x_min, float x_max, int bits);
  float uint_to_float(int x_int, float x_min, float x_max, int bits);
  DMCANMsg dm_can_msg;
};
