#pragma once
#include <functional>
#include <string>
#include <vector>
class BaseRemote {
public:
  BaseRemote() {};
  std::string name;
  int channel;
  virtual void bindKeyValue(
      std::function<void(std::vector<std::string> &, std::vector<float> &)>
          key_value) = 0;
  virtual void closeRemote() = 0;
  virtual bool openRemote() = 0;
};