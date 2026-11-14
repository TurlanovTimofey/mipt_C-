#pragma once

#include <string>

#include "../hpp/IEnergyConsumer.hpp"
#include "../hpp/IThing.hpp"

class Dock : public IThing, public IEnergyConsumer {
 public:
  Dock(std::string id, std::string name, double energy);
  std::string Id() const override;
  std::string Name() const override;
  std::string Describe() const override;
  double EnergyForDay() const override;

 private:
  double energy_;
};
