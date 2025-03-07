#pragma once
#include "PCANBasic.h"
#include <atomic>
#include <iomanip>
#include <iostream>
#include <libudev.h>
#include <map>
#include <memory>
#include <mutex>
#include <termios.h>
#include <thread>
#include <tuple>
#include <unistd.h> // 在gcc编译器中，使用的头文件因gcc版本的不同而不同
#include <vector>

// PCAN-USB interface, channel
#define PCAN_NONEBUS 0x00U
#define CAN1 0x51U
#define CAN2 0x52U
#define CAN3 0x53U
#define CAN4 0x54U
#define CAN5 0x55U
#define CAN6 0x56U
#define CAN7 0x57U
#define CAN8 0x58U
#define CAN9 0x509U
#define CAN10 0x50AU
#define CAN11 0x50BU
#define CAN12 0x50CU
#define CAN13 0x50DU
#define CAN14 0x50EU
#define CAN15 0x50FU
#define CAN16 0x510U

#define BAUD_1MBPS 0x0014U   //   1 MBit/s
#define BAUD_800KBPS 0x0016U // 800 kBit/s
#define BAUD_500KBPS 0x001CU // 500 kBit/s
#define BAUD_250KBPS 0x011CU // 250 kBit/s
#define BAUD_125KBPS 0x031CU // 125 kBit/s
#define BAUD_100KBPS 0x432FU // 100 kBit/s
#define BAUD_95KBPS 0xC34EU  //  95,238 kBit/s
#define BAUD_83KBPS 0x852BU  //  83,333 kBit/s
#define BAUD_50KBPS 0x472FU  //  50 kBit/s
#define BAUD_47KBPS 0x1414U  //  47,619 kBit/s
#define BAUD_33KBPS 0x8B2FU  //  33,333 kBit/s
#define BAUD_20KBPS 0x532FU  //  20 kBit/s
#define BAUD_10KBPS 0x672FU  //  10 kBit/s
#define BAUD_5KBPS 0x7F7FU   //   5 kBit/s

#define STR(x) #x
// TPCANHandle Channel,
// TPCANBaudrate Btr0Btr1,

class CompensateAngle {
public:
  int m1 = -1;
  int m2 = -1;
  int m3 = -1;
  int m4 = -1;
  int m5 = -1;
  int m6 = -1;
  int m7 = -1;
  int m8 = -1;
  int m9 = -1;
  int m10 = -1;
  int m11 = -1;
  int m12 = -1;
  int m13 = -1;
  std::map<int, int> getCompensateAngle();
};
//USB最多挂8路CAN
struct PChannel {
  TPCANHandle PCAN1, PCAN2, PCAN3, PCAN4, PCAN5, PCAN6, PCAN7, PCAN8;
};

// USB 端口映射值
template <typename T> class USBHubPort {
public:
  T port1;
  T port2;
  T port3;
  T port4;
};

class PCAN {
public:
  PCAN();
  ~PCAN();
  /*初始化CAN通道之后才能使用，RM电机则initPCAN之后使用readRMMotor为一组通道*/
  bool initPCAN(TPCANHandle Channel, TPCANBaudrate Btr0Btr1);
  void readT(TPCANHandle CANx);

  /*以物理端口寻找PCAN设备，不是PCAN没有id，而是24块盗版更有性价比
      将PCAN挂载到HUB上，返回HUB对应端口及通道 USBTreePort对应物理端口
  */
  USBHubPort<TPCANHandle> findPCAN();
  //从PCAN的id来映射通道
  PChannel findPChannel();
  //寻找所有能用的PCAN并初始化 返回可用CAN通道
  std::vector<TPCANHandle> initAvailableCAN();

  void send(TPCANHandle CANx, TPCANMsg msg);
  std::tuple<bool, TPCANMsg> read(TPCANHandle CANx);

private:
  std::vector<TPCANHandle> tpcan;
  std::vector<TPCANHandle> available;
  int compareStrNum(std::string str1, std::string str2);

  void print(TPCANMsg msg);
  // // 线程列表 对应接收线程
  std::atomic<bool> thread_state{true};
  std::vector<std::thread> threads;
  std::vector<TPCANHandle> readmsgs_map;
  std::mutex mtx;

  // static void sendRMMotor(TPCANHandle CANx, DWORD ID, WORD M1, WORD M2, WORD
  // M3, WORD M4, bool is_open);
  // /*通道 发布者 消息帧id 电机类型
  // 获取RM电机直接打开即可 每个通道独立线程
  // */
  // void readRMMotor(TPCANHandle CANx,
  // rclcpp::Publisher<hongying_ctrl_msg::msg::MotorFeedback>::SharedPtr
  // publisher, std::string frame_id, MotorType motor_type, CompensateAngle
  // compensate_angle=CompensateAngle());
  //     //达妙给正逆时针旋转 逆时针选装位置数值增加

  // void addRMMotor(TPCANHandle CANx,
  // rclcpp::Publisher<hongying_ctrl_msg::msg::MotorFeedback>::SharedPtr
  // publisher, std::string frame_id, MotorType motor_type, CompensateAngle
  // compensate_angle=CompensateAngle()); std::thread rmmotro_rv_thread;
  // std::atomic<bool> rmmotro_rv_thread_state{true};
  // void runRMMotorRv();

  // //组合电机3508仍然是ID1-8，达妙与RM电机ID不冲突，不过数据不同
  // void addMotor(TPCANHandle CANx,
  // rclcpp::Publisher<hongying_ctrl_msg::msg::MotorFeedback>::SharedPtr
  // publisher, std::string frame_id, MotorType motor_type, CompensateAngle
  // compensate_angle=CompensateAngle());
};
