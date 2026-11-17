#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class FenwickTree {
 public:
  int size;
  std::vector<std::vector<int64_t>> tree;
  explicit FenwickTree(int size)
      : size(size), tree(size + 1, std::vector<int64_t>(size + 1, 0)) {}

  void Add(int x, int y, int64_t delta) {
    for (int i = x; i <= size; i += i & (-i)) {
      for (int j = y; j <= size; j += j & (-j)) {
        tree[i][j] += delta;
      }
    }
  }

  int64_t Prefix(int x, int y) {
    int64_t sum = 0;
    for (int i = x; i > 0; i -= i & (-i)) {
      for (int j = y; j > 0; j -= j & (-j)) {
        sum += tree[i][j];
      }
    }
    return sum;
  }

  int64_t Sum(int x_left, int x_right, int y_down, int y_up) {
    return Prefix(x_right, y_up) - Prefix(x_left - 1, y_up) -
           Prefix(x_right, y_down - 1) + Prefix(x_left - 1, y_down - 1);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int size{};
  int nums{};
  std::cin >> size;
  std::cin >> nums;
  FenwickDoubleTree tree(size);
  for (int i = 0; i < nums; ++i) {
    std::string operation;
    std::cin >> operation;
    if (operation == "ADD") {
      int x{};
      int y{};
      std::cin >> x;
      std::cin >> y;
      tree.Add(x, y, 1);
    } else {
      int x1{};
      int y1{};
      int x2{};
      int y2{};
      std::cin >> x1;
      std::cin >> y1;
      std::cin >> x2;
      std::cin >> y2;
      if (x1 > x2) {
        std::swap(x1, x2);
      }
      if (y1 > y2) {
        std::swap(y1, y2);
      }
      std::cout << tree.Sum(x1, x2, y1, y2) << "\n";
    }
  }
}