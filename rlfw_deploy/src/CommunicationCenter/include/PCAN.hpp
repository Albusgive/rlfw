#pragma once
#include "BaseCAN.h"
#include "PCANBasic.h"
#include <atomic>
#include <functional>
#include <iostream>
#include <libudev.h>
#include <termios.h>
#include <tuple>
#include <unistd.h> // 在gcc编译器中，使用的头文件因gcc版本的不同而不同
#include <vector>

// PCAN-USB interface, channel
#define PCAN_NONEBUS 0x00U
#define PCAN1 0x51U
#define PCAN2 0x52U
#define PCAN3 0x53U
#define PCAN4 0x54U
#define PCAN5 0x55U
#define PCAN6 0x56U
#define PCAN7 0x57U
#define PCAN8 0x58U
#define PCAN9 0x509U
#define PCAN10 0x50AU
#define PCAN11 0x50BU
#define PCAN12 0x50CU
#define PCAN13 0x50DU
#define PCAN14 0x50EU
#define PCAN15 0x50FU
#define PCAN16 0x510U

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

// USB最多挂8路CAN
struct PChannel {
  TPCANHandle CAN1, CAN2, CAN3, CAN4, CAN5, CAN6, CAN7, CAN8;
};

// USB 端口映射值
template <typename T> class USBHubPort {
public:
  T port1;
  T port2;
  T port3;
  T port4;
};

class PCAN : public BaseCAN {
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
  // 从PCAN的id来映射通道
  PChannel findPChannel();
  // 寻找所有能用的PCAN并初始化 返回可用CAN通道
  std::vector<TPCANHandle> initAvailableCAN();

  void send(uint16_t CANx, CANMSG *msg) override;
  std::tuple<bool, CANMSG> read(uint16_t CANx) override;

  void connectDecode(std::function<void(CANMSG&,std::vector<int>& motor_ids,std::string& name)> lambda);
  // 独立接受线程
  void RunRecv();
  void closeRecv();

private:
  std::vector<TPCANHandle> tpcan;
  std::vector<TPCANHandle> available;
  int compareStrNum(std::string str1, std::string str2);

  void print(TPCANMsg msg);
  std::function<void(CANMSG&,std::vector<int>&,std::string&)> decode_lambda = [=](CANMSG,std::vector<int>,std::string) {
    std::cout << "pcan no bind decode" << std::endl;
  };
  std::atomic_bool is_only_thread{false};   //端口打开标志

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
