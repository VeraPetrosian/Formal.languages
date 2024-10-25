#pragma once
#include <iostream>
#include <string>

class Grammar {
 public:
  struct Hash {
    size_t operator()(const Grammar& grammar_) const;
  };

  char left;

  std::string right;

  Grammar(char left, const std::string& right);

  bool operator==(const Grammar& other) const;
};
