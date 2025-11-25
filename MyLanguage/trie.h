#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <unordered_map>

// Структура узла бора
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    int tokenIndex = -1;
    std::string tokenType = "";
};

// Класс для реализации бора
class Trie {
public:
    Trie();
    ~Trie();

    void insert(const std::string& str, int tokenIndex, const std::string& tokenType = "");
    int findLongestToken(const std::string& str, size_t& pos, std::string& foundTokenType);

private:
    void clearTrie(TrieNode* node);
    TrieNode* root;
};

#endif