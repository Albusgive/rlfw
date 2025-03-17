#include "XMLDecoder.hpp"
#include "ComCfg.hpp"
#include <iostream>
#include <sstream>

XMLDecoder::XMLDecoder(std::string path) { load(path); }
XMLDecoder::~XMLDecoder() {}
bool XMLDecoder::load(std::string path) {
  tinyxml2::XMLError error = doc.LoadFile(path.c_str());
  if (error != tinyxml2::XML_SUCCESS) {
    std::cerr << "加载失败: " << doc.ErrorStr() << std::endl;
    return false;
  }
  tinyxml2::XMLElement *root = doc.RootElement();
  if (!root || strcmp(root->Name(), "rlfw") != 0) {
    std::cerr << "无效的根节点" << std::endl;
    return false;
  }

  XMLElement *com = root->FirstChildElement("com");
  if (com) {
    for (; com; com = com->NextSiblingElement("com")) {
      ComCfg ComCfg;
      // 解析 com 节点属性
      ComCfg.type =
          string2enum<ComType>(Attribute2String(com->Attribute("type")));
      // std::cout << "com type:" << magic_enum::enum_name(ComCfg.type) <<
      // std::endl;
      ComCfg.attrs = Attribute2String(com->Attribute("attrs"));
      ComCfg.channel = com->IntAttribute("channel", 1);
      ComCfg.name = Attribute2String(com->Attribute("name"));
      ComCfg.port = Attribute2String(com->Attribute("port"));
      // std::cout<<"com port:"<<ComCfg.port<<std::endl;
      ComCfg.only_thred = com->BoolAttribute("thread", false);
      ComCfg.bps = com->IntAttribute("bps", 115200);
      ComCfg.datasize = com->IntAttribute("datasize", 8);
      ComCfg.parity = com->IntAttribute("parity", 0);
      ComCfg.stopbit = com->IntAttribute("stopbit", 1);

      // 解析子 motor 节点
      XMLElement *motor = com->FirstChildElement("motor");
      if (!motor) {
        //   std::cout << "  (无 motor 子节点)" << std::endl;
      } else {
        for (; motor; motor = motor->NextSiblingElement("motor")) {
          XMLMotor xml_motor;
          xml_motor.type = string2enum<Motortype>(
              Attribute2String(motor->Attribute("type")));
          xml_motor.joint_name =
              Attribute2String(motor->Attribute("jointname"));
          xml_motor.id = motor->IntAttribute("id", -1);
          xml_motor.ctrl_type = string2enum<MotorCtrlType>(
              Attribute2String(motor->Attribute("ctrltype")));
          xml_motor.invert = motor->BoolAttribute("invert", false);
          xml_motor.PosKD = motor->FloatAttribute("poskd", -1.0);
          xml_motor.PosKP = motor->FloatAttribute("poskp", -1.0);
          xml_motor.VelKI = motor->FloatAttribute("velki", -1.0);
          xml_motor.VelKP = motor->FloatAttribute("velkp", -1.0);
          xml_motor.TorqueKI = motor->FloatAttribute("torqueki", -1.0);
          xml_motor.TorqueKP = motor->FloatAttribute("torquekp", -1.0);
          xml_motor.SafePos = motor->FloatAttribute("safepos", -1.0);
          xml_motor.SafeVel = motor->FloatAttribute("safevel", -1.0);
          xml_motor.SafeTorque = motor->FloatAttribute("safetorque", -1.0);
          xml_motor.default_ = motor->FloatAttribute("default", 0.0);
          auto torque_range = splitFromString(
              Attribute2String(motor->Attribute("torquerange")));
          if (torque_range.size() == 2) {
            xml_motor.torque_range[0] = torque_range[0];
            xml_motor.torque_range[1] = torque_range[1];
          }
          auto pos_range =
              splitFromString(Attribute2String(motor->Attribute("posrange")));
          if (pos_range.size() == 2) {
            xml_motor.pos_range[0] = pos_range[0];
            xml_motor.pos_range[1] = pos_range[1];
          }
          auto vel_range =
              splitFromString(Attribute2String(motor->Attribute("velrange")));
          if (vel_range.size() == 2) {
            xml_motor.vel_range[0] = vel_range[0];
            xml_motor.vel_range[1] = vel_range[1];
          }
          ComCfg.xml_motors.push_back(xml_motor);
        }
      }
      coms.push_back(ComCfg);
    }
  }
  XMLElement *remote = root->FirstChildElement("remote");
  if (remote) {
    for (; remote; remote = remote->NextSiblingElement("remote")) {
      XMLRemote xml_remote;
      xml_remote.name = Attribute2String(remote->Attribute("name"));
      xml_remote.type =
          string2enum<RemoteType>(Attribute2String(remote->Attribute("type")));
      xml_remote.channel = remote->IntAttribute("channel", 0);
      std::string key_ = Attribute2String(remote->Attribute("key"));
      xml_remote.key = splitByStream(key_);
      remotes.push_back(xml_remote);
    }
  }
  XMLElement *virtualmotor = root->FirstChildElement("virtualmotor");
  if (virtualmotor) {
    for (; virtualmotor;
         virtualmotor = virtualmotor->NextSiblingElement("virtualmotor")) {
      XMLVirtualMotor xml_virtualmotor;
      xml_virtualmotor.joint_name =
          Attribute2String(virtualmotor->Attribute("jointname"));
      xml_virtualmotor.type = string2enum<VirtualMotortype>(
          Attribute2String(virtualmotor->Attribute("type")));
      xml_virtualmotor.motor1 =
          Attribute2String(virtualmotor->Attribute("motor1"));
      xml_virtualmotor.motor2 =
          Attribute2String(virtualmotor->Attribute("motor2"));
      xml_virtualmotor.terminal =
          virtualmotor->BoolAttribute("terminal", false);
      xml_virtualmotor.default_theta =
          virtualmotor->FloatAttribute("default_theta", 1.57);
      xml_virtualmotor.default_ = virtualmotor->FloatAttribute("default", 0.0);
      auto torque_range = splitFromString(
          Attribute2String(virtualmotor->Attribute("torquerange")));
      if (torque_range.size() == 2) {
        xml_virtualmotor.torque_range[0] = torque_range[0];
        xml_virtualmotor.torque_range[1] = torque_range[1];
      }
      auto pos_range = splitFromString(
          Attribute2String(virtualmotor->Attribute("posrange")));
      if (pos_range.size() == 2) {
        xml_virtualmotor.pos_range[0] = pos_range[0];
        xml_virtualmotor.pos_range[1] = pos_range[1];
      }
      auto vel_range = splitFromString(
          Attribute2String(virtualmotor->Attribute("velrange")));
      if (vel_range.size() == 2) {
        xml_virtualmotor.vel_range[0] = vel_range[0];
        xml_virtualmotor.vel_range[1] = vel_range[1];
      }
      std::string str = Attribute2String(virtualmotor->Attribute("ln"));
      std::stringstream ss(str); // 使用字符串流解析
      float value;
      while (ss >> value) {
        xml_virtualmotor.ln.push_back(value);
      }
      virtualmotors.push_back(xml_virtualmotor);
    }
  }
  return true;
}

bool XMLDecoder::check() {
  bool flag = true;
  for (auto com : coms) {
    flag = flag && com.check();
    for (auto motor : com.xml_motors) {
      flag = flag && motor.check();
    }
  }
  for (auto remote : remotes) {
    flag = flag && remote.check();
  }
  for (auto virtualmotor : virtualmotors) {
    flag = flag && virtualmotor.check();
  }
  return flag;
}

std::string XMLDecoder::Attribute2String(const char *name) {
  if (name == 0) {
    return std::string("");
  }
  return std::string(name);
}

std::vector<std::string> XMLDecoder::splitByStream(const std::string &s) {
  std::istringstream iss(s);
  std::vector<std::string> tokens;
  std::string token;
  while (iss >> token) { // 自动跳过连续空格
    tokens.push_back(token);
  }
  return tokens;
}

std::vector<float> XMLDecoder::splitFromString(const std::string &s) {
  // std::cout<<"range string:"<<s<<std::endl;
  std::istringstream iss(s);
  iss.imbue(std::locale::classic());
  std::vector<float> tokens;
  float token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  if (!iss.eof()) {
    throw std::invalid_argument("Invalid floating point value in: " + s);
  }
  return tokens;
}