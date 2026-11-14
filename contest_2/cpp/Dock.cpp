#include "../hpp/Dock.hpp"

#include <utility>

#include "../hpp/Errors.hpp"

Dock::Dock(std::string id, std::string name, double energy)
    : IThing(std::move(id), std::move(name)), energy_(energy) {
  if (energy < 0.0) {
    throw CommandError("energy must be >= 0, but got " +
                       std::to_string(energy));
  }
}

std::string Dock::Id() const { return IdReturn(); }
std::string Dock::Name() const { return NameReturn(); }

double Dock::EnergyForDay() const { return energy_; }

std::string Dock::Describe() const {
  return IdReturn() + " " + NameReturn() + " dock, " + std::to_string(energy_) +
         " kWh/day";
}
