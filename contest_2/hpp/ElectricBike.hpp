#pragma once

#include <memory>
#include <string>

#include "../hpp/IEnergyConsumer.hpp"
#include "../hpp/ITransport.hpp"
#include "../hpp/ModelSpec.hpp"


class ElectricBike : public ITransport, public IEnergyConsumer {
 public:
  ElectricBike(std::string id, std::string name, double energy, int score,
               std::shared_ptr<const ModelSpec> spec);
  std::string Id() const override;
  std::string Name() const override;
  std::string Describe() const override;
  double EnergyForDay() const override;
  int Score() const override;

 private:
  int score_;
  double energy_;
  std::shared_ptr<const ModelSpec> spec_;
};