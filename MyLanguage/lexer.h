#ifndef LEXER_H
#define LEXER_H

#include "trie.h"
#include <vector>
#include <string>
#include <unordered_map>

class Lexer {
public:
    Lexer() = default;

    bool loadTokensFromFile(const std::string& filename);
    std::vector<std::pair<int, std::string>> tokenize(const std::string& input);
    std::string getTokenTypeName(int tokenIndex);

private:
    Trie trie;
    std::unordered_map<int, std::string> tokenNames;
};

#endif