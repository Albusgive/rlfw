#pragma once
#include "BaseCAN.h"
#include "controlcan.h"
#include <atomic>
#include <functional>
#include <iostream>
#include <libudev.h>
#include <termios.h>
#include <tuple>
#include <unistd.h> // 在gcc编译器中，使用的头文件因gcc版本的不同而不同
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <thread>

#define USBCAN_I 3  // USBCAN-I/I+ 3
#define USBCAN_II 4 // USBCAN-II/II+ 4
#define MAX_CHANNELS 2
#define RX_WAIT_TIME 100
#define RX_BUFF_SIZE 1000

class ZCAN_USBCAN : public BaseCAN {
public:
  ZCAN_USBCAN();
  ~ZCAN_USBCAN();
  int DevType = USBCAN_II;
  int sub_can_channel = 0;
  bool initZCAN_USBCAN();

  bool send(uint16_t CANx, CANMSG *msg) override;
  bool send(CANMSG *msg);
  std::pair<bool, CANMSG> receive(uint16_t CANx) override;

  void connectDecode(std::function<void(CANMSG &, std::vector<int> &motor_ids,
                                        std::string &name, int decoder_idx)>
                         lambda) override;
  // 独立接受线程
  void RunRecv() override;
  void closeRecv();

private:
  std::function<void(CANMSG &, std::vector<int> &, std::string &, int)>
      decode_lambda = [=](CANMSG, std::vector<int>, std::string, int) {
        std::cout << "ZCAN_USBCAN no bind decode" << std::endl;
      };
};
