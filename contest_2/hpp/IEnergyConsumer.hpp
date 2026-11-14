#pragma once

class IEnergyConsumer {
 public:
  virtual ~IEnergyConsumer() = default;
  virtual double EnergyForDay() const = 0;
};