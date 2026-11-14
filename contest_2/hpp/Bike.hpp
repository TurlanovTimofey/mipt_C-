#pragma once

#include <string>

#include "../hpp/ITransport.hpp"

class Bike : public ITransport {
 public:
  Bike(std::string id, std::string name, int score);
  std::string Id() const override;
  std::string Name() const override;
  std::string Describe() const override;
  int Score() const override;

 private:
  int score_;
};