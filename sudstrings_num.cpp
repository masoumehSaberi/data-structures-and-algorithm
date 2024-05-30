#include <algorithm>
#include <iostream>
#include <vector>

constexpr int maximum = std::numeric_limits<int>::max();

struct Suffix {
  int index;
  std::pair<int, int> order = {maximum, maximum};
};

int CompairSuffixes(Suffix a, Suffix b) {
  return (a.order.first == b.order.first)
             ? (a.order.second < b.order.second ? 1 : 0)
             : (a.order.first < b.order.first ? 1 : 0);
}

void AssignIndices(std::vector<Suffix> suffixes, int n) {
  std::vector<int> next_suffix_index(n);
  for (int k = 4; k < 2 * n; k = k * 2) {
    int order = 0, previous_order = suffixes[0].order.first;
    suffixes[0].order.first = order;
    next_suffix_index[suffixes[0].index] = 0;
    for (int i = 1; i < n; i++) {
      if (suffixes[i].order.first == previous_order &&
          suffixes[i].order.second == suffixes[i - 1].order.second) {
        previous_order = suffixes[i].order.first;
        suffixes[i].order.first = order;
      } else {
        previous_order = suffixes[i].order.first;
        suffixes[i].order.first = ++order;
      }
      next_suffix_index[suffixes[i].index] = i;
    }
    for (int i = 0; i < n; i++) {
      int next_index = suffixes[i].index + k / 2;
      suffixes[i].order.second =
          (next_index < n) ? suffixes[next_suffix_index[next_index]].order.first
                           : -1;
    }
  }
}

std::vector<int> SuffixArray(std::string txt, int n) {
  std::vector<Suffix> suffixes(2 * n);
  for (int i = 0; i < n; i++) {
    suffixes[i].index = i;
    suffixes[i].order.first = txt[i] - 'a';
    suffixes[i].order.second = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
  }
  std::sort(suffixes.begin(), suffixes.end(), CompairSuffixes);
  AssignIndices(suffixes, n);
  std::sort(suffixes.begin(), suffixes.end(), CompairSuffixes);
  std::vector<int> suffix_arr(n);
  for (int i = 0; i < n; i++) {
    suffix_arr[i] = suffixes[i].index;
  }
  return suffix_arr;
}

std::vector<int> LCP(std::string txt, std::vector<int> suffix_arr) {
  int n = suffix_arr.size();
  std::vector<int> lcp(n, 0);
  std::vector<int> inverse_suffix(n, 0);
  for (int i = 0; i < n; i++) {
    inverse_suffix[suffix_arr[i]] = i;
  }
  int k = 0;
  for (int i = 0; i < n; i++) {
    if (inverse_suffix[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = suffix_arr[inverse_suffix[i] + 1];
    while (i + k < n && j + k < n && txt[i + k] == txt[j + k]) k++;

    lcp[inverse_suffix[i]] = k;
    if (k > 0) {
      k--;
    }
  }
  return lcp;
}

int CountDistinctSubstring(std::string txt) {
  int n = txt.length();
  std::vector<int> suffix_arr = SuffixArray(txt, n);
  std::vector<int> lcp = LCP(txt, suffix_arr);
  int result = n - suffix_arr[0];
  for (size_t i = 1; i < lcp.size(); i++) {
    result += (n - suffix_arr[i]) - lcp[i - 1];
  }
  return result;
}

int main() {
  std::string txt;
  std::cin >> txt;
  std::cout << CountDistinctSubstring(txt) << std::endl;
  return 0;
}
