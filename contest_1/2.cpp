#include <cstring>
#include <iostream>

struct NameFuncs {
  const char* name;
  void (*func)(int&);
};

void Deposit(int& sum) {
  int k{};
  std::cin >> k;
  if (k <= 0) {
    std::cout << "error\n";
    return;
  }
  sum += k;
}

void Withdraw(int& sum) {
  int k{};
  std::cin >> k;
  if (k <= 0 || sum < k) {
    std::cout << "error\n";
    return;
  }
  sum -= k;
}

void Balance(int& sum) { std::cout << sum << "\n"; }

void Reset(int& sum) { sum = 0; }

void Double(int& sum) { sum *= 2; }

int main() {
  NameFuncs arr[] = {{"deposit", Deposit},
                     {"withdraw", Withdraw},
                     {"balance", Balance},
                     {"reset", Reset},
                     {"double", Double}};
  const int size = sizeof(arr) / sizeof(arr[0]);
  char cmd[20];
  int sum{};
  while (true) {
    std::cin >> cmd;
    if (std::strcmp(cmd, "stop") == 0) {
      break;
    }
    bool found = false;
    for (int i = 0; i < size; ++i) {
      if (std::strcmp(arr[i].name, cmd) == 0) {
        arr[i].func(sum);
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "error\n";
    }
  }
  return 0;
}