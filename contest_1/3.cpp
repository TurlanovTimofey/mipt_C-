#include <cstring>
#include <iostream>

struct NameFuncs {
  const char* name;
  void (*func)(char (&board)[5][10]);
};

bool InBoard(int x, int y) { return x >= 0 && x < 10 && y >= 0 && y < 5; }

void Clear(char (&board)[5][10]) {
  for (int y = 0; y < 5; ++y) {
    for (int x = 0; x < 10; ++x) {
      board[y][x] = ' ';
    }
  }
}

void Put(char (&board)[5][10]) {
  int x{};
  int y{};
  char c{};
  std::cin >> x >> y >> c;
  if (!InBoard(x, y)) {
    std::cout << "error\n";
    return;
  }
  board[y][x] = c;
}

void Print(char (&board)[5][10]) {
  for (int y = 0; y < 5; ++y) {
    for (int x = 0; x < 10; ++x) {
      std::cout << board[y][x];
    }
    std::cout << "\n";
  }
}

void Text(char (&board)[5][10]) {
  int x{};
  int y{};
  char word[16];
  std::cin >> x >> y >> word;
  int len = static_cast<int>(std::strlen(word));
  if (!InBoard(x, y) || !InBoard(x + len - 1, y)) {
    std::cout << "error\n";
    return;
  }
  for (int i = 0; i < len; ++i) {
    board[y][x + i] = word[i];
  }
}

int main() {
  NameFuncs arr[] = {
      {"clear", Clear}, {"put", Put}, {"text", Text}, {"print", Print}};
  const int size = sizeof(arr) / sizeof(arr[0]);
  char cmd[20];
  char board[5][10];
  Clear(board);
  while (true) {
    std::cin >> cmd;
    if (std::strcmp(cmd, "quit") == 0) {
      break;
    }
    bool found = false;
    for (int i = 0; i < size; ++i) {
      if (std::strcmp(arr[i].name, cmd) == 0) {
        arr[i].func(board);
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