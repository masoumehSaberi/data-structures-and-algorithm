#include <iostream>

void Swap(int arr[], int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

int Part(int arr[], int left, int right, int pivot) {
  while (left <= right) {
    while (arr[left] < pivot) {
      left++;
    }
    while (arr[right] > pivot) {
      right--;
    }
    if (left <= right) {
      Swap(arr, left, right);
      left++;
      right--;
    }
  }
  return left;
}

void QuickSort(int arr[], int low, int high) {
  int partition_index;
  if (low < high) {
    int mid = (low + high) / 2;
    int pivot = arr[mid];
    partition_index = Part(arr, low, high, pivot);
    QuickSort(arr, low, partition_index - 1);
    QuickSort(arr, partition_index, high);
  }
}

int main() {
  int n;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; i++) std::cin >> arr[i];
  QuickSort(arr, 0, n - 1);
  for (int i = 0; i < n; i++) std::cout << arr[i] << ' ';
  delete[] arr;
  return 0;
}
