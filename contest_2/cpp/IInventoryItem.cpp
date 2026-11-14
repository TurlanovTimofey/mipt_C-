#include "../hpp/IInventoryItem.hpp"

#include <utility>

IInventoryItem::IInventoryItem(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name)) {}

IInventoryItem::~IInventoryItem() = default;
bool operator<(const IInventoryItem& first, const IInventoryItem& second) {
  return first.Id() < second.Id();
}
bool operator==(const IInventoryItem& first, const IInventoryItem& second) {
  return first.Id() == second.Id();
}
bool operator!=(const IInventoryItem& first, const IInventoryItem& second) {
  return !(first == second);
}
std::ostream& operator<<(std::ostream& os, const IInventoryItem& item) {
  return os << item.Id() << ' ' << item.Name();
}