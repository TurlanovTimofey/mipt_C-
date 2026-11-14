#pragma once

#include <string>

class ServiceCenter {
 public:
  void IfBroken(const std::string& name) const;
};