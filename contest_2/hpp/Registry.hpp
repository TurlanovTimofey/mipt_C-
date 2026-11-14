#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Errors.hpp"

template <typename T, int Cap>
class Registry {
 private:
  std::vector<T> items_;

 public:
  void Add(const T& item) {
    if (items_.size() >= static_cast<size_t>(Cap)) {
      throw CommandError("Registry capacity exceeded");
    }
    items_.push_back(item);
  }

  size_t Size() const { return items_.size(); }

  const T& operator[](size_t index) const {
    if (index >= items_.size()) {
      throw CommandError("Registry index out of range");
    }
    return items_[index];
  }

  friend std::ostream& operator<<(std::ostream& out, const Registry& registry) {
    for (const auto& item : registry.items_) {
      out << item << ' ';
    }
    return out;
  }
};

template <int Cap>
class Registry<std::string, Cap> {
 private:
  std::vector<std::string> items_;

 public:
  void Add(const std::string& item) {
    if (items_.size() >= static_cast<size_t>(Cap)) {
      throw CommandError("String Registry capacity exceeded");
    }
    items_.push_back(item);
  }

  size_t Size() const { return items_.size(); }

  const std::string& operator[](size_t index) const {
    if (index >= items_.size()) {
      throw CommandError("Registry index out of range");
    }
    return items_[index];
  }

  friend std::ostream& operator<<(std::ostream& out,
                                  const Registry<std::string, Cap>& registry) {
    for (const auto& item : registry.items_) {
      out << item << '\n';
    }
    return out;
  }
};