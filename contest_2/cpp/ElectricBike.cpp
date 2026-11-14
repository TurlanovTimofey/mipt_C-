#include "../hpp/ElectricBike.hpp"

#include <string>
#include <utility>

#include "../hpp/Errors.hpp"

ElectricBike::ElectricBike(std::string id, std::string name, double energy,
                           int score, std::shared_ptr<const ModelSpec> spec)
    : ITransport(std::move(id), std::move(name)),
      IEnergyConsumer(),
      energy_(energy),
      score_(score),
      spec_(std::move(spec)) {
  if (score < 1 || score > 10) {
    throw CommandError("score must be from 1 to 10, but got " +
                       std::to_string(score));
  }
  if (energy < 0.0) {
    throw CommandError("energy must be >= 0, but got " +
                       std::to_string(energy));
  }
}

std::string ElectricBike::Id() const { return IdReturn(); }
std::string ElectricBike::Name() const { return NameReturn(); }
double ElectricBike::EnergyForDay() const { return energy_; }
int ElectricBike::Score() const { return score_; }
std::string ElectricBike::Describe() const {
  return IdReturn() + " " + NameReturn() + " electricbike, " +
         std::to_string(score_) + "/10 of easy, " + std::to_string(energy_) +
         " kWh/day, model: " + spec_->modelName;
}
