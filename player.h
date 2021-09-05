#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

class Player
{
    char color;
    std::vector< char > capturedPieces;
    struct Position {
        int row;int column;
    } king;
    // struktura w której zapisywane jest czy pionki się już poruszyły i czy roszada jest możliwa
    // true dla kingWhite_l oznacza, że ani biały król ani lewa wieża nie wykonały jeszcze ruchu w grze
    struct Castle{
        bool king_l;
        bool king_r;
    } castle;

    bool hasCheck;
public:
    Player(char color);
    char getColor() const;
    void addToCaptured(char piece);
    Position getKingsPosition();
    void setKingPosition(int row, int column);
    Castle getCastleParam();
    void setCastleLefttoFalse();
    void setCastleRighttoFalse();
    bool isCastleFalse();
    bool getHasCheck() const;
    void setHasCheck(bool value);
};

#endif // PLAYER_H
