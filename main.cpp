#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "ChessLib\chess-library-master\include\chess.hpp"
#include "Dimibot.h"
#include "Book\Book.h"

using namespace std;

Dimibot Bot;
Trie Book;
chess::Board board;
string FEN = board.getFen();

void FindBestMove(std::vector<std::string>& Sequence){
    //Find the best move
    Move BestMove = Bot.Think(board, 100);

    //Add the move to the sequence
    Sequence.push_back(uci::moveToSan(board,BestMove));

    //Apply the move to the board
    board.makeMove(BestMove);
}

void uci_loop() {
    bool Opening = false;
    std::vector<std::string> Sequence;

    while (true) {
        // Read a command from the user
        string command;
        getline(cin, command);

        // Process the command
        if (command == "uci") {
            cout << "id name Dimibot" << endl;
            cout << "id author Dimiboi" << endl;
            cout << "uciok" << endl;
        }
        else if (command.substr(0, 17) == "position startpos") {
            vector<string> info;
            istringstream iss(command);

            for(string s; iss >> s; )
                info.push_back(s);

            if (info.size() > 2) {
                // If they have alternate moves then we know that other moves have been played else just return the starting FEN to the engine
                chess::Move OppMove = uci::uciToMove(board, info.back());
                Sequence.push_back(uci::moveToSan(board, OppMove));
                board.makeMove(OppMove);
            }
            else if (info.size() == 2){
                FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
            }

            FEN = board.getFen();
        }
        else if (command.substr(0, 2) == "go") {
            // Make the Engine find the best move
            vector<string> info;
            istringstream iss(command);

            for(string s; iss >> s; )
                info.push_back(s);

            if(!Opening){
                FindBestMove(Sequence);

            }else{
                bool NextFound = false;
                std::string SanMove;

                //Try to find a book move
                tie(NextFound, SanMove) = Book.FindNextMove(Sequence);

                if(NextFound){
                    //If found ask play that move
                    chess::Move NextMove = chess::uci::parseSan(board, SanMove);

                    Sequence.push_back(SanMove);

                    board.makeMove(NextMove);

                    cout << "bestmove " << chess::uci::uciToMove(board, uci::moveToUci(NextMove) )<< endl;

                }else{
                    //else fall back on the engine to find the optimal move
                    Opening = false;
                    FindBestMove(Sequence);
                }
            }

        }else if (command.substr(0, 12) == "position fen") {
            // Handle "position fen <fen-string> [moves ...]"
            istringstream iss(command);
            string token;
            string fen = "";

            // Skip the "position" and "fen" keywords
            iss >> token;  // position
            iss >> token;  // fen

            // Read the FEN string until we encounter "moves"
            while (iss >> token && token != "moves")
                fen += token + " ";
            
            if (!fen.empty() && fen.back() == ' ') {
                fen.pop_back();
            }

            // Set the FEN on the board
            board.setFen(fen);
            Sequence.clear();

            while (iss >> token) {
                chess::Move move = chess::uci::uciToMove(board, token);
                board.makeMove(move);
                //Sequence.push_back(chess::uci::moveToSan(board, move));
            }
        }else if (command == "quit") {
            // Handle the quit command
            break;
        }
        else if (command == "ucinewgame") {
            // Reset the board for a new game
            Bot.ClearTT();
            board.setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
            Sequence.clear();
            Opening = false;
        } 
        else if (command == "isready") {
            cout << "readyok" << endl;
        }
        else {
            // Unknown command
            cout << "Unknown command: " << command << endl;
        }
    }
}

int main() {
    LoadOpeningBook(Book,"Book/Book.txt");

    uci_loop();

    return 0;
}