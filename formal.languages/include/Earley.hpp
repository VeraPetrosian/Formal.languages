#pragma once
#include <algorithm>
#include <cmath>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Grammar.hpp"
#include "Situation.hpp"

typedef std::unordered_set<Situation, Situation::Hash> config_t;
typedef std::vector<config_t> configset_t;
typedef std::unordered_set<Grammar, Grammar::Hash> grammar_t;
typedef std::unordered_map<char, grammar_t> grammarset_t;

class EarleyAnalyse {
 public:
  EarleyAnalyse(const std::vector<Grammar>& grammars, char first_symbol);

  bool CompriseSymbol(const std::string& symbol);

 private:
  bool Build(char first_symbol, const std::string& symbol);

  void CompletePredict(int config_index);

  char first_symbol;

  grammarset_t grammar_set;

  configset_t configs;
};

class Earley {
 public:
  static void Predict(grammarset_t& grammar_set, configset_t& configs,
                      int config_index);

  static void Scan(configset_t& configs, char next_symbol, int config_index);

  static void Complete(configset_t& configs, int config_index);

  static void SetRule(grammarset_t& grammar_set,
                      const std::vector<Grammar>& grammars);
};
