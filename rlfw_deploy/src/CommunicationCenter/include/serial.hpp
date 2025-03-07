#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <string>

#include <dirent.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#include <thread>

#include <iostream>
#include <list>
#include <libudev.h>
#include <termios.h> 
#include <vector>
#include <queue>
#include <atomic>
#include <functional>

const long long RecvBufferLen = 1024;   //设置接收数据缓冲区大小


/*
使用时需要用libudev库  sudo apt-get install libudev-dev
装好后CMakeLists
target_link_libraries(your_project/your_node udev)
*/
typedef enum
{
    _2400,
    _4800,
    _9600,
    _19200,
    _38400,
    _57600,
    _115200,
    _460800,
}E_BaudRate;  //波特率 没有的去 termios-baud.h找

typedef enum
{
    _5,
    _6,
    _7,
    _8,
}E_DataSize;  //数据位

typedef enum
{
    None,
    Odd,
    Even,
}E_Parity;  //校验位

typedef enum
{
    _1,
    _2,
}E_StopBit;  //停止位

class Serial
{
public:
    Serial();
    ~Serial();

    bool OpenSerial(std::string SerialID, E_BaudRate Bps, E_DataSize DataSize, E_Parity Parity, E_StopBit StopBit);
    // 发送函数
    int Send(const void*Buff, int length);

    // 接收函数
    int Recv(unsigned char *Buff, int length);
    void Close();

    //寻找端口 返回设备列表
    std::list<std::string> getComList();
    //寻找设备和串口号并打印
    void search_device_serial();

    //寻找属性->ATTRS{serial}  返回/dev/ttyUSB*设备名称
    std::string get_attrs_serial(const std::string& attrs_serial);

    std::vector<char> recv_queue;

    //串口接收 OpenSerial中默认打开
    void RunRecv();
    //绑定解码
    void connectDecode(std::function<void()> lambda);
    
private:
    int last_size;
    std::atomic_bool is_recv{false};
    void decode();
    std::function<void()> decode_lambda=[=](){std::cout<<"no bind decode"<<std::endl;};


    int RefreshBuffer(unsigned char *pBuf, int Len, bool RecvTypet);

    //寻找端口
    std::string get_driver(const std::string& tty);
    void register_comport(std::list<std::string>& comList, std::list<std::string>& comList8250, const std::string& dir);
    void probe_serial8250_comports(std::list<std::string>& comList, std::list<std::string> comList8250);

    //用在get_attrs_serial中，根据usb设备路径在tty中寻找ttyUSB*设备
    std::string search_usb_port(std::string search_path);
private:
    int nSerialID;  //串口

    bool b_OpenSign;   //串口打开标志

    struct termios ProtoOpt;   //存放串口原始配置
};
