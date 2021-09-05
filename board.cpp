#include "board.h"
#include "controller.h"
#include <iostream>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include <bits/stdc++.h>
using namespace std;
BoardPiece *Board::getSelectedBoardPiece() const
{
    return selectedBoardPiece;
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

Board::Board(QWidget *parent) : QWidget(parent)
{
    newGame();
    // setFixedSize(64*8,64*8);
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
    addPieces();
}

void Board::validateClick(int row, int column)
{
    // czy to pole jest już zaznaczone? (isselected)
     if(boarpieces[row][column] -> getisSelected()){
         // tak - odznaczamy
         boarpieces[row][column] -> unhighlight();
         boarpieces[row][column] -> setisSelected(false);
         setSelectedBoardPiece(nullptr);
         std::vector<int> &vc = *checkAvailableMoves(row,column);
         for (size_t i = 0; i < vc.size(); i++) {
             if(i%2!=0){
                 boarpieces[vc[i-1]][vc[i]] -> unhighlight();
             }
         }
         // nie
         //czy to pole jest jednym z możliwych ruchów?
     }else if(boarpieces[row][column]->getisMovePossThere()){
         // tak - wykonaj ruch
         movePiece(getSelectedBoardPiece()->getRow(),getSelectedBoardPiece()->getColumn(),row,column);
         addPieces();
         clearAllAfterMove();
         displayTurn();
         // nie
         // czy to pole zawiera pionek gracza którego jest kolej?
     }else if(checkPieceColor(getPieceFromPosition(row,column)) == getWhosTurn()){

         // czy jest już zaznaczone inne pole?
         // tak - wyczyść zaznaczenie
         if(selectedBoardPiece != nullptr){
            clearAllAfterMove();
         }
         // nie - zaznacz pole i pokaż możliwe ruchy
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

}
void BoardPiece::mousePressEvent(QMouseEvent *event){
        emit clicked(row, column);
}




void BoardPiece::setisSelected(bool value)
{
    isSelected = value;
}

QString BoardPiece::getColor()
{
    return color;
}

bool BoardPiece::getisMovePossThere() const
{
    return isMovePossThere;
}

void BoardPiece::setisMovePossThere(bool value)
{
    isMovePossThere = value;
}

int BoardPiece::getRow() const
{
    return row;
}

int BoardPiece::getColumn() const
{
    return column;
}

BoardPiece::BoardPiece(int row, int column,  QWidget *parent) : QLabel(parent)
{
    setFixedSize(siz);
    this->row = row;
    this->column = column;
        isSelected = false;
        // ustawienie pionków po ßrodku
        setAlignment(Qt::AlignCenter);
        setisMovePossThere(false);

}

void BoardPiece::setColor(bool value)
{
    if (value == false){
        color = "darkgrey";
        this -> setStyleSheet("background:darkgrey;");
    }else{
        color = "lightgrey";
        this -> setStyleSheet("background:lightgrey;");
    }
    // color = value;
}

void BoardPiece::unhighlight()
{

  //  QString qstr = QString::fromStdString("QLabel {background:" + getColor());
    this -> setStyleSheet("QLabel {background:" + getColor() + ";}");

}
void BoardPiece::highlight()
{

   this -> setStyleSheet("QLabel {background:#ff0000;}");

}

bool BoardPiece::getisSelected()
{
    return isSelected;
}
