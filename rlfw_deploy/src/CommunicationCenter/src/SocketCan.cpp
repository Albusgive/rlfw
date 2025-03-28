#include "SocketCan.h"
#include <utility>
SocketCan::SocketCan() {}
SocketCan::~SocketCan() {}
bool SocketCan::connect() {
  if ((sock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
    std::cout << "can't creat can socket" << std::endl;
    return false;
  }
  struct ifreq ifr;
  std::string port = "can" + std::to_string(channel);
  strcpy(ifr.ifr_name, port.c_str());
  ioctl(sock, SIOCGIFINDEX, &ifr);
  std::cout << "Connecting to " << ifr.ifr_name << std::endl;
  struct sockaddr_can addr;
  memset(&addr, 0, sizeof(addr));
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    std::cout << "can't bind socket" << std::endl;
    return false;
  }
  return true;
}

bool SocketCan::send(uint16_t /*CANx*/, CANMSG *msg) {
  struct can_frame frame;
  switch (msg->MSGTYPE) {
  case CAN_STANDARD: {
    frame.can_id = msg->ID;
    break;
  }
  case CAN_EXTENDED: {
    frame.can_id = CAN_EFF_FLAG | msg->ID;
    break;
  }
  default: {
    frame.can_id = msg->ID;
  }
  }
  frame.can_dlc = msg->LEN;
  memcpy(frame.data, msg->DATA, 8);
  ssize_t bytes_sent = write(sock, &frame, sizeof(frame));
  if (bytes_sent != sizeof(frame)) {
    std::cout << "socketcan: " << channel << " send err" << std::endl;
    return false;
  }
  return true;
}

std::pair<bool, CANMSG> SocketCan::receive(uint16_t /*CANx*/) {
  struct can_frame frame;
  ssize_t nbytes = read(sock, &frame, sizeof(frame));
  if (nbytes < 0) {
    std::cout << "SocketCan: " << channel << " Read error" << std::endl;
    return {false, CANMSG()};
  } else if (nbytes < static_cast<ssize_t>(sizeof(frame))) {
    return {false, CANMSG()};
    std::cout << "SocketCan: " << channel << " Incomplete frame" << std::endl;
  } else {
    CANMSG msg;
    msg.ID = frame.can_id;
    msg.LEN = frame.can_dlc;
    memcpy(msg.DATA, frame.data, frame.can_dlc);
    return {true, msg};
  }
}

void SocketCan::connectDecode(
    std::function<void(CANMSG &, std::vector<int> &motor_ids,
                       std::string &name,int decoder_idx)>
        lambda) {
  decode_lambda = lambda;
}

void SocketCan::RunRecv() {
  is_only_thread.store(true);
  std::thread ThRecv = std::thread{[this]() {
    while (is_only_thread.load()) {
      auto [is, msg] = receive(channel);
      if (is) {
        decode_lambda(msg, devive_ids, this->name,decoder_idx);
      }
      // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }};
  ThRecv.detach();
}

void SocketCan::closeRecv() { is_only_thread.store(false); }