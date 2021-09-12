#include "board.h"
#include <iostream>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include <bits/stdc++.h>
#include "controller.h"
using namespace std;

Board::Board(QWidget *parent) : QWidget(parent)
{
    newGame();
    QGridLayout *gridlayout = new QGridLayout();
    gridlayout->setSpacing(0);
        this->setLayout(gridlayout);
    for (int i=0; i<8; i++) {
          for(int j=0; j<8;j++) {
              BoardPiece *bp = new BoardPiece(i,j);
              boarpieces[i][j] = bp;
              gridlayout->addWidget(bp,i,j);
              connect(bp,SIGNAL(clicked(int,int)),this,SLOT(validateClick(int,int)));
              if((i+j)%2==0){
                  bp ->setColor(true);
              }else{
                  bp->setColor(false);
              }
          }
    }
}
void Board::setSelectedBoardPiece(BoardPiece *value)
{
    selectedBoardPiece = value;
}

void Board::addPieces()
{
    BoardPiece *bp;
    for (int i=0; i<8; i++) {

        for(int j=0; j<8;j++) {
             bp = boarpieces[i][j];
            char piece = getPieceFromPosition(i,j);
            if(islower(piece)){
                bp ->setPixmap(QPixmap(":/new/prefix1/"+ QString(getPieceFromPosition(i,j)) +".png"));
            }else{
                bp ->setPixmap(QPixmap(":/new/prefix1/"+ QString(tolower(getPieceFromPosition(i,j))) +"w.png"));
            }
        }
    }
}

void Board::clearAllAfterMove()
{
    BoardPiece *bp;

    for (int i=0; i<8; i++) {
        for(int j=0; j<8;j++) {
            bp = boarpieces[i][j];
            bp ->setisSelected(false);
            bp->setisMovePossThere(false);
            bp->unhighlight();
        }
    }
}

BoardPiece *Board::getSelectedBoardPiece() const
{
    return selectedBoardPiece;
}

void Board::validateClick(int row, int column)
{
    /**
         * czy to pole jest już zaznaczone? (isselected)
         */
     if(boarpieces[row][column] -> getisSelected()){
         /**
              * tak - odznaczamy
              */
         boarpieces[row][column] -> unhighlight();
         boarpieces[row][column] -> setisSelected(false);
         setSelectedBoardPiece(nullptr);
         std::vector<int> &vc = *checkAvailableMoves(row,column);
         for (size_t i = 0; i < vc.size(); i++) {
             if(i%2!=0){
                 boarpieces[vc[i-1]][vc[i]] -> unhighlight();
             }
         }
         /**
              * nie - czy to pole jest jednym z możliwych ruchów?
              */
     }else if(boarpieces[row][column]->getisMovePossThere()){
         /**
          *  tak - wykonaj ruch
          */
         movePiece(getSelectedBoardPiece()->getRow(),getSelectedBoardPiece()->getColumn(),row,column);
         updateGame();
         /**
          *  nie - czy to pole zawiera pionek gracza którego jest kolej?
          */
     }else if(checkPieceColor(getPieceFromPosition(row,column)) == getWhosTurn()){

         /*
          *  czy jest już zaznaczone inne pole?
          *  tak - wyczyść zaznaczenie
         */
         if(selectedBoardPiece != nullptr){
            clearAllAfterMove();
         }
         /*
          * nie - zaznacz pole i pokaż możliwe ruchy
          */
         boarpieces[row][column] -> highlight();
         boarpieces[row][column] -> setisSelected(true);
         setSelectedBoardPiece(boarpieces[row][column]);
         std::vector<int> &vc = *checkAvailableMoves(row,column);
         for (size_t i = 0; i < vc.size(); i++) {
             if(i%2!=0){
                 boarpieces[vc[i-1]][vc[i]] -> highlight();
                 boarpieces[vc[i-1]][vc[i]] -> setisMovePossThere(true);
             }
         }
     }
}

void Board::validateButtonClick()
{
    clearAllAfterMove();
    newGame();
    addPieces();
    displayTurn();
    clearCaptured();
}

