#include "utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>

std::string readCodeFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open code file: " + filename);
    }
    return std::string((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
}

void writeTokensToFile(const std::vector<std::pair<int, std::string>>& tokens,
    Lexer& lexer,
    const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }

    for (const auto& token : tokens) {
        file << token.first << " " << token.second << " # "
            << lexer.getTokenTypeName(token.first) << std::endl;
    }
}

void printTokens(const std::vector<std::pair<int, std::string>>& tokens, Lexer& lexer) {
    std::cout << "Found " << tokens.size() << " tokens:" << std::endl;
    std::cout << "Index | Token                | Type" << std::endl;
    std::cout << "------+----------------------+----------------" << std::endl;

    for (const auto& token : tokens) {
        std::cout << std::setw(5) << token.first << " | "
            << std::setw(20) << std::left << token.second << " | "
            << lexer.getTokenTypeName(token.first) << std::endl;
    }
}