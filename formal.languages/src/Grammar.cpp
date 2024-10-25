#include "Grammar.hpp"

size_t Grammar::Hash::operator()(const Grammar& grammar_) const {
  return std::hash<size_t>()(std::hash<std::string>()(grammar_.right) +
                             std::hash<char>()(grammar_.left));
}
bool Grammar::operator==(const Grammar& other) const {
  return left == other.left && right == other.right;
}
Grammar::Grammar(char left, const std::string& right)
    : left(left), right(right) {}
