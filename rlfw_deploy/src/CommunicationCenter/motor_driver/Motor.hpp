#pragma once
#include "BaseCAN.h"
#include "ComCfg.hpp"
#include "ParallelMechanism.hpp"
#include "magic_enum/magic_enum.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "ComCfg.hpp"

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
  float vel;
  float torque;
  float current;
  float temperature; // 摄氏度

  MotorWarning warning = MotorWarning::Normal;
  void print() {
    std::cout << "id: " << id << std::endl;
    std::cout << "Angle: " << angle << std::endl;
    std::cout << "Angular Velocity: " << vel << std::endl;
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
    vel = -vel;
    torque = -torque;
    current = -current;
    return this;
  }
};

class UnitreeMsg {};

// 是电机解码器也是电机
class BaseMotor {
public:
  int id = -1;
  MotorBack motorback;
  bool invert = false;
  float default_=0; // 角度补偿
  std::string motor_name;
  std::string motor_type;
  MotorCtrlType ctrl_type;
  float torque_range[2] = {-9999, 9999};
  float vel_range[2] = {-9999, 9999};
  float pos_range[2] = {-9999, 9999};
  void setTorqueRange(float min_torque,float max_torque){
    torque_range[0]=min_torque;
    torque_range[1]=max_torque;
  };
  void setPosRange(float min_pos,float max_pos){
    pos_range[0]=min_pos;
    pos_range[1]=max_pos;
  };
  void setVelRange(float min_vel,float max_vel){
    vel_range[0]=min_vel;
    vel_range[1]=max_vel;
  };
  virtual void locomotion(float torque, float pos, float vel, float kp,
                          float kd) = 0;
  virtual void ctrl_pos(float pos) = 0;
  virtual void ctrl_vel(float vel) = 0;
  virtual void ctrl_pos_vel(float pos, float vel) = 0;
  virtual void ctrl_torque(float torque) = 0;
  virtual void enableMotor(bool enable, bool clear_fault = false) = 0;
  virtual void setPosKP(float kp) = 0;
  virtual void setPosKD(float kd) = 0;
  virtual void setVelKP(float kp) = 0;
  virtual void setVelKI(float ki) = 0;
  virtual void setTorqueKP(float kp) = 0;
  virtual void setTorqueKI(float ki) = 0;
  virtual void setSafeTorque(float torque) = 0;
  virtual void setSafePos(float pos) = 0;
  virtual void setSafeVel(float vel) = 0;
  virtual void setCtrlType() = 0;
  virtual MotorBack decode() = 0;
  virtual MotorBack decode(CANMSG /*msg*/) = 0;
  virtual MotorBack decode(UnitreeMsg /*msg*/) = 0;
  virtual std::vector<float> other() = 0;
  float clip(float data, float min, float max) {
    if (data > max) {
      return max;
    } else if (data < min) {
      return min;
    }
    return data;
  };
};

class CANMotor : public BaseMotor {
public:
  /*--------can电机专有虚函数--------*/
  //  MIT motor_id , torque, pos, vel, kp, kd
  virtual CANMSG *locomotion(uint8_t /*motor_id*/, float /*torque*/,
                             float /*pos*/, float /*vel*/, float /*kp*/,
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
  virtual CANMSG *setCtrlType(uint8_t /*motor_id*/) = 0;
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

  /*--------电机控制--------*/
  std::shared_ptr<BaseCAN> can;
  void locomotion(float torque, float pos, float vel, float kp,
                  float kd) override {
    float torque_ = clip(torque, torque_range[0], torque_range[1]);
    float pos_ = clip(pos, pos_range[0], pos_range[1]);
    float vel_ = clip(vel, vel_range[0], vel_range[1]);
    float angle = pos_ + default_;
    if (invert)
      can->send(can->channel, locomotion(id, -torque_, -angle, -vel_, kp, kd));
    else
      can->send(can->channel, locomotion(id, torque_, angle, vel_, kp, kd));
  }
  void ctrl_pos(float pos) override {
    float pos_ = clip(pos, pos_range[0], pos_range[1]);
    float angle = pos_ + default_;
    if (invert)
      can->send(can->channel, ctrl_pos(id, -angle));
    else
      can->send(can->channel, ctrl_pos(id, angle));
  }
  void ctrl_vel(float vel) override {
    float vel_ = clip(vel, vel_range[0], vel_range[1]);
    if (invert)
      can->send(can->channel, ctrl_vel(id, -vel_));
    else
      can->send(can->channel, ctrl_vel(id, vel_));
  }
  void ctrl_pos_vel(float pos, float vel) override {
    float pos_ = clip(pos, pos_range[0], pos_range[1]);
    float vel_ = clip(vel, vel_range[0], vel_range[1]);
    float angle = pos_ + default_;
    if (invert)
      can->send(can->channel, ctrl_pos_vel(id, -angle, -vel_));
    else
      can->send(can->channel, ctrl_pos_vel(id, angle, vel_));
  }
  void ctrl_torque(float torque) override {
    float torque_ = clip(torque, torque_range[0], torque_range[1]);
    if (invert)
      can->send(can->channel, ctrl_torque(id, -torque_));
    else
      can->send(can->channel, ctrl_torque(id, torque_));
  }
  void enableMotor(bool enable, bool clear_fault = false) override {
    can->send(can->channel, enableMotor(id, enable, clear_fault));
  }
  /*----------设置电机参数----------*/
  void setCtrlType() override {
    can->send(can->channel, setCtrlType(id));
  }
  void setPosKP(float kp) override {
    if (kp == -1)
      return;
    can->send(can->channel, setPosKP(id, kp));
  }
  void setPosKD(float kd) override {
    if (kd == -1)
      return;
    can->send(can->channel, setPosKD(id, kd));
  }
  void setVelKP(float kp) override {
    if (kp == -1)
      return;
    can->send(can->channel, setVelKP(id, kp));
  }
  void setVelKI(float ki) override {
    if (ki == -1)
      return;
    can->send(can->channel, setVelKI(id, ki));
  }
  void setTorqueKP(float kp) override {
    if (kp == -1)
      return;
    can->send(can->channel, setTorqueKP(id, kp));
  }
  void setTorqueKI(float ki) override {
    if (ki == -1)
      return;
    can->send(can->channel, setTorqueKI(id, ki));
  }
  void setSafeTorque(float torque) override {
    if (torque == -1)
      return;
    can->send(can->channel, setSafeTorque(id, torque));
  }
  void setSafePos(float pos) override {
    if (pos == -1)
      return;
    can->send(can->channel, setSafePos(id, pos));
  }
  void setSafeVel(float vel) override {
    if (vel == -1)
      return;
    can->send(can->channel, setSafeVel(id, vel));
  }
  // 没有用的虚函数
  MotorBack decode(UnitreeMsg /*msg*/) override { return MotorBack(); };
  MotorBack decode() override { return MotorBack(); };
  std::vector<float> other() override { return std::vector<float>(); };
};

// 虚拟电机
class VirtualMotor : public BaseMotor {
public:
  VirtualMotortype type = VirtualMotortype::ERR;
  /*--------电机控制--------*/
  bool terminal = false;        // 虚拟末端解算 角度,角速度,末端距离
  float default_theta = M_PI_4; // 默认45度
  std::shared_ptr<BaseMotor> motor1;
  std::shared_ptr<BaseMotor> motor2;
  float l[5] = {1.0, 1.0, 1.0, 1.0, 1.0};
  void locomotion(float, float pos, float vel, float kp, float kd) override {
    float pos_ = clip(pos, pos_range[0], pos_range[1]);
    float vel_ = clip(vel, vel_range[0], vel_range[1]);
    float angle = pos_ + default_;
    switch (type) {
    // 传进来的是虚拟关节期望角速度
    case VirtualMotortype::CFourBL: {
      // 共轴四连杆motor1是主关节，motor2是连杆关节 要获取两关节差motor2 -
      // motor1 作用到motor2上
      auto [theta1, w1] = PM::setFourBL(angle, vel_, l[0], l[1], l[2], l[3]);
      motor2->locomotion(0.0, theta1 + motor1->motorback.angle - default_theta,
                         w1 + motor1->motorback.vel, kp, kd);
      break;
    }
    case VirtualMotortype::FourBL: {
      // 非共轴四连杆由一个电机驱动为moto1
      auto [theta1, w1] = PM::setFourBL(angle, vel_, l[0], l[1], l[2], l[3]);
      motor1->locomotion(0.0, theta1, w1, kp, kd);
      break;
    }
    case VirtualMotortype::FiveBL: {
      // TODO
      break;
    }
    case VirtualMotortype::ERR: {
      break;
    }
    }
    update();
  }
  void ctrl_pos(float pos) override {
    float pos_ = clip(pos, pos_range[0], pos_range[1]);
    float angle = pos_ + default_;
    switch (type) {
    // 传进来的是虚拟关节期望角度
    case VirtualMotortype::CFourBL: {
      // 共轴四连杆motor1是主关节，motor2是连杆关节 要获取两关节差 theta1 +
      // motor1 - default_theta 作用到motor2上
      auto [theta1, w1] = PM::setFourBL(angle, 0.0, l[0], l[1], l[2], l[3]);
      motor2->ctrl_pos(theta1 + motor1->motorback.angle - default_theta);
      break;
    }
    case VirtualMotortype::FourBL: {
      // 非共轴四连杆由一个电机驱动为moto1
      auto [theta1, w1] = PM::setFourBL(angle, 0.0, l[0], l[1], l[2], l[3]);
      motor1->ctrl_pos(theta1);
      break;
    }
    case VirtualMotortype::FiveBL: {
      // TODO
      break;
    }
    case VirtualMotortype::ERR: {
      break;
    }
    }
    update();
  }
  void ctrl_vel(float vel) override {
    float vel_ = clip(vel, vel_range[0], vel_range[1]);
    switch (type) {
    // 传进来的是虚拟关节期望角速度
    case VirtualMotortype::CFourBL: {
      // 共轴四连杆motor1是主关节，motor2是连杆关节 要获取两关节差motor2 -
      // motor1 作用到motor2上
      auto [theta1, w1] = PM::setFourBL(0.0, vel_, l[0], l[1], l[2], l[3]);
      motor2->ctrl_vel(w1 + motor1->motorback.vel);
      break;
    }
    case VirtualMotortype::FourBL: {
      // 非共轴四连杆由一个电机驱动为moto1
      auto [theta1, w1] = PM::setFourBL(0.0, vel_, l[0], l[1], l[2], l[3]);
      motor1->ctrl_vel(w1);
      break;
    }
    case VirtualMotortype::FiveBL: {
      // TODO
      break;
    }
    case VirtualMotortype::ERR: {
      break;
    }
    }
    update();
  }
  void ctrl_pos_vel(float pos, float vel) override {
    float pos_ = clip(pos, pos_range[0], pos_range[1]);
    float vel_ = clip(vel, vel_range[0], vel_range[1]);
    float angle = pos_ + default_;
    switch (type) {
    // 传进来的是虚拟关节期望角速度
    case VirtualMotortype::CFourBL: {
      // 共轴四连杆motor1是主关节，motor2是连杆关节 要获取两关节差motor2 -
      // motor1 作用到motor2上
      auto [theta1, w1] = PM::setFourBL(angle, vel_, l[0], l[1], l[2], l[3]);
      motor2->ctrl_pos_vel(theta1 + motor1->motorback.angle - default_theta,
                           w1 + motor1->motorback.vel);
      break;
    }
    case VirtualMotortype::FourBL: {
      // 非共轴四连杆由一个电机驱动为moto1
      auto [theta1, w1] = PM::setFourBL(angle, vel_, l[0], l[1], l[2], l[3]);
      motor1->ctrl_pos_vel(theta1, w1);
      break;
    }
    case VirtualMotortype::FiveBL: {
      // TODO
      break;
    }
    case VirtualMotortype::ERR: {
      break;
    }
    }
    update();
  }
  void ctrl_torque(float) override {}
  void enableMotor(bool enable, bool clear_fault = false) override {
    motor1->enableMotor(enable, clear_fault);
    motor2->enableMotor(enable, clear_fault);
  }
  /*----------更新电机参数----------*/
  void update() {
    switch (type) {
    case VirtualMotortype::CFourBL: {
      float angle =
          motor2->motorback.angle + default_theta - motor1->motorback.angle;
      float w = motor2->motorback.vel - motor1->motorback.vel;
      auto [theta3, w3] = PM::getFourBL(angle, w, l[0], l[1], l[2], l[3]);
      motorback.angle = theta3 - default_;
      motorback.vel = w3;
      break;
    }
    case VirtualMotortype::FourBL: {
      // 非共轴四连杆由一个电机驱动为moto1
      auto [theta3, w3] =
          PM::getFourBL(motor1->motorback.angle, motor1->motorback.vel, l[0],
                        l[1], l[2], l[3]);
      motorback.angle = theta3 - default_;
      motorback.vel = w3;
      break;
    }
    case VirtualMotortype::FiveBL: {
      // TODO
      break;
    }
    case VirtualMotortype::ERR: {
      break;
    }
    }
  }
  // 计算终端
  std::vector<float> other() override {
    if (terminal)
      return PM::getFourBLT(motor1->motorback.angle, motor1->motorback.vel,
                            motorback.angle, motorback.vel, l[3], l[4]);
    else
      return std::vector<float>();
  }
  /*----------设置电机参数----------*/
  void setPosKP(float) override {}
  void setPosKD(float) override {}
  void setVelKP(float) override {}
  void setVelKI(float) override {}
  void setTorqueKP(float) override {}
  void setTorqueKI(float) override {}
  void setSafeTorque(float) override {}
  void setSafePos(float) override {}
  void setSafeVel(float) override {}
  // 没有用的虚函数
  MotorBack decode(CANMSG /*msg*/) override { return MotorBack(); };
  MotorBack decode(UnitreeMsg /*msg*/) override { return MotorBack(); };
  MotorBack decode() override { return MotorBack(); };
  void setCtrlType() override {};
};

class XXMotor {};