#include "../hpp/Park.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>

#include "../hpp/Errors.hpp"
#include "../hpp/IEnergyConsumer.hpp"
#include "../hpp/ITransport.hpp"

void Park::Add(std::shared_ptr<IInventoryItem> item) {
  if (FindById(item->Id())) {
    throw CommandError("item with id " + item->Id() + " already exists");
  }
  items_.push_back(std::move(item));
  added_id_.Add(items_.back()->Id());
}

void Park::Remove(const std::string& id) {
  for (int i = 0; i < static_cast<int>(items_.size()); ++i) {
    if (items_[i]->Id() == id) {
      items_.erase(items_.begin() + i);
      return;
    }
  }
  throw CommandError("item not found: " + id);
}

void Park::Focus(const std::string& id) {
  auto item = FindById(id);
  if (!item) {
    throw CommandError("item not found: " + id);
  }
  focus_ = item;
}

void Park::ShowFocus() const {
  if (focus_.expired()) {
    std::cout << "removed or expired\n";
  } else {
    auto item = focus_.lock();
    std::cout << *item << '\n';
  }
}

bool CompareItems(const std::shared_ptr<IInventoryItem>& a,
                  const std::shared_ptr<IInventoryItem>& b) {
  return *a < *b;
}

void Park::PrintList() const {
  auto sorted = items_;
  std::sort(sorted.begin(), sorted.end(), CompareItems);
  for (const auto& item : sorted) {
    std::cout << *item << '\n';
  }
}

void Park::PrintEnergy() const {
  double total = 0.0;
  for (const auto& item : items_) {
    if (auto consumer = dynamic_cast<IEnergyConsumer*>(item.get())) {
      total += consumer->EnergyForDay();
    }
  }
  std::cout << std::fixed << std::setprecision(1) << total << '\n';
}

void Park::PrintNovice() const {
  for (const auto& item : items_) {
    if (auto transport = dynamic_cast<ITransport*>(item.get())) {
      if (transport->Score() >= 6) {
        std::cout << *item << '\n';
      }
    }
  }
}

void Park::PrintHistory() const { std::cout << added_id_; }

void Park::MaxEnergy() const {
  std::shared_ptr<IInventoryItem> max_item = nullptr;
  double max_energy = -1.0;
  for (const auto& item : items_) {
    if (auto consumer = dynamic_cast<IEnergyConsumer*>(item.get())) {
      if (consumer->EnergyForDay() > max_energy) {
        max_energy = consumer->EnergyForDay();
        max_item = item;
      }
    }
  }
  if (max_item != nullptr) {
    std::cout << max_item->Name() << " " << max_item->Id() << " (" << std::fixed
              << std::setprecision(1) << max_energy << " kWh/day)\n";
  } else {
    std::cout << "no energy consumers\n";
  }
}

std::shared_ptr<IInventoryItem> Park::FindById(const std::string& id) const {
  for (const auto& item : items_) {
    if (item->Id() == id) {
      return item;
    }
  }
  return nullptr;
}

std::shared_ptr<const ModelSpec> Park::GetCreateSpec(const std::string& name) {
  for (const auto& spec : models_) {
    if (spec->modelName == name) {
      return spec;
    }
  }
  auto spec = std::make_shared<ModelSpec>(ModelSpec{name, "ФизКат", 25});
  models_.push_back(spec);
  return spec;
}