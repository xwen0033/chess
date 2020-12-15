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
bool Piece::moveValid(int s_rank, int s_file, int d_rank, int d_file){ return false;}
bool Piece::captureValid(int s_rank, int s_file, int d_rank, int d_file){ return false; }
Piece::~Piece(){}

Pawn::Pawn(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'p') : (sign = 'P');
    count = 0;
}

char Pawn::getSign() { return sign; } 
Type Pawn::getType() { return type; }
bool Pawn::moveValid(int s_rank, int s_file, int d_rank, int d_file){
    if (s_file != d_file) { return false; }
    if (colour == WHITE){
        if (d_rank >= s_rank){ return false; }
        int distance = s_rank - d_rank;
        //move forward one square if not first move
        if (count != 0 && distance != 1) { return false; }
        if (count == 0 && distance != 2 && distance != 1){ return false; }
    } else { //black pawns
        if (d_rank <= s_rank) { return false; }
        int distance = d_rank - s_rank;
        if (count != 0 && distance != 1) { return false; }
        if (count == 0 && distance != 2 && distance != 1){ return false; }
    }
    count++;
    return true;
}

bool Pawn::captureValid(int s_rank, int s_file, int d_rank, int d_file){
    int file_distance = abs(d_file - s_file);
    if (file_distance != 1){ return false; }
    if (colour == WHITE){
        if (d_rank >= s_rank){ return false; }
        int distance = s_rank - d_rank;
        if (distance != 1){ return false; }
    } else { //black pawns
        if (d_rank <= s_rank) { return false; }
        int distance = d_rank - s_rank;
        if (distance != 1){ return false; }
    }
    count++;
    return true;
}

Pawn::~Pawn(){}

Knight::Knight(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'n') : (sign = 'N');
}

char Knight::getSign() { return sign; } 
Type Knight::getType() { return type; }
bool Knight::moveValid(int s_rank, int s_file, int d_rank, int d_file){
    if (captureValid(s_rank, s_file, d_rank, d_file)) { return true; }
    return false;
}
bool Knight::captureValid(int s_rank, int s_file, int d_rank, int d_file){
    int rank_distance = abs(s_rank - d_rank);
    int file_distance = abs(s_file - d_file);
    if (rank_distance == 2 && file_distance == 1) { return true; }
    if (rank_distance == 1 && file_distance == 2) { return true; }
    return false;
}
Knight::~Knight(){}

Bishop::Bishop(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'b') : (sign = 'B');
}

char Bishop::getSign() { return sign; } 
Type Bishop::getType() { return type; }

bool Bishop::moveValid(int s_rank, int s_file, int d_rank, int d_file){
    if (captureValid(s_rank, s_file, d_rank, d_file)) { return true; }
    return false;
}
bool Bishop::captureValid(int s_rank, int s_file, int d_rank, int d_file){
    int rank_distance = abs(s_rank - d_rank);
    int file_distance = abs(s_file - d_file);
    if (rank_distance == file_distance) { return true; }
    return false;
}

Bishop::~Bishop(){}

Rook::Rook(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'r') : (sign = 'R');
}

char Rook::getSign() { return sign; } 
Type Rook::getType() { return type; }
bool Rook::moveValid(int s_rank, int s_file, int d_rank, int d_file) {
    if (captureValid(s_rank, s_file, d_rank, d_file)) { return true; }
    return false;
}
bool Rook::captureValid(int s_rank, int s_file, int d_rank, int d_file){
    //along the rank
    if (d_rank == s_rank && d_file != s_file){ return true; }
    //along the file
    if (d_file == s_file && d_rank != s_rank) { return true; }
    return false;
}

Rook::~Rook(){}

Queen::Queen(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'q') : (sign = 'Q');
}

char Queen::getSign() { return sign; } 
Type Queen::getType() { return type; }
bool Queen::moveValid(int s_rank, int s_file, int d_rank, int d_file) {
    if (captureValid(s_rank, s_file, d_rank, d_file)) { return true; }
    return false;
}
bool Queen::captureValid(int s_rank, int s_file, int d_rank, int d_file) {
    //moving horizontally along the rank
    if (d_rank == s_rank && d_file != s_file){ return true; }
    //moving vertically along the file
    if (d_file == s_file && d_rank != s_rank) { return true; }
    int rank_distance = abs(s_rank - d_rank);
    int file_distance = abs(s_file - d_file);
    //moving diagonally
    if (rank_distance == file_distance) { return true; }
    return false;
}
Queen::~Queen(){}

King::King(Colour colour):Piece(colour){
    (colour == BLACK) ? (sign = 'k') : (sign = 'K');
}

char King::getSign() { return sign; } 
Type King::getType() { return type; }

bool King::moveValid(int s_rank, int s_file, int d_rank, int d_file){
    if (captureValid(s_rank, s_file, d_rank, d_file)) { return true; }
    return false;
}

bool King::captureValid(int s_rank, int s_file, int d_rank, int d_file){
    int rank_distance = abs(s_rank - d_rank);
    int file_distance = abs(s_file - d_file);
    //moving horizontally 1 square along the rank
    if (d_rank == s_rank && file_distance == 1 ){ return true; }
    //moving vertically 1 square along the file
    if (d_file == s_file && rank_distance == 1) { return true; }
    //moving diagonally 1 square
    if (rank_distance == 1 && file_distance == 1) { return true; }
    return false;
}

King::~King(){}