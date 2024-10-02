#include "Book.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void Trie::insert(const std::vector<std::string>& words) {
    std::shared_ptr<TrieNode> node = root;
    
    for (const auto& word : words) {
        if (node->children.find(word) == node->children.end()) {
            node->children[word] = std::make_shared<TrieNode>();
        }
        node = node->children[word];
    }
    node->EndOfWord = true;
}

std::tuple<bool, std::string> Trie::FindNextMove(const std::vector<std::string>& sequence) const {
    std::shared_ptr<TrieNode> node = root;

    for(const auto& word : sequence){
        if (node->children.find(word) == node->children.end()) {
            return std::make_tuple(false, "");
        }
        node = node->children[word];
    }
    
    if (!node->children.empty()) {
        //Return a random childs key
        return std::make_tuple(true, node->children.begin()->first);
    } else {
        return std::make_tuple(false, "");
    }
}


void LoadOpeningBook(Trie& trie, const std::string& filename){
    std::ifstream infile(filename);
    std::string line;

    if (!infile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> moves;
        std::string move;
        
        while (iss >> move) {
            moves.push_back(move);
        }

        //Insert the sequence of moves into the trie
        trie.insert(moves);
    }
}