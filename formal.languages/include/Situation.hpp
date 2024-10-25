#pragma once
#include <iostream>
#include <string>

#include "Grammar.hpp"

class Situation : public Grammar {
 public:
  struct Hash {
    size_t operator()(const Situation& situation_) const;
  };

  int start;

  int cur_point;

  Situation(char left, const std::string& right, int start, int index);

  Situation(const Grammar& grammar, int start, int index);

  bool operator==(const Situation& other) const;
};
