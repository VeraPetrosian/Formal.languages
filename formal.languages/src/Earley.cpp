#include "Earley.hpp"

void Earley::Scan(configset_t& configs, char next_symbol, int config_index) {
  config_t tmp_config_set;
  for (const auto& cur_situation : configs[config_index]) {
    if (cur_situation.cur_point >= cur_situation.right.size()) {
      continue;
    }
    if (cur_situation.right[cur_situation.cur_point] == next_symbol) {
      tmp_config_set.insert(Situation(cur_situation.left, cur_situation.right,
                                      cur_situation.start,
                                      cur_situation.cur_point + 1));
    }
  }
  configs.emplace_back(tmp_config_set);
}

void Earley::Predict(grammarset_t& grammar_set, configset_t& configs,
                     int config_index) {
  config_t tmp_config_set;
  for (const auto& cur_situation : configs[config_index]) {
    if (cur_situation.cur_point >= cur_situation.right.size()) {
      continue;
    }
    char point_front_symbol = cur_situation.right[cur_situation.cur_point];
    if (grammar_set.find(point_front_symbol) != grammar_set.end()) {
      const auto& current_grammars = grammar_set[point_front_symbol];
      for (const auto& cur_grammar : current_grammars) {
        tmp_config_set.insert(Situation(cur_grammar, config_index, 0));
      }
    }
  }
  configs[config_index].merge(tmp_config_set);
}

void Earley::Complete(configset_t& configs, int config_index) {
  config_t tmp_config_set;
  for (const auto& cur_situation : configs[config_index]) {
    if (cur_situation.cur_point < cur_situation.right.size()) {
      continue;
    }
    const auto& cur_config_set = configs[cur_situation.start];
    for (const auto& config : cur_config_set) {
      if (config.cur_point >= config.right.size()) {
        continue;
      }
      if (config.right[config.cur_point] == cur_situation.left) {
        tmp_config_set.insert(Situation(config.left, config.right, config.start,
                                        config.cur_point + 1));
      }
    }
  }
  configs[config_index].merge(tmp_config_set);
}

void Earley::SetRule(grammarset_t& grammar_set,
                     const std::vector<Grammar>& grammars) {
  grammar_t tmp_grammar_set;
  for (const auto& cur_grammar : grammars) {
    if (grammar_set.find(cur_grammar.left) != grammar_set.end()) {
      grammar_set[cur_grammar.left].insert(cur_grammar);
      continue;
    }
    tmp_grammar_set.clear();
    tmp_grammar_set.insert(cur_grammar);
    grammar_set.insert({cur_grammar.left, tmp_grammar_set});
  }
  tmp_grammar_set.clear();
  tmp_grammar_set.insert(Grammar('.', std::string(1, 'S')));
  grammar_set.insert({'.', tmp_grammar_set});
}

EarleyAnalyse::EarleyAnalyse(const std::vector<Grammar>& grammars,
                             char first_symbol)
    : first_symbol(first_symbol) {
  Earley::SetRule(grammar_set, grammars);
  config_t tmp_config_set;
  tmp_config_set.insert(Situation('.', std::string(1, first_symbol), 0, 0));
  configs.emplace_back(tmp_config_set);
}

bool EarleyAnalyse::CompriseSymbol(const std::string& symbol) {
  configs.resize(1);
  return Build(first_symbol, symbol);
}

void EarleyAnalyse::CompletePredict(int config_index) {
  int previous_size = configs[config_index].size();
  int new_size = configs[config_index].size();
  do {
    Earley::Predict(grammar_set, configs, config_index);
    Earley::Complete(configs, config_index);
    previous_size = new_size;
    new_size = configs[config_index].size();
  } while (new_size != previous_size);
}

bool EarleyAnalyse::Build(char first_symbol, const std::string& symbol) {
  CompletePredict(0);
  for (int j = 1; j <= symbol.size(); ++j) {
    Earley::Scan(configs, symbol[j - 1], j - 1);
    CompletePredict(j);
  }
  Situation found_situation('.', std::string(1, first_symbol), 0, 1);
  return configs[symbol.size()].find(found_situation) !=
         configs[symbol.size()].end();
}
