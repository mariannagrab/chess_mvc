#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
/**
 *  klasa Player
 *  Reprezentuje gracza w tym kolor jego pionków, ustawienie króla, zbite pionki
 *  przechowuje informację o szachu.
 */
class Player
{
private:

    char color; /**< Kolor ustawiany w konstruktorze na białe lub czarne */
    bool hasCheck; /**< Czy dany gracz szachuje w tym ruchu króla przeciwnika */
    std::vector< char > *capturedPieces = nullptr; /**< Wskaźnik do wektora ze zbitymi przez gracza pionkami */
    /**
         * struktura Position.
         * zapisuje teraźniejszą pozycję króla danego gracza w instancji king.
         */
    struct Position {
        int row;    /**< wartość struktury Position - numer wiersza na planszy */
        int column; /**< wartość struktury Position - numer kolumny na planszy */
    } king;
    /**
         * struktura Castle.
         * struktura w której zapisywane jest czy pionki się poruszyły i czy roszada jest możliwa
         * true dla kingWhite_l oznacza, że ani biały król ani lewa wieża nie wykonały jeszcze ruchu w grze
         */

    struct Castle{
        bool king_l; /**< Czy lewa roszada jest możliwa dla tego gracza */
        bool king_r; /**< Czy prawa roszada jest możliwa dla tego gracza */
    } castle;


public:
    /**
           * Konstruktor.
           * Tworzy instancję gracza przypisuje mu dany kolor i ustawia pola na defaultowe.
           * @param kolor pionków gracza
           */
    Player(char color);
    /**
           * Getter i Setter pola bool hasCheck.
           */
    bool getHasCheck() const;
    void setHasCheck(bool value);
    /**
         * Getter pola capturedPieces
         * @return wektor zbitych przez gracza pionków
         */
    std::vector<char>* getCapturedPieces() const;
    /**
         * funckja dodaje zbity pionek na końcu wektora capturedPieces (pole klasy)
         * @param zbity pionek
         */
    void addToCaptured(char piece);
    /**
         * Getter pola king - funkcja zwraca strukturę z teraźniejszą pozycją króla gracza
         * @return struktura Position ze współrzędnymi króla
         */
    Position getKingsPosition();
    /**
         * Setter pola king - funkcja zmienia parametry struktury Position king
         * @param wiersz i kolumna (indeksowane od 0 do 7)
         */
    void setKingPosition(int row, int column);
    /**
         * Getter pola castle - funkcja zwraca strukturę zawierającą informację o roszadzie
         * @return struktura Castle
         */
    Castle getCastleParam();
    /**
         * Setter pola king - funkcje ustawiające parametry struktury Castle
         * setCastleLefttoFalse - lewa roszada nie będzie już możliwa
         * setCastleRighttoFalse - prawa roszada nie będzie już możliwa
         * wywoływane po ruchu króla lub zbiciu bądż ruchu wieży
         */
    void setCastleLefttoFalse();
    void setCastleRighttoFalse();
    /**
         * funkcja sprawdzająca możliwość roszady z dwóch stron
         * @return false gdy roszada jest już niemożliwa z lewej i z prawej
         */
    bool isCastleFalse();

};

#endif // PLAYER_H
