#include "../hpp/Bike.hpp"

#include <string>
#include <utility>

#include "../hpp/Errors.hpp"

Bike::Bike(std::string id, std::string name, int score)
    : ITransport(std::move(id), std::move(name)), score_(score) {
  if (score < 1 || score > 10) {
    throw CommandError("score must be from 1 to 10, but got " +
                       std::to_string(score));
  }
}
std::string Bike::Id() const { return IdReturn(); }
std::string Bike::Name() const { return NameReturn(); }
int Bike::Score() const { return score_; }
std::string Bike::Describe() const {
  return IdReturn() + " " + NameReturn() + " bike, " + std::to_string(score_) +
         "/10 of easy";
}