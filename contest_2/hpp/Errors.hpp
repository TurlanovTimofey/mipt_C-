#pragma once

#include <stdexcept>
#include <string>

struct ParkError : std::runtime_error {
  explicit ParkError(const std::string& what) : std::runtime_error(what) {}
};

struct Broken : ParkError {
  explicit Broken(const std::string& what) : ParkError(what) {}
};

struct CommandError : ParkError {
  explicit CommandError(const std::string& what) : ParkError(what) {}
};