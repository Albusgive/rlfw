#pragma once
#include "ComCfg.hpp"
#include "tinyxml2.h"
#include <stdexcept>
#include <string>
#include <vector>
using namespace tinyxml2;

class XMLDecoder {
public:
  XMLDecoder() = default;
  XMLDecoder(std::string path);
  ~XMLDecoder();
  bool load(std::string path);

  std::vector<ComCfg> coms;
  bool check();

private:
  XMLDocument doc;
  std::string Attribute2String(const char *name);

  template <typename Enum> Enum string2enum(const std::string &name) {
    auto result = magic_enum::enum_cast<Enum>(name);
    if (result) {
      return *result;
    } else {
      result = magic_enum::enum_cast<Enum>("ERR");
      if (result) {
        return *result;
      } else {
        throw std::invalid_argument("枚举类型未定义 ERR 项且转换失败: " + name);
      }
    }
  }
};
