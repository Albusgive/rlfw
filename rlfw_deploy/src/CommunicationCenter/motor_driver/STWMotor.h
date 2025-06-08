#pragma once
#include "BaseCAN.h"
#include "ComCfg.hpp"
#include "Motor.hpp"
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
/*
xml中ctrltype选择POS，VEL，TORQUE 但是控制指令选择MIT
*/


// ==================== 常量定义 ====================
const uint32_t HEARTBEAT_ID = 0x001;
const uint32_t ESTOP_ID = 0x002;
const uint32_t RXSDO_ID = 0x004;
const uint32_t SET_AXIS_NODE_ID = 0x006;
const uint32_t SET_STATE_ID = 0x007;
const uint32_t MIT_CONTROL_ID = 0x008;
const uint32_t SET_CTRL_MODE_ID = 0x00B;
const uint32_t SET_POS_ID = 0x00C;
const uint32_t SET_VEL_ID = 0x00D;
const uint32_t SET_POS_GAIN_ID = 0x01A;
const uint32_t SET_VEL_GAINS_ID = 0x01B;
const uint32_t ENCODER_FEEDBACK_ID = 0x009;
const uint32_t CURRENT_FEEDBACK_ID = 0x014;

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
class STWCANMsg : public CANMSG {
public:
  STWCANMsg() = default;
  STWCANMsg(const CANMSG &base_msg) : CANMSG(base_msg) {}
  void print() {
    std::cout << "ID: 0x" << std::hex << std::uppercase << this->ID << std::dec
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

class STWMotor : public CANMotor {
public:
  STWMotor();
  ~STWMotor();

  STWCANMsg *enableMotor(uint8_t motor_id, bool enable,
                        bool clear_fault = false) override;
  MotorBack decode(CANMSG msg) override;
  // 运动控制
  STWCANMsg *locomotion(uint8_t motor_id, float torque, float pos, float ang_vel,
                       float kp, float kd) override;
  // 设置运行模式
  STWCANMsg *setCtrlType(uint8_t motor_id);
  // 位置
  STWCANMsg *ctrl_pos(uint8_t motor_id, float pos) override { return nullptr; };
  // 速度
  STWCANMsg *ctrl_vel(uint8_t motor_id, float vel) override { return nullptr; };
  // 速度位置
  STWCANMsg *ctrl_pos_vel(uint8_t motor_id, float pos, float vel) override {
    return nullptr;
  };
  // 扭矩
  STWCANMsg *ctrl_torque(uint8_t motor_id, float torque) override {
    return nullptr;
  };
  /*--------电机参数设置----*/
  STWCANMsg *clearErr(uint8_t motor_id) override;
  STWCANMsg *setZeroPoint(uint8_t motor_id) override;
  STWCANMsg *setPosKP(uint8_t motor_id, float kp) override { return nullptr; };
  STWCANMsg *setPosKD(uint8_t motor_id, float kd) override { return nullptr; };
  // 速度PI
  STWCANMsg *setVelKP(uint8_t motor_id, float kp) override { return nullptr; };
  STWCANMsg *setVelKI(uint8_t motor_id, float ki) override { return nullptr; };
  // 扭矩/电流PI
  STWCANMsg *setTorqueKP(uint8_t motor_id, float kp) override {
    return nullptr;
  };
  STWCANMsg *setTorqueKI(uint8_t motor_id, float ki) override {
    return nullptr;
  };
  // 设置安全扭矩/电流
  STWCANMsg *setSafeTorque(uint8_t motor_id, float torque) override {
    return nullptr;
  };
  STWCANMsg *setSafePos(uint8_t motor_id, float pos) override {
    return nullptr;
  };
  STWCANMsg *setSafeVel(uint8_t motor_id, float vel) override {
    return nullptr;
  };

private:
  STWCANMsg stw_can_msg;
};
