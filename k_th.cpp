#include <iostream>

void swap(int arr[], int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

int kth(int arr[], int left, int right, int k) {
  if (k > 0 && k <= right - left + 1) {
    int index;
    int pivot = arr[right];
    int i = left;
    for (int j = left; j <= right - 1; j++) {
      if (arr[j] <= pivot) {
        std::swap(arr[i], arr[j]);
        i++;
      }
    }
    std::swap(arr[i], arr[right]);
    index = i;
    if (index - left == k - 1) {
      return arr[index];
    }
    if (index - left > k - 1) {
      return kth(arr, left, index - 1, k);
    }
    return kth(arr, index + 1, right, k - index + left - 1);
  }
  throw "error";
}

int main() {
  int n = 2;
  std::cin >> n;
  int* arr = new int[n];
  int k;
  std::cin >> k;
  if (n >= 2) {
    std::cin >> arr[0];
    std::cin >> arr[1];
  }
  for (int i = 2; i < n; i++) {
    arr[i] = (arr[i - 1] * 123 + arr[i - 2] * 45) % (10004321);
  }
  try {
    std::cout << kth(arr, 0, n - 1, k);
  } catch (...) {
    std::cout << "error" << std::endl;
  }
  delete[] arr;
  return 0;
}
