#include "controller.h"

#include <QMessageBox>
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

   game->saveThisMove(getPieceFromPosition(whatPiece_row, whatPiece_column),whatPiece_row, whatPiece_column, putWhere_row, putWhere_column);
   game->movePiece();
}
char getWhosTurn(){
    return game -> getWhosTurn();
}
char checkPieceColor(char piece)
{
    return game -> getPieceColor<char>(piece);
}

void displayTurn()
{
    if(game->getWhosTurn()==game->WHITE_COLOR){
        w->setTurn("Teraz kolej gracza białego ");
    }else{
        w->setTurn("Teraz kolej gracza czarnego");
    }
}

void displayCheckInfo()
{
    if(game->getWhite()->getHasCheck()){
        w->setCheck("Szach dla gracza białego!");
    }else if(game->getBlack()->getHasCheck()){
       w->setCheck("Szach dla gracza czarnego!");
    }else{
        w->setCheck("");
    }
}
void displayEndOfGame(){
    QMessageBox msgbox;

    msgbox.setText("Szach mat! Koniec gry!");
    QPushButton *winButton = msgbox.addButton("Nowa gra", QMessageBox::ActionRole);

    msgbox.setDefaultButton(winButton);
    msgbox.setWindowTitle("Szachy");
    if(game->getWhosCheckMate()==game->BLACK_KING){
        msgbox.setInformativeText("Grę wygrywa gracz biały!");
    }else{
        msgbox.setInformativeText("Grę wygrywa gracz czarny!");

    }
    msgbox.setStyleSheet("QLabel{min-width: 350px; min-height: 100px; font-size: 18px;}");
    msgbox.exec();
    if (msgbox.clickedButton() == winButton) {
        w->close();
        start();
    };
}

bool isCheckMate()
{
    return !(game->getWhosCheckMate()==game->EMPTY);
}


char getCapturedPiece(char color)
{
    if(color==game->BLACK_COLOR){
        if(getCountCapturedPiece(game->BLACK_COLOR)!=0)
            return game -> getBlack()->getCapturedPieces()->back();
    }else{
        if(getCountCapturedPiece(game->WHITE_COLOR)!=0)
            return game -> getWhite()->getCapturedPieces()->back();
    }
    return 0x20;
}

void displayCapturedPieces()
{
    if(getWhosTurn()==game->WHITE_COLOR){
        w->addToCaptured(game->BLACK_COLOR,getCapturedPiece(game->BLACK_COLOR),getCountCapturedPiece(game->BLACK_COLOR));
    }else{
        w->addToCaptured(game->WHITE_COLOR,getCapturedPiece(game->WHITE_COLOR),getCountCapturedPiece(game->WHITE_COLOR));
    }
}

int getCountCapturedPiece(char color)
{
    if(color==game->BLACK_COLOR){

        return game -> getBlack()->getCapturedPieces()->size();

    }else{
            return game -> getWhite()->getCapturedPieces()->size();
    }
    return 0;
}

void clearCaptured()
{
    w->clearCaptured();
}

void updateGame()
{
    displayCapturedPieces();
    displayCheckInfo();
    w->addPieces();
    w-> clearBoard();
    displayTurn();
    if(isCheckMate()){
        displayEndOfGame();
    };
}
