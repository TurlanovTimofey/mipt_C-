#include <climits>
#include <iomanip>
#include <iostream>


struct Extremum {
  int min;
  int max;
};

double Getaverage(const int* arr, int size) {
  int sum{};
  for (int i = 0; i < size; ++i) {
    sum += arr[i];
  }
  return sum * 1.0 / size;
}

int CountNegative(const int* arr, int size) {
  int count{};
  for (int i = 0; i < size; ++i) {
    if (arr[i] < 0) {
      ++count;
    }
  }
  return count;
}

Extremum GetExtremums(const int* arr, int size) {
  Extremum result;
  result.min = INT_MAX;
  result.max = INT_MIN;
  for (int i = 0; i < size; ++i) {
    if (result.min > arr[i]) {
      result.min = arr[i];
    }
    if (result.max < arr[i]) {
      result.max = arr[i];
    }
  }
  return result;
}

int main() {
  int num{};
  std::cin >> num;
  int* arr = new int[num];
  for (int i = 0; i < num; ++i) {
    std::cin >> arr[i];
  }
  double average = Getaverage(arr, num);
  int count_negative = CountNegative(arr, num);
  Extremum result = GetExtremums(arr, num);
  std::cout << std::fixed << std::setprecision(1) << average << "\n";
  std::cout << result.min << " " << result.max << "\n";
  std::cout << count_negative << "\n";
  delete[] arr;
  return 0;
}