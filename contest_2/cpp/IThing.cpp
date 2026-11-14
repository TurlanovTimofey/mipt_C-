#include "../hpp/IThing.hpp"

#include <utility>

IThing::IThing(std::string id, std::string name)
    : IInventoryItem(std::move(id), std::move(name)) {}