#pragma once
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>

#define CAN_STANDARD 0x00U
#define CAN_RTR 0x01U
#define CAN_EXTENDED 0x02U
#define CAN_FD 0x04U
#define CAN_BRS 0x08U
#define CAN_ESI 0x10U
#define CAN_ECHO 0x20U
#define CAN_ERRFRAME 0x40U
#define CAN_STATUS 0x80U

struct CANMSG {
  uint32_t ID;
  uint8_t MSGTYPE;
  uint8_t LEN;
  uint8_t DATA[8];
};

class BaseCAN {
public:
  BaseCAN(){};
  int channel = -1;
  std::string name;
  bool only_thread=false;
  virtual bool send(uint16_t /*CANx*/, CANMSG* /*msg*/)=0;
  virtual std::tuple<bool, CANMSG> read(uint16_t /*CANx*/)=0;

  bool send(CANMSG* msg){
    return send(channel,msg);
  };
  std::tuple<bool, CANMSG> read(){
    return read(channel);
  };
  //该总线上设备的id
  std::vector<int> devive_ids;
  static int getCANtype(uint8_t type){
    switch (type) {
      case 0:return CAN_STANDARD;
      case 1:return CAN_EXTENDED;
      default:return CAN_STANDARD;
    }
  };
};
