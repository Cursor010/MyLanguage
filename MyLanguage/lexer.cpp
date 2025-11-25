#include "lexer.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>

bool Lexer::loadTokensFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open tokens file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string token;
        int index;
        std::string typeName;

        if (iss >> token >> index >> typeName) {
            trie.insert(token, index, typeName);
            tokenNames[index] = typeName;
        }
        else if (iss >> token >> index) {
            trie.insert(token, index, token);
            tokenNames[index] = token;
        }
    }

    file.close();
    return true;
}

std::vector<std::pair<int, std::string>> Lexer::tokenize(const std::string& input) {
    std::vector<std::pair<int, std::string>> tokens;
    size_t pos = 0;

    while (pos < input.length()) {
        if (std::isspace(input[pos])) {
            ++pos;
            continue;
        }

        if (pos + 1 < input.length() && input[pos] == '/' && input[pos + 1] == '/') {
            while (pos < input.length() && input[pos] != '\n') {
                ++pos;
            }
            continue;
        }

        if (pos + 1 < input.length() && input[pos] == '/' && input[pos + 1] == '*') {
            pos += 2;
            while (pos + 1 < input.length() && !(input[pos] == '*' && input[pos + 1] == '/')) {
                ++pos;
            }
            pos += 2;
            continue;
        }

        size_t start = pos;
        std::string tokenType;
        int tokenIndex = trie.findLongestToken(input, pos, tokenType);

        if (tokenIndex != -1) {
            std::string token = input.substr(start, pos - start);
            tokens.emplace_back(tokenIndex, token);
            continue;
        }

        if (std::isalpha(input[pos]) || input[pos] == '_') {
            size_t start = pos;
            while (pos < input.length() &&
                (std::isalnum(input[pos]) || input[pos] == '_')) {
                ++pos;
            }
            std::string identifier = input.substr(start, pos - start);
            tokens.emplace_back(2, identifier);
            continue;
        }

        if (std::isdigit(input[pos])) {
            size_t start = pos;
            bool hasDot = false;
            while (pos < input.length() &&
                (std::isdigit(input[pos]) || (!hasDot && input[pos] == '.'))) {
                if (input[pos] == '.') hasDot = true;
                ++pos;
            }
            std::string number = input.substr(start, pos - start);
            tokens.emplace_back(3, number);
            continue;
        }

        if (input[pos] == '"') {
            size_t start = pos;
            ++pos;
            while (pos < input.length() && input[pos] != '"') {
                if (input[pos] == '\\' && pos + 1 < input.length()) {
                    ++pos;
                }
                ++pos;
            }
            if (pos < input.length()) {
                ++pos;
            }
            std::string strLiteral = input.substr(start, pos - start);
            tokens.emplace_back(5, strLiteral);
            continue;
        }

        if (input[pos] == '\'') {
            size_t start = pos;
            ++pos;
            if (pos < input.length() && input[pos] == '\\') {
                ++pos;
            }
            if (pos < input.length()) {
                ++pos;
            }
            if (pos < input.length() && input[pos] == '\'') {
                ++pos;
            }
            std::string charLiteral = input.substr(start, pos - start);
            tokens.emplace_back(6, charLiteral);
            continue;
        }

        tokens.emplace_back(-1, std::string(1, input[pos++]));
    }

    return tokens;
}

std::string Lexer::getTokenTypeName(int tokenIndex) {
    auto it = tokenNames.find(tokenIndex);
    if (it != tokenNames.end()) {
        return it->second;
    }

    switch (tokenIndex) {
    case 2: return "IDENTIFIER";
    case 3: return "NUMBER";
    case 5: return "STRING_LITERAL";
    case 6: return "CHAR_LITERAL";
    case -1: return "UNKNOWN";
    default: return "TOKEN_" + std::to_string(tokenIndex);
    }
}