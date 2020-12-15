#include "ChessBoard.h"
#include <iostream>

using namespace std;


void ChessBoard::placePieces(){
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++){
            if (r == 0){
                if(f == 1 || f == 6){
                    board[r][f] = new class Knight(BLACK);
                } else if(f == 2 || f == 5){
                    board[r][f] = new class Bishop(BLACK);
                } else if(f == 0 || f == 7){
                    board[r][f] = new class Rook(BLACK);
                } else if(f == 3){
                    board[r][f] = new class Queen(BLACK);
                } else if(f == 4){
                    board[r][f] = new class King(BLACK);
                }
            } else if (r == 1){
                board[r][f] = new class Pawn(BLACK);
            } else if (r == 6){
                board[r][f] = new class Pawn(WHITE);
            } else if (r == 7) {
                if(f == 1 || f == 6){
                    board[r][f] = new class Knight(WHITE);
                } else if(f == 2 || f == 5){
                    board[r][f] = new class Bishop(WHITE);
                } else if(f == 0 || f == 7){
                    board[r][f] = new class Rook(WHITE);
                } else if(f == 3){
                    board[r][f] = new class Queen(WHITE);
                } else if(f == 4){
                    board[r][f] = new class King(WHITE);
                }
            } else {
                board[r][f] = nullptr;
            }
        }
    }
}

void ChessBoard::erasePieces(){
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++){
            if (board[r][f] != nullptr){
                Piece* tmp = board[r][f];
                delete tmp;
                board[r][f] = nullptr;
            }
        }
    }
}

ChessBoard::ChessBoard(){
    placePieces();
    turn = WHITE; //white moves first
    cout << "A new chess game is started!" <<endl;
}

void ChessBoard::printFrame(){
    cout << "  +---+---+---+---+---+---+---+---+"<< '\n';
}

void ChessBoard::printRank(int r){
    cout << 8-r << " ";
  for (int i=0; i<8; i++) {
    cout << ((i!=0) ? ':' : '|' ) << " ";
    //cout << "o" << " ";
    cout << ( (board[r][i]==nullptr) ? ' ' : board[r][i]->getSign()) << " ";
  }
  cout << "|" << '\n';
}

void ChessBoard::printBoard(){
    cout << "    ";
  for (int r=0; r<8; r++) {
    cout << (char) ('A'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<8; r++) {
    printFrame();
    printRank(r);
  }
  printFrame();
}

int ChessBoard::checksquare(char const* source, char const* destination){
    //position too long
    if (source[2]!='\0' || destination[2]!='\0'){ return 1; }
    
    int s_file = source[0] - 'A', s_rank = '8'- source[1];
    int d_file = destination[0] - 'A', d_rank = '8' - destination[1];

    //source square out of index
    if (s_rank < 0 || s_rank > 7 || s_file < 0 || s_file > 7){ return 2; }

    //destination square out of index
    if (d_rank < 0 || d_rank > 7 || d_file < 0 || d_file > 7){ return 3; }

    if (board[s_rank][s_file] == nullptr) {
        return 4; //no piece at source square
    } else {
        Colour colour = board[s_rank][s_file]->colour;
        if (colour!=turn){ return 5; } // not this player's turn
    }

    Type type = board[s_rank][s_file]->getType();
    if (type != Knight) {
        //cannot jump over other pieces
        if (!enrouteClear(s_rank,s_file,d_rank,d_file,type)){ return 6; }
    }

    return 0;
}

void ChessBoard::submitMove(char const* source, char const* destination){
    int s_file = source[0] - 'A', s_rank = '8'- source[1];
    int d_file = destination[0] - 'A', d_rank = '8' - destination[1];
    int error = checksquare(source, destination);
    if (error != 0) { //simple errors
        switch(error) {
            case 1: cout << "Invalid square coordinates: too long" << endl; break;
            case 2: cout << "Invalid source square coordinate!" << endl; break;
            case 3: cout << "Invalid destination square coordinate!" << endl; break;
            case 4: cout << "There is no piece at position " << source << "!" << endl; break;
            case 5: cout << "It is not " << board[s_rank][s_file]->colour << "’s turn to move!" << endl; break;
            case 6: cout << board[s_rank][s_file]->getType() << " cannot leap over other pieces!" << endl;
        }
    }else { //more complicated errors
        Type type = board[s_rank][s_file]->getType();
        Colour colour = board[s_rank][s_file]->colour;
        cout << colour <<"'s "<< type;
        if (board[d_rank][d_file] == nullptr) { //regular move
            if (board[s_rank][s_file]->moveValid(s_rank,s_file,d_rank,d_file)){
                cout << " moves from " << source << " to " << destination << endl;
                if (colour == WHITE){ wCount++; } else { bCount++; }
                if (turn == WHITE) { turn = BLACK; } else { turn = WHITE; }
                board[d_rank][d_file] = board[s_rank][s_file];
                board[s_rank][s_file] = nullptr;
            } else {
                cout << " cannot move to " << destination << "!" << endl;
            }
        } else { //capture move
            Colour d_colour = board[d_rank][d_file]->colour;
            Type d_type = board[d_rank][d_file]->getType();
            if (d_colour == colour) {
                cout << " cannot capture it's own piece!" << endl;
            } else {
                if (board[s_rank][s_file]->captureValid(s_rank,s_file,d_rank,d_file)){
                    cout << " moves from " << source << " to " << destination;
                    cout << " taking " << d_colour << "’s " << d_type << endl;
                    if (colour == WHITE){ wCount++; }else{ bCount++; }
                    if (turn == WHITE) { turn = BLACK; } else { turn = WHITE; }
                    Piece* tmp = board[d_rank][d_file];
                    delete tmp; //delete the captured piece
                    board[d_rank][d_file] = board[s_rank][s_file];
                    board[s_rank][s_file] = nullptr;
                } else {
                    cout << " cannot move to " << destination << " and capture ";
                    cout << d_colour << "’s " << d_type << endl;
                }
            }
        }
    }
}


bool ChessBoard::enrouteClear(int s_rank, int s_file, int d_rank, int d_file, Type t){
    return true;
}

void ChessBoard::resetBoard(){
    erasePieces();
    placePieces();
    turn = WHITE; //white moves first
    wCount = 0; //white move count
    bCount = 0; //black move count
    cout << "A new chess game is started!" <<endl;
}

ChessBoard::~ChessBoard(){
    erasePieces();
}