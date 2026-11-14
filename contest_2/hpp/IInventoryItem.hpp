#pragma once
#include <ostream>
#include <string>

class IInventoryItem {
 public:
  IInventoryItem(std::string id, std::string name);
  virtual ~IInventoryItem();
  virtual std::string Id() const = 0;
  virtual std::string Name() const = 0;
  virtual std::string Describe() const = 0;

 protected:
  const std::string& IdReturn() const noexcept { return id_; }
  const std::string& NameReturn() const noexcept { return name_; }

 private:
  std::string id_;
  std::string name_;
};

bool operator<(const IInventoryItem& first, const IInventoryItem& second);
bool operator==(const IInventoryItem& first, const IInventoryItem& second);
bool operator!=(const IInventoryItem& first, const IInventoryItem& second);
std::ostream& operator<<(std::ostream& os, const IInventoryItem& item);