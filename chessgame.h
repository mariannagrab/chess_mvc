#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <iostream>
#include <map>
#include "player.h"



using namespace std;

class ChessGame
{
private:
    const char WHITE_COLOR = 'w';
    const char BLACK_COLOR = 'b';
    const char WHITE_KING = 'K';
    const char BLACK_KING = 'k';
    const char EMPTY = 0x20;

    Player *white,*black;
    // dla którego gracza jest szach
    char isCheck = EMPTY;
    char whosTurn;
    const char first_board[8][8] =
    {
        { 'r',  'n',  'b',  'q',  'k',  'b',  'n',  'r' },
        { 'p',  'p',  'p',  'p',  'p',  'p',  'p',  'p' },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { 'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P' },
        { 'R',  'N',  'B',  'Q',  'K',  'B',  'N',  'R' },
    };
    char board[8][8];
    struct Move {
        char figure; int moveFrom_row; int moveFrom_column; int moveTo_row; int moveTo_column; bool is_enPassant;
    } LastMove, ThisMove;



public:
   ChessGame();
   void initializeBoard();
   char getWhosTurn();
   void changeTurn();
   char checkPieceAtPosition(int row,int column);
   char checkPieceColor(char piece);
    void setChecktoFalse();
   bool isMoveValid(int whatPiece_row,int whatPiece_column, int putWhere_row, int putWhere_column);
    Move checkLastMove();
   void movePiece(int whatPiece_row,int whatPiece_column, int putWhere_row, int putWhere_column);
   void addToCaptured(char piece);
   void setWhosTurn(const char &value);
   // zapisuje ostatni ruch i ustawia parametr is_enPassant possible na false
   void saveLastMove(char figure,int whatPiece_row,int whatPiece_column, int putWhere_row, int putWhere_column);
   char checkCheck();
   bool checkCheck(char color, int whatPiece_row, int whatPiece_column);
   bool checkMate(char piece);
   // sprawdza czy ruch jest podwójnym pójßciem do przodu pionka
   bool doublePawnMove(int whatPiece_row,int whatPiece_column, int putWhere_row, int putWhere_column);
   // sprawdza czy ruch to bicie en passant
 //  bool isEPMove(char pieceColor, int whatPiece_row, int putWhere_row);
   // nowa pozycja króla
   void saveNewKingsPosition(char piece,int row, int column);
   // czy ruch króla jest możliwy?
   bool isKingsMoveValid(char color, int putWhere_row, int putWhere_column);
   // zapisuje ruch wieży, by zapobiec roszadzie
   void saveCastlePossib(int whatPiece_row,int whatPiece_column);
   bool isCastleMove(char pieceColor, int whatPiece_row,int whatPiece_column, int putWhere_row, int putWhere_column);
   void removePiece(int row,int column);
    void addPiece(char piece, int row, int column);
    void resetMove(Move move);
    vector<int>* returnAvailableFields(int whatPiece_row,int whatPiece_column);
};

#endif // CHESSGAME_H
