#include "../hpp/ITransport.hpp"

#include <utility>

ITransport::ITransport(std::string id, std::string name)
    : IInventoryItem(std::move(id), std::move(name)) {}