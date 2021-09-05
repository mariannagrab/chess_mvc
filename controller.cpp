#include "controller.h"
ChessGame* game = NULL;
MainWindow *w = NULL;

void start(){
    w = new MainWindow();
    w->show();
}
void newGame(){
    if(game != NULL){
        delete game;
    };
    game = new ChessGame();
    game -> initializeBoard();
}

void quitGame(){
    if(game != NULL){
        delete game;
    }
}

char getPieceFromPosition(int row, int column)
{
    return game -> checkPieceAtPosition(row,column);
}


vector<int>* checkAvailableMoves(int row, int column)
{
    return game ->returnAvailableFields(row, column);
}
void movePiece(int whatPiece_row,int whatPiece_column, int putWhere_row, int putWhere_column){
    game->movePiece(whatPiece_row,whatPiece_column, putWhere_row, putWhere_column);
}
char getWhosTurn(){
    return game -> getWhosTurn();
}
char checkPieceColor(char piece)
{
    return game -> checkPieceColor(piece);
}

void displayTurn()
{
    if(game->getWhosTurn()=='w'){
        w->setTurn("Teraz kolej gracza białego ");
    }else{
        w->setTurn("Teraz kolej gracza czarnego");

    }
}
