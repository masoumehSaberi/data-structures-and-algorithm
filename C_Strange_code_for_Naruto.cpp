#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Vertex {
  Vertex *parent = nullptr, *suffix = nullptr, *next_suffix = nullptr;
  std::unordered_map<char, Vertex*> child;
  char chr{};
  std::vector<size_t> go_to;
};

class Trie {
 public:
  Trie(std::vector<std::pair<std::string, size_t>>& pattern);
  ~Trie() { Clear(root_); }
  std::vector<size_t> Search(std::string& str);
  void Insert(std::string& str, size_t pattern_index);

 private:
  Vertex* root_;
  Vertex* GoTo(Vertex* vertex, char ch);
  void Clear(Vertex* vertex);
  Vertex* Suffix(Vertex* vertex);
  Vertex* NextSuffix(Vertex* vertex);
};

std::vector<int> FindPattern(std::string& text, std::string& pattern) {
  size_t pattern_index = 0;
  std::vector<std::pair<std::string, size_t>> subpattern;
  for (size_t i = 0; i < pattern.size(); ++i) {
    if (pattern[i] == '?') {
      if (pattern_index != i) {
        subpattern.emplace_back(
            pattern.substr(pattern_index, i - pattern_index), i - 1);
      }
      pattern_index = i + 1;
    }
  }
  if (pattern.size() != pattern_index) {
    subpattern.emplace_back(
        pattern.substr(pattern_index, pattern.size() - pattern_index),
        pattern.size() - 1);
  }
  Trie trie = subpattern;
  std::vector<size_t> subpattern_counter = trie.Search(text);
  std::vector<int> pattern_occurences;
  for (size_t i = 0; i < subpattern_counter.size(); i++) {
    if (i + pattern.size() <= text.size() &&
        subpattern_counter[i] == subpattern.size()) {
      pattern_occurences.push_back(i);
    }
  }
  return pattern_occurences;
}

int main() {
  std::string pattern;
  std::string text;
  std::cin >> pattern >> text;
  for (auto position : FindPattern(text, pattern)) {
    std::cout << position << ' ';
  }
  return 0;
}

Trie::Trie(std::vector<std::pair<std::string, size_t>>& pattern) {
  root_ = new Vertex;
  for (auto part : pattern) {
    Insert(part.first, part.second);
  }
}

std::vector<size_t> Trie::Search(std::string& str) {
  Vertex* current_vertex = root_;
  std::vector<size_t> subpattern_counter(str.size(), 0);
  for (size_t i = 0; i < str.size(); ++i) {
    current_vertex = GoTo(current_vertex, str[i]);
    Vertex* temp_vertex = current_vertex;
    while (temp_vertex != root_) {
      for (size_t shift : temp_vertex->go_to) {
        if (shift <= i) {
          subpattern_counter[i - shift]++;
        }
      }
      temp_vertex = NextSuffix(temp_vertex);
    }
  }
  return subpattern_counter;
}

void Trie::Insert(std::string& str, size_t pattern_index) {
  Vertex* current_vertex = root_;
  for (char index : str) {
    if (current_vertex->child.end() == current_vertex->child.find(index)) {
      current_vertex->child[index] = new Vertex;
      current_vertex->child.at(index)->parent = current_vertex;
      current_vertex->child.at(index)->chr = index;
    }
    current_vertex = current_vertex->child.at(index);
  }
  current_vertex->go_to.push_back(pattern_index);
}

Vertex* Trie::GoTo(Vertex* vertex, char ch) {
  while (vertex != root_ && vertex->child.find(ch) == vertex->child.end()) {
    vertex = Suffix(vertex);
  }
  if (vertex->child.find(ch) == vertex->child.end() && vertex == root_) {
    return root_;
  }
  return vertex->child.at(ch);
}

void Trie::Clear(Vertex* vertex) {
  if (vertex != nullptr) {
    for (auto child : vertex->child) {
      Clear(child.second);
    }
    delete vertex;
  }
}

Vertex* Trie::Suffix(Vertex* vertex) {
  if (vertex->suffix == nullptr) {
    if (vertex->parent == root_ || vertex == root_) {
      vertex->suffix = root_;
    } else {
      vertex->suffix = GoTo(Suffix(vertex->parent), vertex->chr);
    }
  }
  return vertex->suffix;
}

Vertex* Trie::NextSuffix(Vertex* vertex) {
  if (vertex->next_suffix == nullptr) {
    auto next_vertex = Suffix(vertex);
    if (next_vertex != root_) {
      vertex->next_suffix =
          next_vertex->go_to.empty() ? NextSuffix(next_vertex) : next_vertex;
    } else {
      vertex->next_suffix = root_;
    }
  }
  return vertex->next_suffix;
}
