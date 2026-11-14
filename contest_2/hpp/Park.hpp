#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../hpp/IInventoryItem.hpp"
#include "ModelSpec.hpp"
#include "Registry.hpp"

class Park {
 public:
  Park() = default;
  void Add(std::shared_ptr<IInventoryItem> item);
  void Remove(const std::string& id);
  void PrintList() const;
  void PrintEnergy() const;
  void PrintNovice() const;
  void PrintHistory() const;
  void MaxEnergy() const;
  void Focus(const std::string& id);
  void ShowFocus() const;
  std::shared_ptr<const ModelSpec> GetCreateSpec(const std::string& name);

 private:
  std::shared_ptr<IInventoryItem> FindById(const std::string& id) const;
  std::vector<std::shared_ptr<IInventoryItem>> items_;
  std::weak_ptr<IInventoryItem> focus_;
  std::vector<std::shared_ptr<ModelSpec>> models_;
  Registry<std::string, 100> added_id_;
};
