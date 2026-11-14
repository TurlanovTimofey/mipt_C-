#include "../hpp/ServiceCenter.hpp"

#include <cctype>

#include "../hpp/Errors.hpp"

void ServiceCenter::IfBroken(const std::string& name) const {
  std::string low_name = name;
  for (char& c : low_name) {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  }
  if (low_name.find("broken") != std::string::npos) {
    throw Broken("inspection rejected: " + name);
  }
}