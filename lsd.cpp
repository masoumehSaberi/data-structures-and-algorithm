#include <iostream>

unsigned long long int Max(unsigned long long int const arr[], int size) {
  unsigned long long int max = arr[0];
  for (int i = 1; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

void CSort(unsigned long long int arr[], int size,
           unsigned long long int divisor) {
  unsigned long long int* sorted_arr = new unsigned long long int[size];
  unsigned long long int count[256] = {0};
  for (int i = 0; i < size; i++) {
    count[(arr[i] / divisor) % 256]++;
  }
  for (int i = 1; i < 256; i++) {
    count[i] += count[i - 1];
  }
  for (int i = size - 1; i >= 0; i--) {
    sorted_arr[count[(arr[i] / divisor) % 256] - 1] = arr[i];
    count[(arr[i] / divisor) % 256]--;
  }
  for (int i = 0; i < size; i++) {
    arr[i] = sorted_arr[i];
  }
  delete[] sorted_arr;
}

void RedixSort(unsigned long long int arr[], int size) {
  unsigned long long int max = Max(std::move(arr), std::move(size));
  for (unsigned long long int divisor = 1; max / divisor > 0; divisor *= 256) {
    CSort(std::move(arr), std::move(size), std::move(divisor));
  }
}

int main() {
  int size;
  std::cin >> size;
  unsigned long long int* arr = new unsigned long long int[size];
  for (int i = 0; i < size; i++) {
    std::cin >> arr[i];
  }
  RedixSort(std::move(arr), std::move(size));
  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << std::endl;
  }
  delete[] arr;
  return 0;
}
