#include "player.h"

bool Player::getHasCheck() const
{
    return hasCheck;
}

void Player::setHasCheck(bool value)
{
    hasCheck = value;
}

Player::Player(char color)
{
    this -> color = color;
    castle.king_l = true;
    castle.king_r = true;
    hasCheck = false;
}

char Player::getColor() const
{
    return color;
}

void Player::addToCaptured(char piece)
{
    capturedPieces.push_back(piece);
}

Player::Position Player::getKingsPosition()
{
    return king;
}

void Player::setKingPosition(int row, int column)
{
    king.row = row;
    king.column = column;
}

Player::Castle Player::getCastleParam()
{
    return castle;
}

void Player::setCastleLefttoFalse()
{
    castle.king_l = false;
}

void Player::setCastleRighttoFalse()
{
    castle.king_r = false;
}

bool Player::isCastleFalse()
{
    return ((castle.king_l == castle.king_r) && (castle.king_r==false));
}


