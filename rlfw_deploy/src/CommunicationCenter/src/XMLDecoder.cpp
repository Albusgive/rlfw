#include "XMLDecoder.hpp"
#include "ComCfg.hpp"
#include "magic_enum/magic_enum.hpp"
#include <iostream>

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
          xml_motor.PosKD = motor->FloatAttribute("PosKD", -1.0);
          xml_motor.PosKP = motor->FloatAttribute("PosKP", -1.0);
          xml_motor.VelKI = motor->FloatAttribute("VelKI", -1.0);
          xml_motor.VelKP = motor->FloatAttribute("VelKP", -1.0);
          xml_motor.TorqueKI = motor->FloatAttribute("TorqueKI", -1.0);
          xml_motor.TorqueKP = motor->FloatAttribute("TorqueKP", -1.0);
          xml_motor.SafePos = motor->FloatAttribute("SafePos", -1.0);
          xml_motor.SafeVel = motor->FloatAttribute("SafeVel", -1.0);
          xml_motor.SafeTorque = motor->FloatAttribute("SafeTorque", -1.0);
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
      remotes.push_back(xml_remote);
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
  
  for(auto remote:remotes)
  {
    flag = flag && remote.check();
  }
  return flag;
}

std::string XMLDecoder::Attribute2String(const char *name) {
  if (name == 0) {
    return std::string("");
  }
  return std::string(name);
}