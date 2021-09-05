#ifndef UI_H
#define UI_H
#include <iostream>
#include "chessgame.h"
using namespace std;
#define WHITE_SQUARE 0xDB
#define BLACK_SQUARE 0xFF
#define EMPTY_SQUARE 0x20
void printMenu( void );
void printTurn(ChessGame& game);
void printBoard(ChessGame& game);
void printLine( int iLine, int iColor1, int iColor2,ChessGame& game );
void quitGame();
string sss();
#endif // UI_H
