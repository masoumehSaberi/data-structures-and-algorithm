#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, int> hash;
  int n;
  int i;
  std::string input;
  std::cin >> n;
  for (int j = 0; j < n; j++) {
    std::cin >> input;
    if (input == "+") {
      std::cin >> i;
      hash.insert(std::pair<int, int>(i, i));
    } else if (input == "-") {
      std::cin >> i;
      try {
        hash.erase(i);
      } catch (...) {
        continue;
      }
    } else if (input == "?") {
      std::cin >> i;
      try {
        hash.at(i);
        std::cout << "YES" << std::endl;
      } catch (...) {
        std::cout << "NO" << std::endl;
      }
    }
  }
}
