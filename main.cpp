#include "ChessLib/chess-library/include/chess.hpp"
#include "Lumina.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace chess;

const char* DEFAULTFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

void HandleUCIStart(){
    std::cout << "id name Lumina \n";
    std::cout << "id author Dimiboi \n";

    // Print the ASCII art
    std::cout << "info string" << R"(    __                 _                   *                )" << "\n";
    std::cout << "info string" << R"(   / /  _   _ _ __ ___ (_)_ __   __ _       \               )" << "\n";
    std::cout << "info string" << R"(  / /  | | | | '_ ` _ \| | '_ \ / _` |       * --- *   *    )" << "\n";
    std::cout << "info string" << R"( / /__ | |_| | | | | | | | | | | (_| |              \ /     )" << "\n";
    std::cout << "info string" << R"( \____/\____ |_| |_| |_|_|_| |_|\__,_|               *      )" << "\n";
                                      
    // End Handshake
    std::cout << "uciok\n";
}

void HandleIsReady(){
    std::cout << "readyok \n";
}

void HandleUCINewGame(Lumina& Lumina, chess::Board& Board){
    // Reset Board
    Board.setFen(DEFAULTFEN); 

    // Reset Lumina
    Lumina.ClearKMT();
    Lumina.ClearTT();
}

void HandlePosition(chess::Board& Board, const vector<string>& Tokens){
    // Handle Error
    if (Tokens.size() <= 1){
        std::cout << "[ERROR] Unknown Position Command! Quitting program" << std::endl;
        std::exit(0);
    }

    const string PositionCommand = Tokens[1];

    // Find the position in the vector of the "moves" token
    auto it = std::find(Tokens.begin(), Tokens.end(), "moves");

    // Assert that the "moves" token is in the vector 

    // Now we have the FEN and Moves indexes
    int MovesIdx = it == Tokens.end() ? int(Tokens.size()) : int(std::distance(Tokens.begin(), it));

    // Handle UCI Startpos
    if (PositionCommand == "startpos") {
        Board.setFen(DEFAULTFEN);
    }
    
    // Handle Custom FEN
    else if (PositionCommand == "fen") {
        // Get the full FEN and apply it to the board
        // This is to prevent subtle errors
        assert(MovesIdx - 2 == 6);

        string FEN = Tokens[2];
        for (int i=3;i<MovesIdx;i++) {FEN += " " + Tokens[i];}

        Board.setFen(FEN);
    }

    // Now apply the Moves
    for (int i=MovesIdx+1;i<Tokens.size();i++) {Board.makeMove(chess::uci::uciToMove(Board, Tokens[i]));}
}

void HandleGo(vector<string> Tokens, chess::Board& Board, Lumina& Lumina){
    int TokenSize = Tokens.size();

    int WhiteTime = 0;
    int BlackTime = 0;
    int WInc = 0;
    int BInc = 0;

    for (int i=0;i<Tokens.size() - 1;i++){
        string Token = Tokens[i];

        if      (Token == "wtime") {WhiteTime = std::stoi(Tokens[++i]);}
        else if (Token == "btime") {BlackTime = std::stoi(Tokens[++i]);}
        else if (Token == "winc" ) {WInc      = std::stoi(Tokens[++i]);}
        else if (Token == "binc" ) {BInc      = std::stoi(Tokens[++i]);}
    }

    // Basic Time Control Formula:  (STM Time / 20) + (STM Inc / 2)
    int TimeControl = Board.sideToMove() == chess::Color::WHITE ?
                      (WhiteTime / 20) + (WInc / 2) :
                      (BlackTime / 20) + (BInc / 2);

    Lumina.Think(Board, TimeControl);
}

void UCI() {
    Lumina Lumina;
    Board  Board;
    string Line;

    while (getline(cin, Line)) {
        // Receieve Info from the CLI to make the engine take an action
        istringstream CLI(Line);
        vector<string> Tokens;
        string Token;

        while (CLI >> Token)   {Tokens.push_back(Token);}
        if    (Tokens.empty()) {continue;}

        // The first Token is the command
        const string Command = Tokens[0];

        if (Command == "uci") {
            HandleUCIStart();
        }

        else if (Command == "position") {
            HandlePosition(Board, Tokens);
        }

        else if (Command == "go") {
            HandleGo(Tokens, Board, Lumina);
        }

        else if (Command == "ucinewgame") {
            HandleUCINewGame(Lumina, Board);
        }

        else if (Command == "isready") {
            HandleIsReady();
        }

        else if (Command == "quit") {
            std::exit(0);
        }
        
        else {
            // Unknown or unsupported commands
            cout << "Unknown command: " << Command << endl;
        }
    }
}

int main() {
    UCI();

    return 0;
}
