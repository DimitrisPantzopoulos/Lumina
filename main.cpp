#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "ChessLib/chess-library-master/include/chess.hpp"
#include "Dimibot.h"
#include "Book/Book.h"

using namespace std;

Dimibot bot;
Trie book;
chess::Board board;
string FEN = board.getFen();

// Function to find and apply the best move using the engine
void FindBestMove(vector<string>& sequence) {
    Move bestMove = bot.Think(board, 100);
    sequence.push_back(uci::moveToSan(board, bestMove));
    board.makeMove(bestMove);
}

// Function to handle UCI commands and game loop
void uci_loop() {
    bool opening = false;
    vector<string> sequence;

    while (true) {
        string command;
        getline(cin, command);

        if (command == "uci") {
            cout << "id name Dimibot" << endl;
            cout << "id author Dimiboi" << endl;
            cout << "option name Threads type spin default 1 min 1 max 1" << endl;

            cout << "uciok" << endl;
        }

        else if (command.substr(0, 17) == "position startpos") {
            vector<string> info;
            istringstream iss(command);
            string word;
            while (iss >> word) info.push_back(word);

            if (info.size() > 2) {
                // If additional moves exist, apply the opponent's move
                chess::Move opponentMove = uci::uciToMove(board, info.back());
                sequence.push_back(uci::moveToSan(board, opponentMove));
                board.makeMove(opponentMove);
            } else {
                // Reset to starting position if no moves have been played
                board.setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
            }

            FEN = board.getFen();
        }

        else if (command.substr(0, 2) == "go") {
            if (!opening) {
                FindBestMove(sequence);  // Use the engine to find the best move
            } else {
                bool nextFound = false;
                string sanMove;
                tie(nextFound, sanMove) = book.FindNextMove(sequence);

                if (nextFound) {
                    chess::Move nextMove = chess::uci::parseSan(board, sanMove);
                    sequence.push_back(sanMove);
                    board.makeMove(nextMove);
                    cout << "bestmove " << uci::moveToUci(nextMove) << endl;
                } else {
                    // Fall back to engine if no book move is found
                    opening = false;
                    FindBestMove(sequence);
                }
            }
        }

        else if (command.substr(0, 12) == "position fen") {
            // Handle FEN input and apply moves if present
            istringstream iss(command);
            string token, fen;
            iss >> token >> token;  // Skip "position fen"

            // Capture FEN string
            while (iss >> token && token != "moves")
                fen += token + " ";

            if (!fen.empty() && fen.back() == ' ') fen.pop_back();
            board.setFen(fen);  // Set the FEN position on the board
            sequence.clear();

            // Apply any subsequent moves
            while (iss >> token) {
                chess::Move move = uci::uciToMove(board, token);
                board.makeMove(move);
            }
        }

        else if (command == "quit") {
            break;  // Exit the loop and terminate the program
        }

        else if (command == "ucinewgame") {
            // Reset for a new game
            bot.ClearTT();
            board.setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
            sequence.clear();
            opening = false;
        }

        else if (command == "isready") {
            cout << "readyok" << endl;
        }

        else {
            // Unknown or unsupported commands
            cout << "Unknown command: " << command << endl;
        }
    }
}

int main() {
    LoadOpeningBook(book, "Book/Book.txt");
    uci_loop();

    return 0;
}
