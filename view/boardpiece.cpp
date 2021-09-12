#include "boardpiece.h"

BoardPiece::BoardPiece(int row, int column,  QWidget *parent) : QLabel(parent)
{
    setFixedSize(siz);
    this->row = row;
    this->column = column;
    isSelected = false;
    // ustawienie pionków po środku
    setAlignment(Qt::AlignCenter);
    setisMovePossThere(false);
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

void BoardPiece::setColor(bool value)
{
    if (value == false){
        color = "darkgrey";
        this -> setStyleSheet("background:darkgrey;");
    }else{
        color = "lightgrey";
        this -> setStyleSheet("background:lightgrey;");
    }
}

void BoardPiece::unhighlight()
{
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



