#pragma once

#include <string>

#include "../hpp/IInventoryItem.hpp"

class IThing : public IInventoryItem {
 public:
  IThing(std::string id, std::string name);
};