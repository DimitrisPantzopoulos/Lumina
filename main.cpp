#include "ChessLib/chess-library-master/include/chess.hpp"
#include "Lumina.h"
#include "Book/Book.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define AvgMovesaGame 60

using namespace std;

Lumina bot;
Trie book;
chess::Board board;
string FEN = board.getFen();

void FindBestMove(vector<string>& sequence, int Milliseconds) {
    Move bestMove = bot.Think(board, Milliseconds);
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
            istringstream iss(command);
            string token, fen;
            std::vector<string> TimeControl;

            while (iss >> token){
                if(token == "wtime" || token == "btime"){continue;}
                TimeControl.push_back(token);
            }
            
            //The commented code is an attempt to dynamically find how long we should search based on how much time is left, I've left it out because i think to improve the
            //search function it would be better to have this variable be the same for testing purposes. Also this has a wierd bug which causes the program to disconnect from 
            //fastchess my guess is because its trying to search for a few milliseconds it cant do it fast enough so it just returns a null move or smth.
            int TimeToSearch = 100; //(board.sideToMove() == Color::WHITE ? std::stoi(TimeControl[2]) : std::stoi(TimeControl[4])) / (AvgMovesaGame - sequence.size() + 1);   

            if (!opening) {
                FindBestMove(sequence, TimeToSearch);
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
                    FindBestMove(sequence, TimeToSearch);
                }
            }
        }

        else if (command.substr(0, 12) == "position fen") {
            // Handle FEN input and apply moves if present
            istringstream iss(command);
            string token, fen;
            iss >> token >> token;

            // Capture FEN string
            while (iss >> token && token != "moves")
                fen += token + " ";

            if (!fen.empty() && fen.back() == ' ') fen.pop_back();
            board.setFen(fen); 
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
