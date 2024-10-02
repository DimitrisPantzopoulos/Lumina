#ifndef BOOK_H
#define BOOK_H

#include "..\ChessLib\chess-library-master\include\chess.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


using namespace std;
//Code Used from https://www.geeksforgeeks.org/trie-data-structure-in-cpp/ ty sm :)


//class for a node of the trie
class TrieNode {
public:
    bool EndOfWord;
    std::unordered_map<std::string, std::shared_ptr<TrieNode>> children;

    TrieNode() : EndOfWord(false) {}
};

class Trie {
private:
    std::shared_ptr<TrieNode> root;

public:
    Trie() {
        root = std::make_shared<TrieNode>();
    }

    void insert(const std::vector<std::string>& words);

    std::tuple<bool, std::string> FindNextMove(const std::vector<std::string>& sequence) const;
};


void LoadOpeningBook(Trie& trie, const std::string& filename);
#endif