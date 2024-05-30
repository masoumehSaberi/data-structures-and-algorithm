#include <algorithm>
#include <iostream>
#include <vector>

struct Suffix {
  int index;
  int rank[2];
};

int CompairSuffixes(Suffix a, Suffix b) {
  return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0)
                                  : (a.rank[0] < b.rank[0] ? 1 : 0);
}

void AssignIndices(Suffix* suffixes, int n) {
  std::vector<int> next_suffix_index(n);
  for (int k = 4; k < 2 * n; k = k * 2) {
    int rank = 0, prev_rank = suffixes[0].rank[0];
    suffixes[0].rank[0] = rank;
    next_suffix_index[suffixes[0].index] = 0;
    for (int i = 1; i < n; i++) {
      if (suffixes[i].rank[0] == prev_rank &&
          suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
        prev_rank = suffixes[i].rank[0];
        suffixes[i].rank[0] = rank;
      } else {
        prev_rank = suffixes[i].rank[0];
        suffixes[i].rank[0] = ++rank;
      }
      next_suffix_index[suffixes[i].index] = i;
    }
    for (int i = 0; i < n; i++) {
      int next_index = suffixes[i].index + k / 2;
      suffixes[i].rank[1] =
          (next_index < n) ? suffixes[next_suffix_index[next_index]].rank[0]
                           : -1;
    }
    std::sort(suffixes, suffixes + n, CompairSuffixes);
  }
}

std::vector<int> SuffixArray(std::string txt, int n) {
  Suffix* suffixes = new Suffix[n];
  for (int i = 0; i < n; i++) {
    suffixes[i].index = i;
    suffixes[i].rank[0] = txt[i] - 'a';
    suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
  }
  std::sort(suffixes, suffixes + n, CompairSuffixes);
  AssignIndices(suffixes, n);
  std::vector<int> suffix_arr;
  for (int i = 0; i < n; i++) suffix_arr.push_back(suffixes[i].index);
  delete[] suffixes;
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
