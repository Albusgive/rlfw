#pragma once
#include <cstdint>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <dirent.h>
#include <linux/serial.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <thread>

#include <atomic>
#include <functional>
#include <iostream>
#include <libudev.h>
#include <list>
#include <queue>
#include <termios.h>
#include <unordered_map>
#include <vector>

const long long RecvBufferLen = 1024; // 设置接收数据缓冲区大小

/*
使用时需要用libudev库  sudo apt-get install libudev-dev
装好后CMakeLists
target_link_libraries(your_project/your_node udev)
*/

class Serial {
public:
  Serial();
  ~Serial();
  // 是否独立线程
  bool only_thread = false;
  std::string name;
  bool OpenSerial(std::string SerialPort, int Bps, int DataSize, int Parity,
                  int StopBit);
  // 发送函数
  int Send(const void *Buff, int length);
  int Send(const std::vector<uint8_t>& buffer);

  // 接收函数
  int Recv(unsigned char *Buff, int length);
  void Close();

  // 寻找端口 返回设备列表
  std::list<std::string> getComList();
  // 寻找设备和串口号并打印
  void search_device_serial();

  // 寻找属性->ATTRS{serial}  返回/dev/ttyUSB*设备名称
  std::string get_attrs_serial(const std::string &attrs_serial);

  std::vector<uint8_t> recv_queue;

  // 串口接收 OpenSerial中默认打开
  void RunRecv();
  // 绑定解码
  void connectDecode(std::function<void(std::vector<uint8_t>&,std::string&)> lambda);

private:
  int last_size;
  std::atomic_bool is_recv{false};
  void decode();
  std::function<void(std::vector<uint8_t>&,std::string&)> decode_lambda = [=](std::vector<uint8_t>&,std::string&) {
    std::cout << "no bind decode" << std::endl;
  };

  int RefreshBuffer(unsigned char *pBuf, int Len, bool RecvTypet);

  // 寻找端口
  std::string get_driver(const std::string &tty);
  void register_comport(std::list<std::string> &comList,
                        std::list<std::string> &comList8250,
                        const std::string &dir);
  void probe_serial8250_comports(std::list<std::string> &comList,
                                 std::list<std::string> comList8250);

  // 用在get_attrs_serial中，根据usb设备路径在tty中寻找ttyUSB*设备
  std::string search_usb_port(std::string search_path);

private:
  int nSerialID; // 串口

  bool b_OpenSign; // 串口打开标志

  struct termios ProtoOpt; // 存放串口原始配置

  std::unordered_map<int, int> baudrate_map = {
      {50, B50},           {75, B75},           {110, B110},
      {134, B134},         {150, B150},         {200, B200},
      {300, B300},         {600, B600},         {1200, B1200},
      {1800, B1800},       {2400, B2400},       {4800, B4800},
      {9600, B9600},       {19200, B19200},     {38400, B38400},
      {57600, B57600},     {115200, B115200},   {230400, B230400},
      {460800, B460800},   {500000, B500000},   {576000, B576000},
      {921600, B921600},   {1000000, B1000000}, {1152000, B1152000},
      {1500000, B1500000}, {2000000, B2000000}, {2500000, B2500000},
      {3000000, B3000000}, {3500000, B3500000}, {4000000, B4000000},
  };
};
