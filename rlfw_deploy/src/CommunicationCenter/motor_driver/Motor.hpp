#pragma once
#include "BaseCAN.h"
#include "magic_enum/magic_enum.hpp"
#include <iostream>
#include <memory>
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
  std::string joint_name;
  float angle;
  float number_laps; // 圈数
  float ang_vel;
  float torque;
  float current;
  float temperature; // 摄氏度

  MotorWarning warning = MotorWarning::Normal;
  void print() {
    std::cout << "id: " << id << std::endl;
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

class CANMotor {
public:
  int id = -1;
  // MIT motor_id , torque, pos, ang_vel, kp, kd
  virtual CANMSG *locomotion(uint8_t /*motor_id*/, float /*torque*/,
                             float /*pos*/, float /*ang_vel*/, float /*kp*/,
                             float /*kd*/) = 0;
  // 位置
  virtual CANMSG *ctrl_pos(uint8_t /*motor_id*/, float /*pos*/) = 0;
  // 速度
  virtual CANMSG *ctrl_vel(uint8_t /*motor_id*/, float /*vel*/) = 0;
  // 速度位置
  virtual CANMSG *ctrl_pos_vel(uint8_t /*motor_id*/, float /*pos*/,
                               float /*vel*/) = 0;
  // 扭矩/电流
  virtual CANMSG *ctrl_torque(uint8_t /*motor_id*/, float /*torque*/) = 0;
  // 电机使能/失能 清除错误
  virtual CANMSG *enableMotor(uint8_t /*motor_id*/, bool /*enable*/,
                              bool /*clear_fault*/ = false) = 0;
  /*--------电机参数设置--------*/
  // 位置PD
  virtual CANMSG *setPosKP(uint8_t /*motor_id*/, float /*kp*/) = 0;
  virtual CANMSG *setPosKD(uint8_t /*motor_id*/, float /*kd*/) = 0;
  // 速度PI
  virtual CANMSG *setVelKP(uint8_t /*motor_id*/, float /*kp*/) = 0;
  virtual CANMSG *setVelKI(uint8_t /*motor_id*/, float /*ki*/) = 0;
  // 扭矩/电流PI
  virtual CANMSG *setTorqueKP(uint8_t /*motor_id*/, float /*kp*/) = 0;
  virtual CANMSG *setTorqueKI(uint8_t /*motor_id*/, float /*ki*/) = 0;
  // 设置安全扭矩/电流
  virtual CANMSG *setSafeTorque(uint8_t /*motor_id*/, float /*torque*/) = 0;
  virtual CANMSG *setSafePos(uint8_t /*motor_id*/, float /*pos*/) = 0;
  virtual CANMSG *setSafeVel(uint8_t /*motor_id*/, float /*vel*/) = 0;

  /*--------电机返回解码--------*/
  virtual MotorBack decode(CANMSG /*msg*/) = 0;
  std::shared_ptr<BaseCAN> can;
  void locomotion(float torque, float pos, float ang_vel, float kp, float kd) {
    can->send(can->channel, locomotion(id, torque, pos, ang_vel, kp, kd));
  }
  void ctrl_pos(float pos) { can->send(can->channel, ctrl_pos(id, pos)); }
  void ctrl_vel(float vel) { can->send(can->channel, ctrl_vel(id, vel)); }
  void ctrl_pos_vel(float pos, float vel) {
    can->send(can->channel, ctrl_pos_vel(id, pos, vel));
  }
  void ctrl_torque(float torque) {
    can->send(can->channel, ctrl_torque(id, torque));
  }
  void enableMotor(bool enable, bool clear_fault = false) {
    can->send(can->channel, enableMotor(id, enable, clear_fault));
  }
  /*----------设置电机参数----------*/
  void setPosKP(float kp) {
    if (kp == -1)
      return;
    can->send(can->channel, setPosKP(id, kp));
  }
  void setPosKD(float kd) {
    if (kd == -1)
      return;
    can->send(can->channel, setPosKD(id, kd));
  }
  void setVelKP(float kp) {
    if (kp == -1)
      return;
    can->send(can->channel, setVelKP(id, kp));
  }
  void setVelKI(float ki) {
    if (ki == -1)
      return;
    can->send(can->channel, setVelKI(id, ki));
  }
  void setTorqueKP(float kp) {
    if (kp == -1)
      return;
    can->send(can->channel, setTorqueKP(id, kp));
  }
  void setTorqueKI(float ki) {
    if (ki == -1)
      return;
    can->send(can->channel, setTorqueKI(id, ki));
  }
  void setSafeTorque(float torque) {
    if (torque == -1)
      return;
    can->send(can->channel, setSafeTorque(id, torque));
  }
  void setSafePos(float pos) {
    if (pos == -1)
      return;
    can->send(can->channel, setSafePos(id, pos));
  }
  void setSafeVel(float vel) {
    if (vel == -1)
      return;
    can->send(can->channel, setSafeVel(id, vel));
  }
};

class XXMotor {
};