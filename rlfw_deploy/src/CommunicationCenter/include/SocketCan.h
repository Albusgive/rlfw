#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include "BaseCAN.h"
#include <functional>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <thread>

class SocketCan : public BaseCAN {

public:
  SocketCan();
  ~SocketCan();

  bool connect();

  bool send(uint16_t /*CANx*/, CANMSG *msg) override;
  std::pair<bool, CANMSG> receive(uint16_t /*CANx*/) override;

  void connectDecode(std::function<void(CANMSG &, std::vector<int> &motor_ids,
                                        std::string &name,int)>
                         lambda) override;
  void RunRecv() override;
  void closeRecv();

private:
  std::function<void(CANMSG &, std::vector<int> &, std::string &,int )>
      decode_lambda = [=](CANMSG, std::vector<int>, std::string,int ) {
        std::cout << "pcan no bind decode" << std::endl;
      };
  int sock;
};
