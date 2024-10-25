#include "Earley.hpp"

int main() {
  int numGrammars;
  std::vector<Grammar> grammars;

  std::cout << "Enter number of grammar rules: " << std::endl;
  std::cin >> numGrammars;

  for (int i = 0; i < numGrammars; i++) {
    char left;
    std::string right;
    std::cout << "Enter one of the rule of the grammar: " << std::endl;
    std::cin >> left >> right;
    grammars.emplace_back(Grammar(left, right));
  }

  EarleyAnalyse parser(grammars, 'S');
  std::string word;
  char continueTesting;

  do {
    std::cout << "Enter the word: " << std::endl;
    std::cin >> word;

    bool comprisesSymbol = parser.CompriseSymbol(word);
    std::cout << (comprisesSymbol ? "YES" : "NO") << std::endl;

    std::cout << "Do you want to test another word? (y/n) " << std::endl;
    std::cin >> continueTesting;
  } while (continueTesting == 'y' || continueTesting == 'Y');

  return 0;
}
