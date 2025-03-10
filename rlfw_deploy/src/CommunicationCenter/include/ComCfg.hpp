#pragma once
#include "gamepad.h"
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
    if (id == -1) {
      std::cout << "no id" << std::endl;
      return false;
    }
    if (joint_name == "") {
      std::cout << "no joint_name" << std::endl;
      return false;
    }
    bool flag = true;
    flag = flag && (type != Motortype::ERR);
    if (!flag)
      std::cout << joint_name + " type:" << magic_enum::enum_name(type)
                << std::endl;
    flag = flag && (ctrl_type != MotorCtrlType::ERR);
    if (!flag)
      std::cout << joint_name + " ctrl_type:"
                << magic_enum::enum_name(ctrl_type) << std::endl;
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
    if (name == "") {
      std::cout << "com no name" << std::endl;
      return false;
    }
    bool flag = true;
    flag = flag && (type != ComType::ERR);
    if (!flag)
      std::cout << name + " type:" << magic_enum::enum_name(type) << std::endl;
    switch (type) {
    case ComType::pcan: {
      if (channel == 0) {
        std::cout << name + " pcan no channel" << std::endl;
        flag = false;
      }
      break;
    }
    case ComType::serial: {
      if (port == "" && attrs == "") {
        std::cout << name + " serial parameters on enough" << std::endl;
        flag = false;
      }
      break;
    }
    case ComType::canable: {
      if (channel == 0) {
        std::cout << name + " canable no channel" << std::endl;
        flag = false;
      }
      break;
    }
    case ComType::ERR: {
      std::cout << name + " Invalid ComCfg type" << std::endl;
      flag = false;
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
  bool check()
  {
    if (name == "") {
      std::cout << "remote no name" << std::endl;
      return false;
    }
    if(type == RemoteType::ERR)
    {
      std::cout << "remote type err" << std::endl;
      return false;
    }
    return true;
  }
};
