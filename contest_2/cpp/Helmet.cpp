#include "../hpp/Helmet.hpp"

#include <utility>

Helmet::Helmet(std::string id, std::string name)
    : IThing(std::move(id), std::move(name)) {}
std::string Helmet::Id() const { return IdReturn(); }
std::string Helmet::Name() const { return NameReturn(); }
std::string Helmet::Describe() const {
  return IdReturn() + " " + NameReturn() + " helmet";
}