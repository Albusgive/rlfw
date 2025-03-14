#pragma once
#include "magic_enum/magic_enum.hpp"
#include <iostream>
#include <string>
#include <vector>

enum class ComType {
  pcan,
  serial,
  canable,
  ERR,
};

enum class Motortype { Mi, DM, RM, UNITREE, ERR };

// CFourBL ：CoaxialFourBarLinkage(双电机同轴) FourBL :FourBarLinkage(单电机)
// FiveBL :FiveBarLinkage(双电机)
enum class VirtualMotortype { CFourBL, FourBL, FiveBL, ERR };

// 控制模式
enum class MotorCtrlType { MIT = 0, POS, VEL, TORQUE, POS_VEL, ENABLE, ERR };

enum class RemoteType { gamepad, keyboard, custom, ERR };

class XMLMotor {
public:
  int id = -1; // 电机实际ID
  Motortype type;
  MotorCtrlType ctrl_type;
  std::string joint_name;
  bool invert = false;

  // 电机参数 发给电机的 -1为未定义
  float PosKP = -1.0;
  float PosKD = -1.0;
  float VelKP = -1.0;
  float VelKI = -1.0;
  float TorqueKP = -1.0;
  float TorqueKI = -1.0;
  float SafeTorque = -1.0;
  float SafePos = -1.0;
  float SafeVel = -1.0;
  bool check() {
    bool flag = true;
    if (id == -1) {
      std::cout << "no id" << std::endl;
      flag = flag && false;
    }
    if (joint_name == "") {
      std::cout << "motor no joint_name" << std::endl;
      flag = flag && false;
    }
    if (type == Motortype::ERR) {
      std::cout << joint_name + " type err" << std::endl;
      flag = flag && false;
    }
    if (ctrl_type == MotorCtrlType::ERR) {
      std::cout << joint_name + " ctrl_type err"<< std::endl;
      flag = flag && false;
    }
    return flag;
  }
};

class XMLVirtualMotor {
public:
  VirtualMotortype type;
  std::string joint_name;
  std::string motor1 = "";
  std::string motor2 = "";
  std::vector<float> ln;
  float default_theta;
  bool terminal=false;
  bool check() {
    bool flag = true;
    if (joint_name == "") {
      std::cout << "virtualmotor no joint_name" << std::endl;
      flag = flag && false;
    }
    switch (type) {
    case VirtualMotortype::CFourBL: {
      if (motor1 == "" && motor2 == "") {
        std::cout << "virtualmotor no virtualmotor no enough motor"
                  << std::endl;
        flag = flag && false;
      }
      break;
    }
    case VirtualMotortype::FourBL: {
      if (motor1 == "") {
        std::cout << "virtualmotor no virtualmotor no motor1" << std::endl;
        flag = flag && false;
      }
      break;
    }
    case VirtualMotortype::FiveBL: {
      if (motor1 == "" && motor2 == "") {
        std::cout << "virtualmotor no virtualmotor no enough motor"
                  << std::endl;
        flag = flag && false;
      }
      break;
    }
    case VirtualMotortype::ERR: {
      std::cout << joint_name + " type: ERR" << std::endl;
      flag = flag && false;
    }
    }
    return flag;
  }
};

class ComCfg {
public:
  std::string name = "";
  ComType type = ComType::ERR;
  bool only_thred = false; // 独立线程
  std::vector<XMLMotor> xml_motors;
  /*--------can--------*/
  int channel = 0; // can通道
  /*--------serial--------*/
  std::string attrs = ""; // 串口号
  std::string port = "";  // 端口名tty
  int bps;                // 115200
  int datasize;           // 5/6/7/8
  int parity;             // 0/1/2 无/奇/偶
  int stopbit;            // 1/2

  bool check() {
    bool flag = true;
    if (name == "") {
      std::cout << "com no name" << std::endl;
      flag = flag && false;
    }
    if (type == ComType::ERR) {
      std::cout << name + " type err"<< std::endl;
      flag = flag && false;
    }
    switch (type) {
    case ComType::pcan: {
      if (channel <= 0) {
        std::cout << name + " pcan channel err" << std::endl;
        flag = flag && false;
      }
      break;
    }
    case ComType::serial: {
      if (port == "" && attrs == "") {
        std::cout << name + " serial parameters on enough" << std::endl;
        flag = flag && false;
      }
      break;
    }
    case ComType::canable: {
      if (channel <= 0) {
        std::cout << name + " canable channel err" << std::endl;
        flag = flag && false;
      }
      break;
    }
    case ComType::ERR: {
      std::cout << name + "no Invalid ComCfg type" << std::endl;
      flag = flag && false;
      break;
    }
    }
    return flag;
  }
};

class XMLRemote {
public:
  RemoteType type;
  std::string name;
  int channel = 0;
  bool check() {
    bool flag = true;
    if (name == "") {
      std::cout << "remote no name" << std::endl;
      flag = flag && false;
    }
    if (type == RemoteType::ERR) {
      std::cout << "remote type err" << std::endl;
      flag = flag && false;
    }
    return flag;
  }
  std::vector<std::string> key;
};
