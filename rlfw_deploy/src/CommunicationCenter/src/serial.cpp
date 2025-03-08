#include "serial.hpp"
Serial::Serial()
{
    b_OpenSign = false;
    nSerialID = 0;
}

Serial::~Serial()
{
    Close();
}

// 开启串口
bool Serial::OpenSerial(std::string SerialID, E_BaudRate Bps, E_DataSize DataSize, E_Parity Parity, E_StopBit StopBit)
{
    // Close();
    nSerialID = open(SerialID.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (-1 == nSerialID)
    {
        /* 不能打开串口一*/
        std::string str = SerialID + " open fail !!!";
        perror(str.c_str());
        return false;
    }
    struct termios Opt;
    tcgetattr(nSerialID, &ProtoOpt); // 获取设备当前的设置

    Opt = ProtoOpt;

    /*设置输入输出波特率*/
    switch (Bps)
    {
    case E_BaudRate::_2400:
        cfsetispeed(&Opt, B2400);
        cfsetospeed(&Opt, B2400);
        break;
    case E_BaudRate::_4800:
        cfsetispeed(&Opt, B4800);
        cfsetospeed(&Opt, B4800);
        break;
    case E_BaudRate::_9600:
        cfsetispeed(&Opt, B9600);
        cfsetospeed(&Opt, B9600);
        break;
    case E_BaudRate::_19200:
        cfsetispeed(&Opt, B19200);
        cfsetospeed(&Opt, B19200);
        break;
    case E_BaudRate::_38400:
        cfsetispeed(&Opt, B38400);
        cfsetospeed(&Opt, B38400);
        break;
    case E_BaudRate::_57600:
        cfsetispeed(&Opt, B57600);
        cfsetospeed(&Opt, B57600);
        break;
    case E_BaudRate::_115200:
        cfsetispeed(&Opt, B115200);
        cfsetospeed(&Opt, B115200);
        break;
    case E_BaudRate::_460800:
        cfsetispeed(&Opt, B460800);
        cfsetospeed(&Opt, B460800);
        break;
    default:
        printf("Don't exist baudrate %d !\n", Bps);
        return false;
    }

    /*设置数据位*/
    Opt.c_cflag &= (~CSIZE);
    switch (DataSize)
    {
    case E_DataSize::_5:
        Opt.c_cflag |= CS5;
        break;
    case E_DataSize::_6:
        Opt.c_cflag |= CS6;
    case E_DataSize::_7:
        Opt.c_cflag |= CS7;
        break;
    case E_DataSize::_8:
        Opt.c_cflag |= CS8;
        break;
    default:
        /*perror("Don't exist iDataSize !");*/
        printf("Don't exist DataSize %d !\n", DataSize);
        return false;
    }

    /*设置校验位*/
    switch (Parity)
    {
    case E_Parity::None: /*无校验*/
        Opt.c_cflag &= (~PARENB);
        break;
    case E_Parity::Odd: /*奇校验*/
        Opt.c_cflag |= PARENB;
        Opt.c_cflag |= PARODD;
        Opt.c_iflag |= (INPCK | ISTRIP);
        break;
    case E_Parity::Even: /*偶校验*/
        Opt.c_cflag |= PARENB;
        Opt.c_cflag &= (~PARODD);
        Opt.c_iflag |= (INPCK | ISTRIP);
        break;
    default:
        /*perror("Don't exist cParity  !");*/
        printf("Don't exist Parity %c !\n", Parity);
        return false;
    }

    /*设置停止位*/

    switch (StopBit)
    {
    case E_StopBit::_1:
        Opt.c_cflag &= (~CSTOPB);
        break;
    case E_StopBit::_2:
        Opt.c_cflag |= CSTOPB;
        break;
    default:
        printf("Don't exist iStopBit %d !\n", StopBit);
        return false;
    }

    // 如果只是串口传输数据，而不需要串口来处理，那么使用原始模式(Raw Mode)方式来通讯，设置方式如下：
    Opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    Opt.c_oflag &= ~OPOST;

    tcflush(nSerialID, TCIOFLUSH); /*刷新输入队列(TCIOFLUSH为刷新输入输出队列)*/

    Opt.c_cc[VTIME] = 0; /*设置等待时间*/
    Opt.c_cc[VMIN] = 0;  /*设置最小字符*/

    int Result = tcsetattr(nSerialID, TCSANOW, &Opt); // 使这些设置生效

    if (Result)
    {
        perror("Set new terminal description error !");
        return false;
    }

    b_OpenSign = true;

    RunRecv();

    return true;
};

int Serial::Send(const void *Buff, int length)
{
    int iLen = 0;
    if (length <= 0)
    {
        // printf("Send byte number error !\n");
        std::cout << "Send byte number error !" << std::endl;
        return -1;
    }
    iLen = write(nSerialID, Buff, length);

    return iLen;
}

int Serial::Recv(unsigned char *Buff, int length)
{
    int res = RefreshBuffer(Buff, length, true);

    return res;
}

void Serial::Close()
{
    if (nSerialID > 0)
    {
        tcsetattr(nSerialID, TCSADRAIN, &ProtoOpt); // 恢复原始串口配置
    }
    close(nSerialID);
    b_OpenSign = false;
}
/*寻找端口-------------------------------------*/
std::string Serial::get_driver(const std::string &tty)
{
    struct stat st;
    std::string devicedir = tty;

    // Append '/device' to the tty-path
    devicedir += "/device";

    // Stat the devicedir and handle it if it is a symlink
    if (lstat(devicedir.c_str(), &st) == 0 && S_ISLNK(st.st_mode))
    {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        // Append '/driver' and return basename of the target
        devicedir += "/driver";

        if (readlink(devicedir.c_str(), buffer, sizeof(buffer)) > 0)
            return basename(buffer);
    }
    return "";
}
void Serial::register_comport(std::list<std::string> &comList, std::list<std::string> &comList8250, const std::string &dir)
{
    // Get the driver the device is using
    std::string driver = get_driver(dir);
    // Skip devices without a driver
    if (driver.size() > 0)
    {
        std::string devfile = std::string("/dev/") + basename(dir.c_str());

        // Put serial8250-devices in a seperate list
        if (driver == "serial8250")
        {
            comList8250.push_back(devfile);
        }
        else
            comList.push_back(devfile);
    }
}
void Serial::probe_serial8250_comports(std::list<std::string> &comList, std::list<std::string> comList8250)
{
    struct serial_struct serinfo;
    std::list<std::string>::iterator it = comList8250.begin();

    // Iterate over all serial8250-devices
    while (it != comList8250.end())
    {

        // Try to open the device
        int fd = open((*it).c_str(), O_RDWR | O_NONBLOCK | O_NOCTTY);

        if (fd >= 0)
        {
            // Get serial_info
            if (ioctl(fd, TIOCGSERIAL, &serinfo) == 0)
            {
                // If device type is no PORT_UNKNOWN we accept the port
                if (serinfo.type != PORT_UNKNOWN)
                    comList.push_back(*it);
            }
            close(fd);
        }
        it++;
    }
}
std::list<std::string> Serial::getComList()
{
    int n;
    struct dirent **namelist;
    std::list<std::string> comList;
    std::list<std::string> comList8250;
    const char *sysdir = "/sys/class/tty/";

    // Scan through /sys/class/tty - it contains all tty-devices in the system
    n = scandir(sysdir, &namelist, NULL, NULL);
    if (n < 0)
        perror("scandir");
    else
    {
        while (n--)
        {
            if (strcmp(namelist[n]->d_name, "..") && strcmp(namelist[n]->d_name, "."))
            {

                // Construct full absolute file path
                std::string devicedir = sysdir;
                devicedir += namelist[n]->d_name;
                // Register the device
                register_comport(comList, comList8250, devicedir);
            }
            free(namelist[n]);
        }
        free(namelist);
    }

    // Only non-serial8250 has been added to comList without any further testing
    // serial8250-devices must be probe to check for validity
    probe_serial8250_comports(comList, comList8250);

    // Return the lsit of detected comports
    return comList;
}
/*寻找端口----------------------------*/
void Serial::search_device_serial()
{
    // 创建udev对象
    struct udev *udev = udev_new();
    if (!udev)
    {
        printf("Failed to create udev\n");
        return;
    }
    // 创建udev_enumerate 用于遍历udev设备
    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    // 确定遍历设备类型
    udev_enumerate_add_match_subsystem(enumerate, "usb");
    // 扫描设备添加到 enumerate中
    udev_enumerate_scan_devices(enumerate);
    // 创建设备列表
    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    // 遍历设备列表
    struct udev_list_entry *entry;
    udev_list_entry_foreach(entry, devices)
    {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);
        if (dev)
        {
            // 获取设备的名称
            const char *devName = udev_device_get_devnode(dev);
            printf("设备名称: %s\n", devName);
            // 获取设备的路径
            const char *devPath = udev_device_get_devpath(dev);
            printf("设备路径: %s\n", devPath);
            // 打印设备串口号
            const char *serial = udev_device_get_sysattr_value(dev, "serial");
            printf("serial:%s\n", serial);
            std::cout << "----------------------------------" << std::endl;
            udev_device_unref(dev);
        }
    }
    udev_enumerate_unref(enumerate);
    udev_unref(udev);
    delete udev;
    delete enumerate;
    delete devices;
    delete entry;
}
std::string Serial::get_attrs_serial(const std::string &attrs_serial)
{
    bool search_flag = false;
    // 创建udev对象
    struct udev *udev = udev_new();
    if (!udev)
    {
        printf("Failed to create udev\n");
        return "null";
    }
    // 创建udev_enumerate 用于遍历udev设备
    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    // 确定遍历设备类型
    udev_enumerate_add_match_subsystem(enumerate, "usb");
    // 扫描设备添加到 enumerate中
    udev_enumerate_scan_devices(enumerate);
    // 创建设备列表
    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    // 遍历设备列表
    struct udev_list_entry *entry;
    udev_list_entry_foreach(entry, devices)
    {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);
        if (dev)
        {
            // udev_device_get_xxx_xxx都是获取设备属性的函数(udev_devices设备)
            // udev_device_get_sysattr_value是获取属性值的函数 ATTRS{属性}
            const char *serial = udev_device_get_sysattr_value(dev, "serial");
            if (serial)
            {
                std::string str(serial);
                if (str == attrs_serial)
                {
                    std::cout << "serial-----" << str << std::endl;
                    // 获取设备的路径
                    const char *devPath = udev_device_get_devpath(dev);
                    // 获取设备的名称
                    // const char *devName = udev_device_get_devnode(dev);
                    // printf("设备路径: %s\n", devPath);
                    // printf("设备名称: %s\n", devName);
                    std::cout << "设备名" << search_usb_port(devPath) << std::endl;
                    return search_usb_port(devPath);
                    std::cout << "----------------------------------" << std::endl;
                    search_flag = true;
                }
            }
            udev_device_unref(dev);
        }
    }
    if (!search_flag)
    {
        std::cout << "No search device" << std::endl;
    }
    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    delete udev;
    delete enumerate;
    delete devices;
    delete entry;
}
std::string Serial::search_usb_port(std::string search_path)
{
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *entry;

    // 创建 udev 上下文
    udev = udev_new();
    if (!udev)
    {
        printf("无法创建 udev 上下文！\n");
        return "null";
    }

    // 创建枚举器并添加匹配规则
    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "tty");
    udev_enumerate_scan_devices(enumerate);

    // 获取设备列表
    devices = udev_enumerate_get_list_entry(enumerate);

    // 遍历设备列表
    udev_list_entry_foreach(entry, devices)
    {
        const char *path;
        struct udev_device *dev;

        // 获取设备路径
        path = udev_list_entry_get_name(entry);

        // 根据设备路径创建设备对象
        dev = udev_device_new_from_syspath(udev, path);
        if (dev)
        {
            const char *devpath;

            // 获取设备的父设备路径
            devpath = udev_device_get_devpath(dev);

            // 判断设备的父设备路径是否匹配目标路径
            if (((std::string)devpath).find(search_path) != std::string::npos)
            {
                const char *devnode;

                // 获取设备节点路径
                devnode = udev_device_get_devnode(dev);
                if (devnode)
                {
                    return devnode;
                }
            }

            // 释放结构体内存
            udev_device_unref(dev);
        }
    }

    // 释放资源
    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    delete udev;
    delete enumerate;
    delete devices;
    delete entry;
}
void Serial::RunRecv()
{
    std::thread ThRecv = std::thread{
        [&]()
        {
            unsigned char RecvBuf[4096] = {0};
            while (b_OpenSign)
            {

                if (last_size == recv_queue.size())
                {
                    usleep(10 * 1000);
                    is_recv.store(true);
                }
                if ((nSerialID < 0))
                {
                    continue;
                }
                memset(RecvBuf, 0, 4096);
                int res = read(nSerialID, RecvBuf, sizeof(RecvBuf));
                if (res > 0)
                {
                    is_recv.store(false);
                    for (int i = 0; i < res; i++)
                    {
                        recv_queue.push_back(RecvBuf[i]);
                        //std::cout<<(int)RecvBuf[i]<<" ";
                    }
                    //std::cout<<std::endl;
                }
                last_size = recv_queue.size();
                decode();
            }
        }};

    ThRecv.detach();
}

void Serial::decode()
{
    if(recv_queue.size()==0)
    {
        return ;
    }
    if(!is_recv.load())
    {
        return ;
    }
    decode_lambda();
    // for(auto it:recv_queue)
    // {
    //     std::cout <<it<<" ";
    // }
    recv_queue.clear();
    std::cout<<std::endl;
}

void Serial::connectDecode(std::function<void()> lambda)
{
    decode_lambda = lambda;
}

int Serial::RefreshBuffer(unsigned char *pBuf, int Len, bool RecvTypet)
{
    static unsigned char Buffer[RecvBufferLen + 1] = {0};
    static int nSum = 0; //	缓冲区中数据总长度
    signed int nStop = 0;

    int ren = 0;

    if (false == RecvTypet)
    {
        //************************ 将接收到的数据加入缓冲区中 ************************/
        // std::cout<<"recv = "<< Len <<std::endl;

        if ((Len + nSum) <= RecvBufferLen) //	总长度小于1K
        {
            memcpy(&Buffer[nSum], pBuf, Len);
            nSum = Len + nSum;
        }
        else
        {
            if (Len <= RecvBufferLen) //	拷贝满1K空间，丢弃掉aucT[0]开始的字符，并进行填充，!!!!!!!!!!!
            {
                memcpy(Buffer, pBuf, Len);
                nSum = Len;
            }
            else //	本次接收到的数据长度大于1K
            {
                memcpy(Buffer, pBuf + (Len - RecvBufferLen), RecvBufferLen);
                nSum = RecvBufferLen;
            }
        }
        // std::cout<<"----> nSum = "<< nSum <<std::endl;
        ren = 0;
    }
    else
    {
        if (Len <= 0)
        {
            return -1;
        }
        if (nSum <= 0)
        {
            return 0;
        }

        if (Len <= nSum)
        {
            memcpy(pBuf, Buffer, Len);

            nStop = Len;
            ren = Len;
        }
        else
        {
            memcpy(pBuf, Buffer, nSum);

            nStop = nSum;
            ren = nSum;
        }

        //************ 移动取出数据 ***************/
        if (nStop == 0)
        {
            return 0;
        }
        else if (nSum > nStop) // 把没有解析到的数据移动到最开始位置
        {
            for (int i = 0; i < (nSum - nStop); i++)
            {
                Buffer[i] = Buffer[nStop + i];
            }
            nSum = nSum - nStop;
        }
        else if (nSum == nStop)
        {
            nSum = 0;
        }
    }

    return ren;
}
