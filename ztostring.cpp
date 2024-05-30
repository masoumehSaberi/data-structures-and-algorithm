#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> ZToPrefix(const std::vector<int>& z_functon) {
  std::vector<int> prefix(z_functon.size(), 0);
  for (size_t i = 1; i < z_functon.size(); ++i) {
    prefix[i + z_functon[i] - 1] =
        std::max(prefix[i + z_functon[i] - 1], z_functon[i]);
  }
  for (int i = z_functon.size() - 2; i >= 0; --i) {
    prefix[i] = std::max(prefix[i + 1] - 1, prefix[i]);
  }
  return prefix;
}

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
  std::vector<int> z_function(ParseInput());
  std::vector<int> prefix = ZToPrefix(z_function);
  std::cout << PrefixToString(prefix) << std::endl;
  return 0;
}
