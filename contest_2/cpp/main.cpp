#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "../hpp/Bike.hpp"
#include "../hpp/Dock.hpp"
#include "../hpp/ElectricBike.hpp"
#include "../hpp/Errors.hpp"
#include "../hpp/Helmet.hpp"
#include "../hpp/Park.hpp"
#include "../hpp/Scooter.hpp"
#include "../hpp/ServiceCenter.hpp"

int main() {
  Park park;
  ServiceCenter service;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream input(line);
    std::string cmd;
    input >> cmd;
    try {
      if (cmd == "quit") {
        break;
      }
      if (cmd == "add") {
        std::string type;
        input >> type;
        std::string id;
        std::string name;
        double energy{};
        int score{};
        std::unique_ptr<IInventoryItem> temp_item;
        if (type == "scooter") {
          input >> id >> name >> energy >> score;
          if (!input) {
            throw CommandError("invalid arguments for scooter");
          }
          service.IfBroken(name);
          auto spec = park.GetCreateSpec(name);
          temp_item = std::make_unique<Scooter>(id, name, energy, score, spec);
        } else if (type == "ebike") {
          input >> id >> name >> energy >> score;
          if (!input) {
            throw CommandError("invalid arguments for ebike");
          }
          service.IfBroken(name);
          auto spec = park.GetCreateSpec(name);
          temp_item =
              std::make_unique<ElectricBike>(id, name, energy, score, spec);
        } else if (type == "bike") {
          input >> id >> name >> score;
          if (!input) {
            throw CommandError("invalid arguments for bike");
          }
          service.IfBroken(name);
          temp_item = std::make_unique<Bike>(id, name, score);
        } else if (type == "helmet") {
          input >> id >> name;
          if (!input) {
            throw CommandError("invalid arguments for helmet");
          }
          service.IfBroken(name);
          temp_item = std::make_unique<Helmet>(id, name);
        } else if (type == "dock") {
          input >> id >> name >> energy;
          if (!input) {
            throw CommandError("invalid arguments for dock");
          }
          service.IfBroken(name);
          temp_item = std::make_unique<Dock>(id, name, energy);
        } else {
          throw CommandError("unknown vehicle type: " + type);
        }
        park.Add(std::shared_ptr<IInventoryItem>(std::move(temp_item)));
      } else if (cmd == "list") {
        park.PrintList();
      } else if (cmd == "energy") {
        park.PrintEnergy();
      } else if (cmd == "novice") {
        park.PrintNovice();
      } else if (cmd == "focus") {
        std::string id;
        input >> id;
        park.Focus(id);
      } else if (cmd == "show_focus") {
        park.ShowFocus();
      } else if (cmd == "remove") {
        std::string id;
        input >> id;
        park.Remove(id);
      } else if (cmd == "history") {
        park.PrintHistory();
      } else if (cmd == "max_energy") {
        park.MaxEnergy();
      } else {
        throw CommandError("unknown command: " + cmd);
      }
    } catch (const ParkError& e) {
      std::cout << "error: " << e.what() << '\n';
    }
  }
  return 0;
}