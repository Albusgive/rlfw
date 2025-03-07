#pragma once
#include "PCANBasic.h"
#include "magic_enum/magic_enum.hpp"
#include <iostream>
#include <string>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"

enum class MotorWarning {
  Normal = 0,
  Unenable,            // 未使能
  NoneCom,             // 通讯异常
  OverTemperature,     // 过温
  Overcurrent,         // 过流
  Overvoltage,         // 超压
  Undervoltage,        // 欠压
  MagneticEncoding,    // 磁编码异常
  HALLEncoding,        // HALL编码异常
  MosOverTemperature,  // MOS管过温
  CoilOverTemperature, // 线圈过温
  OverLoad,            // 过载
};

class MotorBack {
public:
  int id;
  float angle;
  float number_laps; // 圈数
  float ang_vel;
  float torque;
  float current;
  float temperature; // 摄氏度

  MotorWarning warning = MotorWarning::Normal;
  void print() {
    std::cout << "Motor ID: " << id << std::endl;
    std::cout << "Angle: " << angle << std::endl;
    std::cout << "Angular Velocity: " << ang_vel << std::endl;
    std::cout << "Torque: " << torque << std::endl;
    std::cout << "Current: " << current << std::endl;
    std::cout << "Temperature: " << temperature << std::endl;
    if (warning == MotorWarning::Normal) {
      std::cout << GREEN;
    } else {
      std::cout << YELLOW;
    }
    std::cout << "Motor: " << std::string(magic_enum::enum_name(warning))
              << RESET << std::endl;
  }
  MotorBack *invertMotor() {
    angle = -angle;
    number_laps = -number_laps;
    ang_vel = -ang_vel;
    torque = -torque;
    current = -current;
    return this;
  }
};

//电机参数
enum class MotorParameter {
  PosKP,
  PosKD,
  VelKP,
  VelKI,
  TorqueKP,
  TorqueKI,
  SafeTorque,
  SafePos,
  SafeVel
};

//控制模式
enum class MotorCtrlType { MIT, POS, VEL, TORQUE, POS_VEL };

class Motor {
public:
  // MIT
  virtual TPCANMsg *locomotion(uint8_t /*motor_id*/, float /*torque*/,
                               float /*pos*/, float /*ang_vel*/, float /*kp*/,
                               float /*kd*/) {
    return nullptr;
  };
  // 位置
  virtual TPCANMsg *ctrl_pos(uint8_t /*motor_id*/, float /*pos*/) {
    return nullptr;
  };
  // 速度
  virtual TPCANMsg *ctrl_vel(uint8_t /*motor_id*/, float /*vel*/) {
    return nullptr;
  };
  // 速度位置
  virtual TPCANMsg *ctrl_pos_vel(uint8_t /*motor_id*/, float /*pos*/,
                                 float /*vel*/) {
    return nullptr;
  };
  // 扭矩/电流
  virtual TPCANMsg *ctrl_torque(uint8_t /*motor_id*/, float /*torque*/) {
    return nullptr;
  };
  // 电机使能/失能 清除错误
  virtual TPCANMsg *enableMotor(uint8_t /*motor_id*/, bool /*enable*/,
                                bool /*clear_fault*/) {
    return nullptr;
  };
  /*--------电机参数设置--------*/
  // 位置PD
  virtual TPCANMsg *setPosKP(uint8_t /*motor_id*/, float /*kp*/) {
    return nullptr;
  };
  virtual TPCANMsg *setPosKD(uint8_t /*motor_id*/, float /*kd*/) {
    return nullptr;
  };
  // 速度PI
  virtual TPCANMsg *setVelKP(uint8_t /*motor_id*/, float /*kp*/) {
    return nullptr;
  };
  virtual TPCANMsg *setVelKI(uint8_t /*motor_id*/, float /*ki*/) {
    return nullptr;
  };
  // 扭矩/电流PI
  virtual TPCANMsg *setTorqueKP(uint8_t /*motor_id*/, float /*kp*/) {
    return nullptr;
  };
  virtual TPCANMsg *setTorqueKI(uint8_t /*motor_id*/, float /*ki*/) {
    return nullptr;
  };
  // 设置安全扭矩/电流
  virtual TPCANMsg *setSafeTorque(uint8_t /*motor_id*/, float /*torque*/) {
    return nullptr;
  };
  virtual TPCANMsg *setSafePos(uint8_t /*motor_id*/, float /*pos*/) {
    return nullptr;
  };
  virtual TPCANMsg *setSafeVel(uint8_t /*motor_id*/, float /*vel*/) {
    return nullptr;
  };

  /*--------电机返回解码--------*/
  virtual MotorBack decode(TPCANMsg /*msg*/) { return MotorBack(); };
};