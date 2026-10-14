#include <cstdint>
#include <cstring>
#include <iostream>

/*Программа хранит квартплату квартир жилого комплекса и может:
-назначать квартплату в определённую квартиру;
-принять оплату определённой квартиры;
-очистить весь дом от оплат;
-показать квартплату определённой квартиры;
-показать суммарную квартплату за здание.
int*** нужен бля удобство обращения к тройной вложенности.
void* нужен, чтобы можно было обращаться к данным без типа,
работать с плоским массивом.
*/

int main() {
  int buildings{};
  int floors{};
  int rooms{};
  std::cin >> buildings >> floors >> rooms;
  if (buildings <= 0 || floors <= 0 || rooms <= 0) {
    std::cout << "error\n";
    return 0;
  }
  const int total = buildings * floors * rooms;
  int* data = new int[total]();
  void* raw = data;
  int*** cube = new int**[buildings];
  for (int b = 0; b < buildings; ++b) {
    cube[b] = new int*[floors];
    for (int f = 0; f < floors; ++f) {
      cube[b][f] = data + b * floors * rooms + f * rooms;
    }
  }
  char cmd[15];
  while (true) {
    std::cin >> cmd;
    if (std::strcmp(cmd, "quit") == 0) {
      break;
    }
    if (std::strcmp(cmd, "set") == 0) {
      int b{};
      int f{};
      int r{};
      int price{};
      std::cin >> b >> f >> r >> price;
      if (b < 0 || b >= buildings || f < 0 || f >= floors || r < 0 ||
          r >= rooms || price < 0) {
        std::cout << "error\n";
        continue;
      }
      cube[b][f][r] += price;
    } else if (std::strcmp(cmd, "pay") == 0) {
      int b{};
      int f{};
      int r{};
      int pay{};
      std::cin >> b >> f >> r >> pay;
      if (b < 0 || b >= buildings || f < 0 || f >= floors || r < 0 ||
          r >= rooms || pay < 0 || pay > cube[b][f][r]) {
        std::cout << "error\n";
        continue;
      }
      cube[b][f][r] -= pay;
    } else if (std::strcmp(cmd, "clear") == 0) {
      std::memset(raw, 0, total * sizeof(int));
    } else if (std::strcmp(cmd, "get") == 0) {
      int b{};
      int f{};
      int r{};
      std::cin >> b >> f >> r;
      if (b < 0 || b >= buildings || f < 0 || f >= floors || r < 0 ||
          r >= rooms) {
        std::cout << "error\n";
        continue;
      }
      std::cout << cube[b][f][r] << "\n";
    } else if (std::strcmp(cmd, "building") == 0) {
      int b{};
      std::cin >> b;
      if (b < 0 || b >= buildings) {
        std::cout << "error\n";
        continue;
      }
      int64_t sum = 0;
      for (int f = 0; f < floors; ++f) {
        for (int r = 0; r < rooms; ++r) {
          sum += cube[b][f][r];
        }
      }
      std::cout << sum << "\n";
    } else {
      std::cout << "error\n";
    }
  }
  for (int b = 0; b < buildings; ++b) {
    delete[] cube[b];
  }
  delete[] cube;
  delete[] data;
  return 0;
}