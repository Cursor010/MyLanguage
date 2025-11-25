#include "trie.h"

Trie::Trie() : root(new TrieNode()) {}

Trie::~Trie() {
    clearTrie(root);
}


void Trie::insert(const std::string& str, int tokenIndex, const std::string& tokenType) {
    TrieNode* node = root;
    for (char c : str) {
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
    }
    node->tokenIndex = tokenIndex;
    node->tokenType = tokenType;
}

int Trie::findLongestToken(const std::string& str, size_t& pos, std::string& foundTokenType) {
    TrieNode* node = root;
    int lastTokenIndex = -1;
    size_t lastPos = pos;
    std::string lastTokenType = "";

    for (size_t i = pos; i < str.length(); ++i) {
        char c = str[i];
        if (node->children.find(c) == node->children.end()) break;

        node = node->children[c];
        if (node->tokenIndex != -1) {
            lastTokenIndex = node->tokenIndex;
            lastTokenType = node->tokenType;
            lastPos = i + 1;
        }
    }

    if (lastTokenIndex != -1) {
        pos = lastPos;
        foundTokenType = lastTokenType;
    }
    return lastTokenIndex;
}

void Trie::clearTrie(TrieNode* node) {
    for (auto& child : node->children) {
        clearTrie(child.second);
    }
    delete node;
}