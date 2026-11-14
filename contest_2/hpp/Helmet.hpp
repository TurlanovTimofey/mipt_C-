#pragma once

#include <string>

#include "../hpp/IThing.hpp"

class Helmet : public IThing {
 public:
  Helmet(std::string id, std::string name);
  std::string Id() const override;
  std::string Name() const override;
  std::string Describe() const override;
};