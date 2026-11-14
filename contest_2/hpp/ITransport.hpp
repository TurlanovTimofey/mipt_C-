#pragma once

#include <string>

#include "../hpp/IInventoryItem.hpp"

class ITransport : public IInventoryItem {
 public:
  ITransport(std::string id, std::string name);
  virtual int Score() const = 0;
};