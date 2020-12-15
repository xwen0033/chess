#include "Pieces.h"

ostream& operator<<(ostream& o, Colour c) {
    switch(c) {
        case WHITE: o << "White"; break;
        case BLACK: o << "Black";
    }
    return o;
}

ostream& operator<<(ostream& o, Type t){
    switch(t) {
        case None: o << "None"; break;
        case Pawn: o << "Pawn"; break;
        case Knight: o << "Knight"; break;
        case Bishop: o << "Bishop"; break;
        case Rook: o << "Bishop"; break;
        case Queen: o << "Queen"; break;
        case King: o << "King"; 
    }
    return o;
}

Piece::Piece(Colour colour):colour(colour) { sign = ' '; }
char Piece::getSign(){ return sign; }
Type Piece::getType(){ return type; }
bool Piece::moveValid(int s_rank, int s_file, int d_rank, int d_file, int wCount, int bCount){}
bool Piece::captureValid(int s_rank, int s_file, int d_rank, int d_file){}
Piece::~Piece(){}

Pawn::Pawn(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'p') : (sign = 'P');
}

char Pawn::getSign() { return sign; } 
Type Pawn::getType() { return type; }
bool Pawn::moveValid(int s_rank, int s_file, int d_rank, int d_file, int wCount, int bCount){
    if (s_file != d_file) { return false; }
    if (colour == WHITE){
        if (d_rank >= s_rank){ return false; }
        int distance = s_rank - d_rank;
        if (wCount != 0 && distance != 1) { return false; }
        if (wCount == 0 && distance != 2 && distance != 1){ return false; }
    } else { //black pawns
        if (d_rank <= s_rank) { return false; }
        int distance = d_rank - s_rank;
        if (bCount != 0 && distance != 1) { return false; }
        if (bCount == 0 && distance != 2 && distance != 1){ return false; }
    }
    return true;
}

bool Pawn::captureValid(int s_rank, int s_file, int d_rank, int d_file){
    int file_distance = d_file - s_file;
    if (file_distance != 1 && file_distance != -1){ return false; }
    if (colour == WHITE){
        if (d_rank >= s_rank){ return false; }
        int distance = s_rank - d_rank;
        if (distance != 1){ return false; }
    } else { //black pawns
        if (d_rank <= s_rank) { return false; }
        int distance = d_rank - s_rank;
        if (distance != 1){ return false; }
    }
    return true;
}

Pawn::~Pawn(){}

Knight::Knight(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'n') : (sign = 'N');
}

char Knight::getSign() { return sign; } 
Type Knight::getType() { return type; }
Knight::~Knight(){}

Bishop::Bishop(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'b') : (sign = 'B');
}

char Bishop::getSign() { return sign; } 
Type Bishop::getType() { return type; }
Bishop::~Bishop(){}

Rook::Rook(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'r') : (sign = 'R');
}

char Rook::getSign() { return sign; } 
Type Rook::getType() { return type; }
Rook::~Rook(){}

Queen::Queen(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'q') : (sign = 'Q');
}

char Queen::getSign() { return sign; } 
Type Queen::getType() { return type; }
Queen::~Queen(){}

King::King(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'k') : (sign = 'K');
}

char King::getSign() { return sign; } 
Type King::getType() { return type; }
King::~King(){}