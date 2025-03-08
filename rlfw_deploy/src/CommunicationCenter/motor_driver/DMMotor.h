#pragma once
#include "BaseCAN.h"
#include "Motor.hpp"
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

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
class DMCANMsg : public CANMSG {
public:
  DMCANMsg() = default;
  DMCANMsg(const CANMSG &base_msg) : CANMSG(base_msg) {}
  void print() {
    std::cout << "ID: " << std::hex << std::uppercase << this->ID << std::dec
              << std::endl;
    std::cout << "LEN: " << static_cast<int>(this->LEN) << std::endl;
    std::cout << "TYPE: " << static_cast<int>(this->MSGTYPE) << std::endl;
    std::cout << "Data: ";
    for (size_t i = 0; i < 8; i++) {
      std::cout << " 0x" << std::hex << std::uppercase << std::setw(2)
                << std::setfill('0') << static_cast<int>(this->DATA[i]);
    }
    std::cout << std::dec << std::endl;
  }
};

class DMMotor : public CANMotor {
public:
  DMMotor();
  ~DMMotor();

  DMCANMsg *enableMotor(uint8_t motor_id, bool enable,
                        bool clear_fault = false) override;
  MotorBack decode(CANMSG msg) override;
  // 运动控制
  DMCANMsg *locomotion(uint8_t motor_id, float torque, float pos, float ang_vel,
                       float kp, float kd) override;

  // 位置
  DMCANMsg *ctrl_pos(uint8_t motor_id, float pos) { return nullptr; };
  // 速度
  DMCANMsg *ctrl_vel(uint8_t motor_id, float vel) { return nullptr; };
  // 速度位置
  DMCANMsg *ctrl_pos_vel(uint8_t motor_id, float pos, float vel) {
    return nullptr;
  };
  // 扭矩
  DMCANMsg *ctrl_torque(uint8_t motor_id, float torque) { return nullptr; };
  /*--------电机参数设置----*/
  DMCANMsg *setPosKP(uint8_t motor_id, float kp) { return nullptr; };
  DMCANMsg *setPosKD(uint8_t motor_id, float kd) { return nullptr; };
  // 速度PI
  DMCANMsg *setVelKP(uint8_t motor_id, float kp) { return nullptr; };
  DMCANMsg *setVelKI(uint8_t motor_id, float ki) { return nullptr; };
  // 扭矩/电流PI
  DMCANMsg *setTorqueKP(uint8_t motor_id, float kp) { return nullptr; };
  DMCANMsg *setTorqueKI(uint8_t motor_id, float ki) { return nullptr; };
  // 设置安全扭矩/电流
  DMCANMsg *setSafeTorque(uint8_t motor_id, float torque) { return nullptr; };
  DMCANMsg *setSafePos(uint8_t motor_id, float pos) { return nullptr; };
  DMCANMsg *setSafeVel(uint8_t motor_id, float vel) { return nullptr; };

private:
  uint16_t float_to_uint(float x, float x_min, float x_max, int bits);
  float uint_to_float(int x_int, float x_min, float x_max, int bits);
  DMCANMsg dm_can_msg;
};
