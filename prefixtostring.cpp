#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::string PrefixToString(const std::vector<int>& prefix) {
  std::string string = "";
  std::vector<char> supporttive_elements(prefix.size(), '\0');
  if (prefix.size() > 0) {
    string += 'a';
    supporttive_elements[0] = 'b';
    for (size_t i = 1; i < prefix.size(); ++i) {
      if (prefix[i] == 0) {
        string += supporttive_elements[i - 1];
      } else {
        string += string[prefix[i] - 1];
      }
      if (prefix[i] - 1 >= 0) {
        supporttive_elements[i] = std::max(supporttive_elements[prefix[i] - 1],
                                           (char)(string[prefix[i]] + 1));
      } else {
        supporttive_elements[i] = 'b';
      }
    }
  }
  return string;
}

std::vector<int> ParseInput() {
  std::string input_string;
  std::getline(std::cin, input_string);
  std::istringstream is(input_string);
  std::vector<int> input((std::istream_iterator<int>(is)),
                         std::istream_iterator<int>());
  return input;
}

int main() {
  std::vector<int> prefix(ParseInput());
  std::cout << PrefixToString(prefix) << std::endl;
  return 0;
}
