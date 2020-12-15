#ifndef PIECES_H
#define PIECES_H
#include <iostream>

using namespace std;

//the pieces are only responsible for checking 
//whether the destination square follows moving rule
//It is the ChessBoard's responsibility to check 
//the validity of squares and whether other pieces are in the way

enum Colour {
    WHITE,
    BLACK
};

ostream& operator<<(ostream& o, Colour c);

enum Type {
    None,
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

ostream& operator<<(ostream& o, Type t);

class Piece {
    char sign;
    static const Type type = None;
public:
    Colour colour;
    Piece(Colour colour);
    virtual char getSign();
    virtual Type getType();
    virtual bool moveValid(int s_rank, int s_file, int d_rank, int d_file);
    virtual bool captureValid(int s_rank, int s_file, int d_rank, int d_file);
    virtual ~Piece();
};

class Pawn : public Piece {
    char sign;//P for White p for Black
    static const Type type = Type::Pawn;
    int count; //move count
public:
    Pawn(Colour colour);
    char getSign() override;
    Type getType() override;
    bool moveValid(int s_rank, int s_file, int d_rank, int d_file) override;
    bool captureValid(int s_rank, int s_file, int d_rank, int d_file) override;
    ~Pawn() override;
};

class Knight : public Piece {
    char sign;//N for White n for Black
    static const Type type = Type::Knight;
public:
    Knight(Colour colour);
    char getSign() override;
    Type getType() override;
    bool moveValid(int s_rank, int s_file, int d_rank, int d_file) override;
    bool captureValid(int s_rank, int s_file, int d_rank, int d_file) override;
    ~Knight() override;
};

class Bishop : public Piece {
    char sign;//B for White b for Black
    static const Type type = Type::Bishop;
public:
    Bishop(Colour colour);
    char getSign() override;
    Type getType() override;
    bool moveValid(int s_rank, int s_file, int d_rank, int d_file) override;
    bool captureValid(int s_rank, int s_file, int d_rank, int d_file) override;
    ~Bishop() override;
};

class Rook : public Piece {
    char sign;//R for White r for Black
    static const Type type = Type::Rook;
public:
    Rook(Colour colour);
    char getSign() override;
    Type getType() override;
    bool moveValid(int s_rank, int s_file, int d_rank, int d_file) override;
    bool captureValid(int s_rank, int s_file, int d_rank, int d_file) override;
    ~Rook() override;
};

class Queen : public Piece {
    char sign;//Q for White q for Black
    static const Type type = Type::Queen;
public:
    Queen(Colour colour);
    char getSign() override;
    Type getType() override;
    bool moveValid(int s_rank, int s_file, int d_rank, int d_file) override;
    bool captureValid(int s_rank, int s_file, int d_rank, int d_file) override;
    ~Queen() override;
};

class King : public Piece {
    char sign;//K for White k for Black
    static const Type type = Type::King;
public:
    King(Colour colour);
    char getSign() override;
    Type getType() override;
    bool moveValid(int s_rank, int s_file, int d_rank, int d_file) override;
    bool captureValid(int s_rank, int s_file, int d_rank, int d_file) override;
    ~King() override;
};



#endif