#include "ZCAN_USBCAN.hpp"
#include <thread>

ZCAN_USBCAN::ZCAN_USBCAN() {}

ZCAN_USBCAN::~ZCAN_USBCAN() { is_only_thread.store(false); }

bool ZCAN_USBCAN::initZCAN_USBCAN() {
  // 打开设备
  if (!VCI_OpenDevice(DevType, channel, 0)) {
    printf("Open device fail\n");
    return 0;
  }
  for (int i = 0; i < sub_channel.size(); i++) {
    VCI_INIT_CONFIG config;
    config.AccCode = 0;
    config.AccMask = 0xffffffff;
    config.Reserved = 0;
    config.Filter = 1;
    int Baud = 0x1c00; // 波特率 0x1400-1M(75%), 0x1c00-500k(87.5%),
                       // 0x1c01-250k(87.5%), 0x1c03-125k(87.5%)
    switch (sub_bps[i]) {
    case CANBps::Brt_1M:
      Baud = 0x1400;
      break;
    case CANBps::Brt_500k:
      Baud = 0x1c00;
      break;
    case CANBps::Brt_250k:
      Baud = 0x1c01;
      break;
    case CANBps::Brt_125k:
      Baud = 0x1c03;
      break;
    }
    config.Timing0 = Baud & 0xff; // 0x00
    config.Timing1 = Baud >> 8;   // 0x1c
    config.Mode = 0;

    if (!VCI_InitCAN(DevType, sub_channel[i], channel, &config)) {
      printf("InitCAN(%d) fail\n", i);
      return false;
    }
    printf("InitCAN(%d) success\n", i);

    if (!VCI_StartCAN(DevType, channel, i)) {
      printf("StartCAN(%d) fail\n", i);
      return false;
    }
    printf("StartCAN(%d) success\n", i);
  }
  return true;
}

bool ZCAN_USBCAN::send(uint16_t CANx, CANMSG *msg) {
  if (msg == nullptr) {
    std::cout << "send msg is nullptr" << std::endl;
    return false;
  }
  VCI_CAN_OBJ can_data;
  can_data.ID = msg->ID;   // id
  can_data.SendType = 0;   // 发送方式 0-正常, 1-单次, 2-自发自收
  can_data.RemoteFlag = 0; // 0-数据帧 1-远程帧
  can_data.ExternFlag = 0; // 0-数据帧 1-远程帧
  switch (msg->MSGTYPE) {
  case CAN_STANDARD:
    break;
  case CAN_EXTENDED:
    can_data.ExternFlag = 1;
    break;
  }
  can_data.DataLen = msg->LEN; // 数据长度 1~8
  for (int i = 0; i < can_data.DataLen; i++)
    can_data.Data[i] = msg->DATA[i];
  int test_num = VCI_Transmit(DevType, channel, CANx, &can_data, 1);
  if (test_num == 1)
    return true;
  else
    return false;
}

bool ZCAN_USBCAN::send(CANMSG *msg) {
  if (msg == nullptr) {
    std::cout << "send msg is nullptr" << std::endl;
    return false;
  }
  VCI_CAN_OBJ can_data;
  can_data.ID = msg->ID;   // id
  can_data.SendType = 0;   // 发送方式 0-正常, 1-单次, 2-自发自收
  can_data.RemoteFlag = 0; // 0-数据帧 1-远程帧
  can_data.ExternFlag = 0; // 0-数据帧 1-远程帧
  switch (msg->MSGTYPE) {
  case CAN_STANDARD:
    break;
  case CAN_EXTENDED:
    can_data.ExternFlag = 1;
    break;
  }
  can_data.DataLen = msg->LEN; // 数据长度 1~8
  for (int i = 0; i < can_data.DataLen; i++)
    can_data.Data[i] = msg->DATA[i];
  int test_num = VCI_Transmit(DevType, channel, sub_can_channel, &can_data, 1);
  if (test_num == 1)
    return true;
  else
    return false;
}

std::pair<bool, CANMSG> ZCAN_USBCAN::receive(uint16_t CANx) {
  VCI_CAN_OBJ can_buff[10];
  int count = VCI_GetReceiveNum(DevType, channel,
                                sub_can_channel); // 获取缓冲区报文数量
  if (count > 0) {
    int rcount = VCI_Receive(DevType, channel, sub_can_channel, can_buff, 10,
                             RX_WAIT_TIME); // 读报文
    CANMSG msg;
    msg.ID = can_buff[rcount - 1].ID;
    msg.LEN = can_buff[rcount - 1].DataLen;
    msg.MSGTYPE = CAN_STANDARD;
    if (can_buff[rcount - 1].ExternFlag == 1)
      msg.MSGTYPE = CAN_EXTENDED;
    memcpy(msg.DATA, can_buff[rcount - 1].Data, msg.LEN);
  }
  return {false, CANMSG()};
}

void ZCAN_USBCAN::connectDecode(
    std::function<void(CANMSG &, std::vector<int> &motor_ids, std::string &name,
                       int decoder_idx)>
        lambda) {
  decode_lambda = lambda;
}

void ZCAN_USBCAN::RunRecv() {
  is_only_thread.store(true);
  std::thread ThRecv = std::thread{[this]() {
    while (is_only_thread.load()) {
      auto [is, msg] = receive(channel);
      if (is) {
        decode_lambda(msg, devive_ids, this->name, decoder_idx);
      }
      // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }};
  ThRecv.detach();
}

void ZCAN_USBCAN::closeRecv() { is_only_thread.store(false); }