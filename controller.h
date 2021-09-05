#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "chessgame.h"
#include "mainwindow.h"

//ChessGame* game;
void start();
void newGame();
char getPieceFromPosition(int row,int column);
void quitGame();
vector<int>*  checkAvailableMoves(int row, int column);
void movePiece(int whatPiece_row,int whatPiece_column, int putWhere_row, int putWhere_column);
char getWhosTurn();
char checkPieceColor(char piece);
void displayTurn();



#endif // CONTROLLER_H
