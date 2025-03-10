#include "PCAN.hpp"
#include <thread>

PCAN::PCAN() {
  tpcan.push_back(PCAN1);
  tpcan.push_back(PCAN2);
  tpcan.push_back(PCAN3);
  tpcan.push_back(PCAN4);
  tpcan.push_back(PCAN5);
  tpcan.push_back(PCAN6);
  tpcan.push_back(PCAN7);
  tpcan.push_back(PCAN8);
}

PCAN::~PCAN() {
  is_only_thread.store(false);
}

bool PCAN::initPCAN(TPCANHandle CANx, TPCANBaudrate Btr0Btr1) {
  // 初始化 PCAN 通道
  TPCANStatus status = CAN_Initialize(CANx, Btr0Btr1);
  if (status != PCAN_ERROR_OK) {
    // std::cout << "Failed to initialize PCAN channel. Error: " << std::hex
    //           << status << std::endl;
    return false;
  }
  return true;
}

void PCAN::readT(TPCANHandle CANx) {
  TPCANMsg msg;
  TPCANTimestamp timestamp;
  TPCANStatus state = CAN_Read(CANx, &msg, &timestamp);
  if (state != PCAN_ERROR_OK) {
    std::cout << "Failed to read CAN message. Error: " << std::hex << state
              << std::endl;
  } else {
    // s十六进制打印
    std::cout << "Message ID: " << std::hex << msg.ID << std::endl;
    // std::cout << "Message ID: " << msg.ID << std::endl;
    std::cout << "Message MSGTYPE: " << msg.MSGTYPE << std::endl;
    std::cout << "Message Length: " << msg.LEN << std::endl;
    std::cout << "Message Data:";
    for (size_t i = 0; i < 8; i++) {
      std::cout << " " << (int)msg.DATA[i];
    }
    std::cout << std::endl;
    std::cout << "    Message Timestamp: " << timestamp.micros << std::endl;
  }
}

USBHubPort<TPCANHandle> PCAN::findPCAN() {
  struct udev *udev;
  struct udev_enumerate *enumerate;
  struct udev_list_entry *devices, *dev_list_entry;
  struct udev_device *dev;
  USBHubPort<TPCANHandle> usbhubport;
  usbhubport.port1 = PCAN_NONEBUS;
  usbhubport.port2 = PCAN_NONEBUS;
  usbhubport.port3 = PCAN_NONEBUS;
  usbhubport.port4 = PCAN_NONEBUS;
  std::vector<std::pair<int, std::string>> port_time;
  // 创建 udev_input 对象
  udev = udev_new();
  if (!udev) {
    fprintf(stderr, "无法创建 input udev\n");
  }

  // 创建一个input列举器对象
  enumerate = udev_enumerate_new(udev);
  udev_enumerate_add_match_subsystem(enumerate, "pcan");
  udev_enumerate_scan_devices(enumerate);
  devices = udev_enumerate_get_list_entry(enumerate);
  udev_list_entry_foreach(dev_list_entry, devices) {
    const char *path;
    path = udev_list_entry_get_name(dev_list_entry);
    dev = udev_device_new_from_syspath(udev, path);
    if (dev) {
      // 上电顺序
      const char *uptime =
          udev_device_get_property_value(dev, "USEC_INITIALIZED");
      // printf("    time %s\n", uptime);
      struct udev_device *parent =
          udev_device_get_parent_with_subsystem_devtype(dev, "usb",
                                                        "usb_device");
      // 物理端口
      const char *port = udev_device_get_sysname(parent);
      // printf("    parent type:%s\n", port);
      if (uptime != NULL && port != NULL) {
        std::string num(port);
        int idex = num.rfind(".");
        num = num.substr(idex + 1);
        int port_num = std::stoi(num);
        port_time.push_back(
            std::pair<int, std::string>(port_num, (std::string)uptime));
      }
    }
  }
  std::cout << "----------------------------------" << std::endl;
  // 按照h的第一个元素从小到大排序
  for (int i = 0; i < static_cast<int>(port_time.size()) - 1; i++) {
    for (int j = 0; j < static_cast<int>(port_time.size()) - 1 - i; j++) {
      if (compareStrNum(port_time[j].second, port_time[j + 1].second) == 1) {
        // std::cout << "hub端口" << port_time[j].first << " time" <<
        // port_time[j].second << std::endl; std::swap(port_time[j], port_time[j
        // + 1]);
        std::pair<int, std::string> temp = port_time[j];
        port_time[j] = port_time[j + 1];
        port_time[j + 1] = temp;
      }
    }
  }
  auto setchannel = [&](int i) {
    std::cout << "open:" << i << std::endl;
    switch (i) {
    case 0:
      return PCAN1;
      break;
    case 1:
      return PCAN2;
      break;
    case 2:
      return PCAN3;
      break;
    case 3:
      return PCAN4;
      break;
    default:
      return PCAN1;
      break;
    }
  };
  for (int i = 0; i < static_cast<int>(port_time.size()); i++) {
    switch (port_time[i].first) {
    case 1:
      usbhubport.port1 = setchannel(i);
      break;
    case 2:
      usbhubport.port2 = setchannel(i);
      break;
    case 3:
      usbhubport.port3 = setchannel(i);
      break;
    case 4:
      usbhubport.port4 = setchannel(i);
      break;
    default:
      break;
    }
    std::cout << "hub端口" << port_time[i].first << " time "
              << port_time[i].second << std::endl;
  }
  return usbhubport;
}

PChannel PCAN::findPChannel() {
  PChannel pc;
  auto setchannel = [&](int id, unsigned int channel) {
    std::cout << "id:" << id << " channel:" << channel << std::endl;
    switch (id) {
    case 1:
      pc.CAN1 = channel;
      break;
    case 2:
      pc.CAN2 = channel;
      break;
    case 3:
      pc.CAN3 = channel;
      break;
    case 4:
      pc.CAN4 = channel;
      break;
    case 5:
      pc.CAN5 = channel;
      break;
    case 6:
      pc.CAN6 = channel;
      break;
    case 7:
      pc.CAN7 = channel;
      break;
    case 8:
      pc.CAN8 = channel;
      break;
    default:
      break;
    }
  };
  for (auto i : tpcan) {
    bool is = initPCAN(i, BAUD_1MBPS);
    if (!is) {
      continue;
    }
    DWORD deviceId;
    if (CAN_GetValue(i, PCAN_DEVICE_ID, &deviceId, sizeof(deviceId)) ==
        PCAN_ERROR_OK) {
      std::cout << "设备ID: " << deviceId << std::endl;
      setchannel(deviceId, i);
    }
    // 关闭 PCAN 通道
    CAN_Uninitialize(i);
  }
  return pc;
}

std::vector<TPCANHandle> PCAN::initAvailableCAN() {
  available = std::vector<TPCANHandle>();
  for (auto i : tpcan) {
    bool is = initPCAN(i, BAUD_1MBPS);
    if (!is) {
      CAN_Uninitialize(i);
      continue;
    }
    available.push_back(i);
  }
  return available;
}

void PCAN::send(uint16_t CANx, CANMSG *msg) {
  if (msg == nullptr) {
    std::cout << "send msg is nullptr" << std::endl;
    return;
  }
  TPCANStatus status = CAN_Write(CANx, (TPCANMsg *)msg);
  if (status != PCAN_ERROR_OK) {
    std::cout << "Failed to write CAN message. Error: " << std::hex << status
              << std::endl;
  } else {
    // std::cout << "Send Success" << std::endl;
  }
}

std::tuple<bool, CANMSG> PCAN::read(uint16_t CANx) {
  TPCANMsg msg;
  TPCANTimestamp timestamp;
  TPCANStatus state = CAN_Read(CANx, &msg, &timestamp);
  if (state != PCAN_ERROR_OK) {
    return {false, *(CANMSG *)&msg};
    // std::cout << "Failed to read CAN message. Error: " << std::hex << state
    // << std::endl;
  } else {
    // s十六进制打印
    //  std::cout << "Message ID: " << std::hex << msg.ID << std::endl;
    //  //std::cout << "Message ID: " << msg.ID << std::endl;
    //  std::cout << "Message MSGTYPE: " << msg.MSGTYPE << std::endl;
    //  std::cout << "Message Length: " << msg.LEN << std::endl;
    //  std::cout << "Message Data:";
    //  for (size_t i = 0; i < 8; i++)
    //  {
    //  std::cout << " "<<(int)msg.DATA[i];
    //  }
    //  std::cout <<std::endl;
    //  std::cout<<"    Message Timestamp: " << timestamp.micros << std::endl;
    return {true, *(CANMSG *)&msg};
  }
}

void PCAN::connectDecode(std::function<void(CANMSG&,std::vector<int>& motor_ids,std::string& name)> lambda) {
  decode_lambda = lambda;
}

void PCAN::RunRecv() {
  is_only_thread.store(true);
  std::thread ThRecv = std::thread{[&]() {
    while (is_only_thread.load()) {
      auto [is, msg] = read(channel);
      if (is)
      {
        decode_lambda(msg,devive_ids,this->name);
      }
      // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }};
  ThRecv.detach();
}

void PCAN::closeRecv()
{
  is_only_thread.store(false);
}

int PCAN::compareStrNum(std::string str1, std::string str2) {
  if (str1.empty() || str2.empty()) {
    throw std::invalid_argument("String is empty");
  }
  if (str1.size() > str2.size()) {
    return 1;
  } else if (str1.size() < str2.size()) {
    return -1;
  } else {
    for (size_t i = 0; i < str1.size(); i++) {
      if (str1[i] > str2[i]) {
        return 1;
      } else if (str1[i] < str2[i]) {
        return -1;
      }
    }
  }
  return 0;
}

// void PCAN::sendRMMotor(TPCANHandle CANx, DWORD ID, WORD M1, WORD M2, WORD M3,
//                        WORD M4, bool is_open) {
//   if (!is_open) {
//     return;
//   }
//   // std::cout << "M1: " << M1 << " M2: " << M2 << " M3: " << M3 << " M4: "
//   <<
//   // M4 << std::endl;
//   TPCANMsg send;
//   send.ID = ID;
//   send.MSGTYPE = PCAN_MESSAGE_STANDARD;
//   send.LEN = 8;
//   send.DATA[0] = (char)(M1 >> 8) & 0xFF;
//   send.DATA[1] = (char)(M1 & 0xFF);
//   send.DATA[2] = (char)(M2 >> 8) & 0xFF;
//   send.DATA[3] = (char)(M2 & 0xFF);
//   send.DATA[4] = (char)(M3 >> 8) & 0xFF;
//   send.DATA[5] = (char)(M3 & 0xFF);
//   send.DATA[6] = (char)(M4 >> 8) & 0xFF;
//   send.DATA[7] = (char)(M4 & 0xFF);
//   TPCANStatus status = CAN_Write(CANx, &send);
//   if (status != PCAN_ERROR_OK) {
//     std::cout << "Failed to write CAN message. Error: " << std::hex << status
//               << std::endl;
//   } else {
//     // std::cout << "Send Success" << std::endl;
//   }
// }

// void PCAN::sendDMMotor(TPCANHandle CANx, int motor_id, float _pos, float
// _vel,
//                        float _KP, float _KD, float _torq, bool is_open) {
//   if (!is_open) {
//     return;
//   }
//   TPCANMsg send;
//   send.ID = motor_id;
//   send.MSGTYPE = PCAN_MESSAGE_STANDARD;
//   send.LEN = 8;
//   uint16_t pos_tmp, vel_tmp, kp_tmp, kd_tmp, tor_tmp;
//   pos_tmp = float_to_uint(_pos, DM_P_MIN, DM_P_MAX, 16);
//   vel_tmp = float_to_uint(_vel, DM_V_MIN, DM_V_MAX, 12);
//   kp_tmp = float_to_uint(_KP, DM_KP_MIN, DM_KP_MAX, 12);
//   kd_tmp = float_to_uint(_KD, DM_KD_MIN, DM_KD_MAX, 12);
//   tor_tmp = float_to_uint(_torq, DM_T_MIN, DM_T_MAX, 12);
//   send.DATA[0] = (pos_tmp >> 8);
//   send.DATA[1] = pos_tmp;
//   send.DATA[2] = (vel_tmp >> 4);
//   send.DATA[3] = ((vel_tmp & 0xF) << 4) | (kp_tmp >> 8);
//   send.DATA[4] = kp_tmp;
//   send.DATA[5] = (kd_tmp >> 4);
//   send.DATA[6] = ((kd_tmp & 0xF) << 4) | (tor_tmp >> 8);
//   send.DATA[7] = tor_tmp;
//   for (int i = 0; i < 8; i++) {
//     std::cout << " " << std::hex << (int)send.DATA[i];
//   }
//   TPCANStatus status = CAN_Write(PCAN_USBBUS1, &send);
//   if (status != PCAN_ERROR_OK) {
//     std::cout << "Failed to write CAN message. Error: " << std::hex << status
//               << std::endl;
//   } else {
//     // std::cout << "Send Success" << std::endl;
//   }
// }

// void PCAN::readRMMotor(
//     TPCANHandle CANx,
//     rclcpp::Publisher<hongying_ctrl_msg::msg::MotorFeedback>::SharedPtr
//         publisher,
//     std::string frame_id, MotorType motor_type,
//     CompensateAngle compensate_angle) {
//   bool is = initPCAN(CANx, BAUD_1MBPS);
//   if (!is) {
//     std::cout << "CAN " << CANx << "init failed" << std::endl;
//     return;
//   }
//   std::map<int, int> id_map_angle = compensate_angle.getCompensateAngle();
//   threads.emplace_back(std::thread([=]() {
//     while (thread_state.load()) {
//       TPCANMsg msg;
//       TPCANTimestamp timestamp;
//       TPCANStatus state = CAN_Read(CANx, &msg, &timestamp);
//       if (state != PCAN_ERROR_OK) {
//         // std::cout << "Failed to read CAN message. Error: " << std::hex <<
//         // state << std::endl;
//       } else {
//         // s十六进制打印
//         // std::cout << "Message ID: " << std::hex << msg.ID << std::endl;
//         hongying_ctrl_msg::msg::MotorFeedback motor;
//         motor.header.frame_id = frame_id;
//         motor.angle = (msg.DATA[0] << 8) | msg.DATA[1];
//         motor.speed = (msg.DATA[2] << 8) | msg.DATA[3];
//         motor.torque_current = (msg.DATA[4] << 8) | msg.DATA[5];
//         motor.temperature = msg.DATA[6];
//         // 角度补偿
//         auto is_compensate = id_map_angle.find(msg.ID);
//         if (is_compensate != id_map_angle.end()) {
//           motor.angle -= is_compensate->second;
//           if (motor.angle < 0)
//             motor.angle += 8191;
//         }
//         switch (motor_type) {
//         case C6X0: {
//           motor.motor_id = (int)msg.ID - 512;
//           std::cout << "M3508 ID: " << static_cast<int>(motor.motor_id)
//                     << std::endl;
//         } break;
//         case GM6020: {
//           motor.motor_id = (int)msg.ID - 512 - 4;
//           std::cout << "GM6020 ID: " << static_cast<int>(motor.motor_id)
//                     << std::endl;
//         } break;
//         case MERGE: {
//           motor.motor_id = (int)msg.ID - 512;
//           std::cout << "MERGE ID: " << static_cast<int>(motor.motor_id)
//                     << std::endl;
//         } break;
//         default:
//           break;
//         }
//         motor.angle = (msg.DATA[0] << 8) | msg.DATA[1];
//         motor.speed = (msg.DATA[2] << 8) | msg.DATA[3];
//         motor.torque_current = (msg.DATA[4] << 8) | msg.DATA[5];
//         motor.temperature = msg.DATA[6];
//         // if(motor.motor_id==1)
//         // {
//         std::cout << " Angle: " << std::dec << static_cast<int>(motor.angle)
//                   << " Speed: " << static_cast<int>(motor.speed)
//                   << " Torque Current: "
//                   << static_cast<int>(motor.torque_current)
//                   << " Temperature: " << static_cast<int>(motor.temperature)
//                   << std::endl;
//         // }
//         publisher->publish(motor);
//       }
//     }
//   }));
// }

// void PCAN::addRMMotor(
//     TPCANHandle CANx,
//     rclcpp::Publisher<hongying_ctrl_msg::msg::MotorFeedback>::SharedPtr
//         publisher,
//     std::string frame_id, MotorType motor_type,
//     CompensateAngle compensate_angle) {
//   bool is = initPCAN(CANx, BAUD_1MBPS);
//   if (!is) {
//     std::cout << "CAN " << CANx << "init failed" << std::endl;
//     return;
//   }
//   std::map<int, int> id_map_angle = compensate_angle.getCompensateAngle();
//   rmmotor_rvs.emplace_back([=]() {
//     TPCANMsg msg;
//     TPCANTimestamp timestamp;
//     TPCANStatus state = CAN_Read(CANx, &msg, &timestamp);
//     if (state != PCAN_ERROR_OK) {
//       // std::cout << "Failed to read CAN message. Error: " << std::hex <<
//       state
//       // << std::endl;
//     } else {
//       // s十六进制打印
//       // std::cout << "Message ID: " << std::hex << msg.ID << std::endl;

//       hongying_ctrl_msg::msg::MotorFeedback motor;
//       motor.header.frame_id = frame_id;
//       motor.angle = (msg.DATA[0] << 8) | msg.DATA[1];
//       motor.speed = (msg.DATA[2] << 8) | msg.DATA[3];
//       motor.torque_current = (msg.DATA[4] << 8) | msg.DATA[5];
//       motor.temperature = msg.DATA[6];
//       // 角度补偿
//       auto is_compensate = id_map_angle.find(msg.ID);
//       if (is_compensate != id_map_angle.end()) {
//         motor.angle -= is_compensate->second;
//         if (motor.angle < 0)
//           motor.angle += 8191;
//         // std::cout<<"补偿"<<static_cast<int>(motor.motor_id)<<"
//         // "<<motor.angle<<std::endl;
//       }
//       switch (motor_type) {
//       case C6X0: {
//         motor.motor_id = (int)msg.ID - 512;
//         // std::cout << "M3508 ID: " <<
//         // static_cast<int>(motor.motor_id)<<std::endl;
//       } break;
//       case GM6020: {
//         motor.motor_id = (int)msg.ID - 512 - 4;
//         // std::cout << "GM6020 ID: " << static_cast<int>(motor.motor_id) <<
//         // std::endl;
//       } break;
//       case MERGE: {
//         motor.motor_id = (int)msg.ID - 512;
//         std::cout << "MERGE ID: " << static_cast<int>(motor.motor_id)
//                   << std::endl;
//       } break;
//       default:
//         break;
//       }

//       // if(motor.motor_id==1)
//       // {
//       // std::cout<<" Angle: "<<std::dec << static_cast<int>(motor.angle)<<"
//       // Speed: "<< static_cast<int>(motor.speed)<<" Torque Current:
//       // "<<static_cast<int>(motor.torque_current)
//       // <<" Temperature: "<<static_cast<int>(motor.temperature)<<std::endl;
//       // }
//       publisher->publish(motor);
//     }
//   });
// }

// void PCAN::runRMMotorRv() {
//   rmmotro_rv_thread = std::thread([=]() {
//     while (rmmotro_rv_thread_state.load()) {
//       for (auto it = rmmotor_rvs.begin(); it != rmmotor_rvs.end(); it++) {
//         (*it)();
//       }
//     }
//   });
// }

// void PCAN::readDMMotor(
//     TPCANHandle CANx,
//     rclcpp::Publisher<hongying_ctrl_msg::msg::MotorFeedback>::SharedPtr
//         publisher,
//     std::string frame_id, MotorType motor_type,
//     CompensateAngle compensate_angle) {
//   bool is = initPCAN(CANx, BAUD_1MBPS);
//   if (!is) {
//     std::cout << "CAN " << CANx << "init failed" << std::endl;
//     return;
//   }
//   std::map<int, int> id_map_angle = compensate_angle.getCompensateAngle();
//   threads.emplace_back(std::thread([=]() {
//     while (thread_state.load()) {
//       TPCANMsg msg;
//       TPCANTimestamp timestamp;
//       TPCANStatus state = CAN_Read(CANx, &msg, &timestamp);
//       if (state != PCAN_ERROR_OK) {
//         // std::cout << "Failed to read CAN message. Error: " << std::hex <<
//         // state << std::endl;
//       } else {
//         hongying_ctrl_msg::msg::MotorFeedback motor;
//         motor.header.frame_id = frame_id;
//         // 解码
//         float p_int = (msg.DATA[1] << 8) | msg.DATA[2];
//         float v_int = (msg.DATA[3] << 4) | (msg.DATA[4] >> 4);
//         float t_int = ((msg.DATA[4] & 0xF) << 8) | msg.DATA[5];
//         float position =
//             uint_to_float(p_int, DM_P_MIN, DM_P_MAX, 16); // (-12.5,12.5)
//         float velocity =
//             uint_to_float(v_int, DM_V_MIN, DM_V_MAX, 12); // (-45.0,45.0)
//         float torque =
//             uint_to_float(t_int, DM_T_MIN, DM_T_MAX, 12); // (-18.0,18.0)
//         motor.speed = velocity;
//         motor.torque = torque;
//         motor.motor_id = (int)((msg.DATA[0]) & 0x0F);
//         // 角度转换 -4PI-4PI 映射到 0-2PI
//         motor.angle = (12.5 - position) -
//                       static_cast<int>((12.5 - position) / (PI * 2)) * PI *
//                       2;
//         // 角度补偿
//         auto is_compensate = id_map_angle.find(motor.motor_id);
//         if (is_compensate != id_map_angle.end()) {
//           motor.angle -= is_compensate->second;
//           if (motor.angle < 0)
//             motor.angle += PI * 2;
//         }
//         std::cout << "ID: " << (int)((msg.DATA[0]) & 0x0F) << std::endl;
//         std::cout << "POS: " << position << std::endl;
//         std::cout << "VEL: " << velocity << std::endl;
//         std::cout << "T: " << torque << std::endl;
//         publisher->publish(motor);
//       }
//     }
//   }));
// }

// void PCAN::addDMMotor(
//     TPCANHandle CANx,
//     rclcpp::Publisher<hongying_ctrl_msg::msg::MotorFeedback>::SharedPtr
//         publisher,
//     std::string frame_id, MotorType motor_type,
//     CompensateAngle compensate_angle) {
//   bool is = initPCAN(CANx, BAUD_1MBPS);
//   if (!is) {
//     std::cout << "CAN " << CANx << "init failed" << std::endl;
//     return;
//   }
//   std::map<int, int> id_map_angle = compensate_angle.getCompensateAngle();
//   rmmotor_rvs.emplace_back([=]() {
//     TPCANMsg msg;
//     TPCANTimestamp timestamp;
//     TPCANStatus state = CAN_Read(CANx, &msg, &timestamp);
//     if (state != PCAN_ERROR_OK) {
//       // std::cout << "Failed to read CAN message. Error: " << std::hex <<
//       state
//       // << std::endl;
//     } else {
//       hongying_ctrl_msg::msg::MotorFeedback motor;
//       motor.header.frame_id = frame_id;
//       // 解码
//       float p_int = (msg.DATA[1] << 8) | msg.DATA[2];
//       float v_int = (msg.DATA[3] << 4) | (msg.DATA[4] >> 4);
//       float t_int = ((msg.DATA[4] & 0xF) << 8) | msg.DATA[5];
//       float position =
//           uint_to_float(p_int, DM_P_MIN, DM_P_MAX, 16); // (-12.5,12.5)
//       float velocity =
//           uint_to_float(v_int, DM_V_MIN, DM_V_MAX, 12); // (-45.0,45.0)
//       float torque =
//           uint_to_float(t_int, DM_T_MIN, DM_T_MAX, 12); // (-18.0,18.0)
//       motor.speed = velocity;
//       motor.torque = torque;
//       motor.motor_id = (int)((msg.DATA[0]) & 0x0F);
//       // 角度转换 -4PI-4PI 映射到 0-2PI
//       motor.angle = (12.5 - position) -
//                     static_cast<int>((12.5 - position) / (PI * 2)) * PI * 2;
//       // 角度补偿
//       auto is_compensate = id_map_angle.find(motor.motor_id);
//       if (is_compensate != id_map_angle.end()) {
//         motor.angle -= is_compensate->second;
//         if (motor.angle < 0)
//           motor.angle += PI * 2;
//       }
//       std::cout << "ID: " << (int)((msg.DATA[0]) & 0x0F) << std::endl;
//       std::cout << "POS: " << position << std::endl;
//       std::cout << "VEL: " << velocity << std::endl;
//       std::cout << "T: " << torque << std::endl;
//       publisher->publish(motor);
//     }
//   });
// }

// void PCAN::addMotor(
//     TPCANHandle CANx,
//     rclcpp::Publisher<hongying_ctrl_msg::msg::MotorFeedback>::SharedPtr
//         publisher,
//     std::string frame_id, MotorType motor_type,
//     CompensateAngle compensate_angle) {
//   bool is = initPCAN(CANx, BAUD_1MBPS);
//   if (!is) {
//     std::cout << "CAN " << CANx << "init failed" << std::endl;
//     return;
//   }
//   std::map<int, int> id_map_angle = compensate_angle.getCompensateAngle();
//   rmmotor_rvs.emplace_back([=]() {
//     TPCANMsg msg;
//     TPCANTimestamp timestamp;
//     TPCANStatus state = CAN_Read(CANx, &msg, &timestamp);
//     if (state != PCAN_ERROR_OK) {
//       // std::cout << "Failed to read CAN message. Error: " << std::hex <<
//       state
//       // << std::endl;
//     } else {
//       // s十六进制打印
//       // std::cout << "Message ID: " << std::hex << msg.ID << std::endl;

//       hongying_ctrl_msg::msg::MotorFeedback motor;
//       motor.header.frame_id = frame_id;
//       motor.angle = (msg.DATA[0] << 8) | msg.DATA[1];
//       motor.speed = (msg.DATA[2] << 8) | msg.DATA[3];
//       motor.torque_current = (msg.DATA[4] << 8) | msg.DATA[5];
//       motor.temperature = msg.DATA[6];

//       // if(motor_type==MERGE)
//       //     std::cout<<"ID:"<<(int)msg.ID-512 << " angle:" << motor.angle <<
//       //     std::endl;
//       // 角度补偿
//       auto is_compensate = id_map_angle.find(msg.ID);
//       if (is_compensate != id_map_angle.end()) {
//         motor.angle -= is_compensate->second;
//         if (motor.angle < 0)
//           motor.angle += 8191;
//         // std::cout<<"补偿"<<static_cast<int>(motor.motor_id)<<"
//         // "<<motor.angle<<std::endl;
//       }

//       switch (motor_type) {
//       case C6X0: {
//         motor.motor_id = (int)msg.ID - 512;
//       } break;
//       case GM6020: {
//         motor.motor_id = (int)msg.ID - 512 - 4;
//       } break;
//       case MERGE: {
//         if ((int)msg.ID != 0) {
//           motor.motor_id = (int)msg.ID - 512;
//         } else {

//           // 解码
//           float p_int = (msg.DATA[1] << 8) | msg.DATA[2];
//           float v_int = (msg.DATA[3] << 4) | (msg.DATA[4] >> 4);
//           float t_int = ((msg.DATA[4] & 0xF) << 8) | msg.DATA[5];
//           float position =
//               uint_to_float(p_int, DM_P_MIN, DM_P_MAX, 16); // (-12.5,12.5)
//           float velocity =
//               uint_to_float(v_int, DM_V_MIN, DM_V_MAX, 12); // (-45.0,45.0)
//           float torque =
//               uint_to_float(t_int, DM_T_MIN, DM_T_MAX, 12); // (-18.0,18.0)
//           motor.speed = velocity;
//           motor.torque = torque;
//           motor.motor_id = (int)((msg.DATA[0]) & 0x0F);
//           // 角度转换 -4PI-4PI 映射到 0-2PI
//           motor.angle = (12.5 - position) -
//                         static_cast<int>((12.5 - position) / (PI * 2)) * PI *
//                         2;
//           // 角度补偿
//           auto is_compensate = id_map_angle.find(motor.motor_id);
//           if (is_compensate != id_map_angle.end()) {
//             motor.angle -= is_compensate->second;
//             if (motor.angle < 0)
//               motor.angle += PI * 2;
//           }
//         }
//       } break;
//       default:
//         break;
//       }
//       publisher->publish(motor);
//     }
//   });
// }

// void PCAN::enableDMotor(TPCANHandle CANx, uint8_t id, bool enable) {
//   TPCANMsg send;
//   send.ID = id; // 达妙
//   send.MSGTYPE = PCAN_MESSAGE_STANDARD;
//   send.LEN = 8;
//   if (enable) {
//     send.DATA[0] = 0xFF;
//     send.DATA[1] = 0xFF;
//     send.DATA[2] = 0xFF;
//     send.DATA[3] = 0xFF;
//     send.DATA[4] = 0xFF;
//     send.DATA[5] = 0xFF;
//     send.DATA[6] = 0xFF;
//     send.DATA[7] = 0xFC;
//   } else {
//     send.DATA[0] = 0xFF;
//     send.DATA[1] = 0xFF;
//     send.DATA[2] = 0xFF;
//     send.DATA[3] = 0xFF;
//     send.DATA[4] = 0xFF;
//     send.DATA[5] = 0xFF;
//     send.DATA[6] = 0xFF;
//     send.DATA[7] = 0xFE;
//   }
//   TPCANStatus status = CAN_Write(PCAN_USBBUS1, &send);
//   if (status != PCAN_ERROR_OK) {
//     std::cout << "Failed to write CAN message. Error: " << std::hex << status
//               << std::endl;
//   } else {
//     // std::cout << "Send Success" << std::endl;
//   }
// }

// std::map<int, int> CompensateAngle::getCompensateAngle() {
//   std::map<int, int> compensate_angle;
//   if (m1 != -1)
//     compensate_angle.insert(std::make_pair(513, m1));
//   if (m2 != -1)
//     compensate_angle.insert(std::make_pair(514, m2));
//   if (m3 != -1)
//     compensate_angle.insert(std::make_pair(515, m3));
//   if (m4 != -1)
//     compensate_angle.insert(std::make_pair(516, m4));
//   if (m5 != -1)
//     compensate_angle.insert(std::make_pair(517, m5));
//   if (m6 != -1)
//     compensate_angle.insert(std::make_pair(518, m6));
//   if (m7 != -1)
//     compensate_angle.insert(std::make_pair(519, m7));
//   if (m8 != -1)
//     compensate_angle.insert(std::make_pair(520, m8));
//   if (m9 != -1)
//     compensate_angle.insert(std::make_pair(521, m9));
//   if (m10 != -1)
//     compensate_angle.insert(std::make_pair(522, m10));
//   if (m11 != -1)
//     compensate_angle.insert(std::make_pair(523, m11));
//   if (m12 != -1)
//     compensate_angle.insert(std::make_pair(524, m12));
//   if (m13 != -1)
//     compensate_angle.insert(std::make_pair(525, m13));
//   return compensate_angle;
// }
