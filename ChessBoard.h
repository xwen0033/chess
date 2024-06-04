#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Pieces.h"
#include <vector>
#include <iostream>

using namespace std;

struct KingPosition {
    int rank;
    int file;
};

class ChessBoard {
    //array of pointers to pieces or nullptr for unoccupied squares
    Piece* board[8][8]; 
    bool turn; //which side's turn: black or white
    int wCount; //white move count
    int bCount; //black move count
public:
    ChessBoard();
    void printBoard();
    void printFrame();
    void printRank(int r);
    void placePieces(); //place pieces at their begining positions on board 
    void erasePieces(); //delete all pieces on board

    KingPosition getKingPosition(Colour colour);

    //whether opponent is in check after moving the piece to destination
    bool isInCheck(Colour attack_colour);

    std::vector <int> possibleMoves(int rank, int file);
    std::vector <int> possibleCaptures(int rank, int file);

    //loop through possible moves to get king out of check
    //if no such move exists, return true otherwise false
    bool checkMate(Colour colour);

    //some sanity checks
    int checksquare(char const* source, char const* destination);

    void submitMove(char const* source, char const* destination);

    //whether other piece is in the way: 
    //return false if route not clear 
    bool enrouteClear(int s_rank, int s_file, int d_rank, int d_file);
    void resetBoard();
    ~ChessBoard();
};

#endif
