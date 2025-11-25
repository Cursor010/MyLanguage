#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "lexer.h"

// Функция для чтения файла с кодом
std::string readCodeFromFile(const std::string& filename);

// Функция для записи токенов в файл
void writeTokensToFile(const std::vector<std::pair<int, std::string>>& tokens,
    Lexer& lexer,
    const std::string& filename);

// Функция для вывода токенов в консоль
void printTokens(const std::vector<std::pair<int, std::string>>& tokens, Lexer& lexer);

#endif