#include <iostream>

using std::cin;

bool BinarySearch(const int* begin, const int* end, int target) {
  if (end > begin) {
    int mid;
    mid = *(begin + (end - begin) / 2);

    if (mid == target) {
      return true;
    }
    if (mid > target) {
      return BinarySearch(begin, (begin + (end - begin) / 2), target);
    }
    return BinarySearch((begin + (end - begin) / 2) + 1, end, target);
  }

  return false;
}

int main() {
  int n = 0, q, t, i, j;
  int *begin, *end;
  cin >> n;
  int* arr = new int[n];
  for (int k = 0; k < n; k++) {
    cin >> arr[k];
  }
  cin >> q;
  bool result = false;
  for (int k = 0; k < q; k++) {
    cin >> i;
    begin = &arr[i];
    cin >> j;
    end = &arr[j];
    cin >> t;
    result = BinarySearch(begin, end, t);
    if (result) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
  delete[] arr;
  return 0;
}
