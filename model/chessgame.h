#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <iostream>
#include <map>
#include "player.h"
/**
 *  klasa ChessGame
 *  kieruje logiką gry
 *  tworzy instancje graczy, przechowuje tablicę [2D] z ustawieniem pionków zamodelowanych jako znaki char,
 *  sprawdza poprawność ruchów pionków na tablicy
 *  zmienia kolej gracza, wykonuje ruch zmieniając pozycję pionka w tablicy,
 *  sprawdza czy jest szach lub szach mat
 */

using namespace std;

class ChessGame
{
public:
    const char WHITE_COLOR = 'w'; /**< stała biały kolor */
    const char BLACK_COLOR = 'b'; /**< stała czarny kolor */
    const char WHITE_KING = 'K'; /**< stała pionek biały król */
    const char BLACK_KING = 'k'; /**< stała pionek czarny król */
    const char EMPTY = 0x20; /**< stała brak pionka na planszy */
    /**
         * template ustalający kolor pionka na planszy na podstawie
         * albo współrzędnych tablicy:
         * rzędu i kolumny zdefiniowanych jako int od 0 do 7
         * albo pionka:
         * char wilkiej lub małej litery
         * @return kolor pionka na planszy (WHITE_COLOR,BLACK_COLOR) lub brak pionka (EMPTY)
         */
    template <class T>
    char getPieceColor (T x, T y=0) {
        if(std::is_same<T,int>::value){
            x = checkPieceAtPosition(x,y);
        };
        if (isupper(x)){
            return WHITE_COLOR;
        }else if(islower(x)){
            return BLACK_COLOR;
        }
        return EMPTY;
    }

private:
    Player *white,*black; /**< wskaźniki do obiektów graczy, białego i czarnego */
    char whosTurn; /**< kolor gracza dla którego jest teraz kolej ruchu (WHITE_COLOR,BLACK_COLOR)*/
    char whosCheckMate; /**< kolor gracza dla którego jest szach mat (WHITE_COLOR,BLACK_COLOR), gdy nie ma szach mat to whosCheckMate = EMPTY */
    /**
         * stała tablica z początkowym ustawieniem pionków na planszy
         * czarne pionki ustawione są w 0 i 1 rzędzie (małe litery)
         * białe pionki ustawione są w 6 i 7 rzędzie (wielkie litery)
         * podczas tworzenia nowej instancji ChessGame ta tablica first_board jest kopiowana do tymczasowej tablicy board
         * na której odbywa się gra
         */
    const char first_board[8][8] =
    {
        { 'r',  'n',  'b',  'q',  'k',  'b',  'n',  'r' },
        { 'p',  'p',  'p',  'p',  'p',  'p',  'p',  'p' },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { 'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P' },
        { 'R',  'N',  'B',  'Q',  'K',  'B',  'N',  'R' },
    };
    /**
         * podczas tworzenia nowej instancji klasy ChessGame tablica first_board[8][8] jest kopiowana do tej tablicy - board[8][8]
         * na tej tablicy przesuwane są pionki
         */
    char board[8][8];
    /**
         * struktura przechowująca informacje o ruchu ba tablicy
         * LastMove służy do zapisania ostatniego ruchu
         * ThisMove jest walidowany w trakcie gry i gdy jest poprawny przepisywany jest do LastMove
         */
    struct Move {
        char figure; /**< pionek który się poruszy/poruszył */
        int moveFrom_row; /**< rząd skąd */
        int moveFrom_column; /**< kolumna skąd */
        int moveTo_row; /**< rząd gdzie (na jakie pole) */
        int moveTo_column;/**< kolumna gdzie (na jakie pole) */
    } LastMove, ThisMove;

public:
    /**
           * Konstruktor.
           * Tworzy instancję ChessGame, dwóch graczy Player, ustawia kolej gracza białego, czyści informację o ruchach i szach mat
           * ustawia początkowe pozycje króli
           * wywoływany jest w kontrolerze
           */
    ChessGame();
    /**
           * funkcja tworząca początkowe ustawienie pionków na planszy
           */
    void initializeBoard();
    /**
           * getter pola whosTurn
           * @return kolor gracza którego jest teraz kolej
           */
    char getWhosTurn();
    /**
           * setter pola whosTurn
           * ustawia pole na przeciwne do teraźniejszego, jeżeli kolej była białego gracza to teraz będzie czarnego
           */
    void changeTurn();
    /**
           * funkcja sprawdzająca tablicę board[8][8] jaki pionek znajduje sie na danej pozycji
           * @param wiersz, kolumna od 0 do 8 (indexowanie od lewej do prawej od góry do dołu)
           * @return pionek znajdujący się na tym polu (char)
           */
    char checkPieceAtPosition(int row,int column);
    /**
           * funkcja isMoveValid po podaniu struktury move sprawdza czy ruch jest możliwy dla danego pionka (w zależności od figury) na dane pole
           * sprawdza również czy na docelowym polu nie ma pionka w tym samym kolorze
           * funkcja ta wykorzystywana jest przy podświetlaniu pól aktywnych na planszy jak i pprzy sprawdzeniu szacha i szach mat
           * @param move zawiera informację o pionku i o potencjalnym ruchu z jakiego miajsca na jakie (rząd, kolumna)
           * @return zwraca fałsz gdy ruch nie jest możliwy, true gdy jest możliwy (nie narusza zasad gry w sachy)
           */
    bool isMoveValid(Move move);
    /**
           * funkcja pomocnicza przy ustalaniu czy ruch po skosie jest możliwy
           * wywoływana w isMoveValid dla królowej i gońca
           * @param obiekt Move: pionek, wiersz, kolumna, wiersz docelowy, kolumna docelowa
           * @return czy ruch jest możliwy dla danego ruchu move
           */
    bool checkDiagonalMove(Move move);
    /**
           * funkcja movePiece wykonująca ruch na tablicy board na podstawie informacji o ruchu ThisMove
           * usuwa pionek i stawia go w nowy miejscu
           * wywołuje funkcje aktualizujące parametry gry
           */
    void movePiece();
    /**
           * funkcja pomocnicza wykonująca ruch roszadowy dla ThisMove
           */
    void doCastleMove();
    /**
           * funkcja sprawdzająca czy w obecnym ustawieniu pionków na tablicy board jest możliwość zbicia króla jakiegokolwiek koloru
           * czyli czy jest szach
           * @return kolor gracza dla którego jest szach, gdy nie ma szacha funkcja zwraca EMPTY
           */
    char checkCheck();
    /**
           * nadpisanie metody checkCheck: funkcja sprawdzająca czy w nowym potencjalnym ustawieniu króla będzie szach
           * wywoływana przy sprawdzaniu szach mat
           * @param czy jest szach dla króla w ustawieniu o kolorze color ustawionego na polu o współrzędnych whatPiece_row, whatPiece_column
           * @return fałsz gdy nie ma szacha
           */
    bool checkCheck(char color, int whatPiece_row, int whatPiece_column);
    /**
           * setter funkcja po sprawdzeniu czy jest szach na planszy ustawia hasCheck na false dla obu graczy
           */

    void setChecktoFalse();
    /**
           * funkcja sprawdzająca czy dla obecnego ustawienia pionków jest szach mat
           * @param pionek króla który jest szachowany
           * @return true gdy jest szach mat
           */
    bool checkMate(char piece);
    /**
           * funkcja zwracająca dostępne pola do poruszenia w postaci wektora dla pionka położonego (whatPiece_row,whatPiece_column)
           * wywoływana w kontrolerze
           * @param wiersz, kolumna pionka dla którego sprawdzane są możliwości ruchu
           * @return wskaźnik do wektora dostępnych pól <int wiersz1, int kolumna1,int wiersz2, int kolumna2 >
           */
    vector<int>* returnAvailableFields(int whatPiece_row,int whatPiece_column);

    /**
           * funkcja dodająca zbity pionek do wektora wzbitych pionków gracza
           * @param zbity pionek (char)
           */
    void addToCaptured(char piece);
    /**
           * setter obiektu ThisMove ustawia obecny/potencjalny (jeszcze nie dokonany) ruch
           * @param parametry Move: pionek, wiersz, kolumna, wiersz docelowy, kolumna docelowa
           */
    void saveThisMove(char _figure, int _whatPiece_row, int _whatPiece_column, int _putWhere_row, int _putWhere_column);
    /**
           * getter obiektu LastMove zwraca ostatni ruch jaki był wykonany
           * @return LastMove
           */
    Move getLastMove();
    /**
           * setter obiektu LastMove ustawia ostatni ruch jaki był wykonany
           * @param parametry Move: pionek, wiersz, kolumna, wiersz docelowy, kolumna docelowa
           */
    void saveLastMove(char _figure, int _whatPiece_row, int _whatPiece_column, int _putWhere_row, int _putWhere_column);
    /**
           * funkcja pomocnicza przy ustalaniu czy ruch pionka o dwa pola do przodu jest możliwy
           * wywoływana w isMoveValid
           * @param obiekt Move: pionek, wiersz, kolumna, wiersz docelowy, kolumna docelowa
           * @return czy ruch jest możliwy dla danego ruchu move
           */
    bool doublePawnMove(Move move);
    /**
           * funkcja zapisująca nową pozycję króla
           * wywoływana po wykonaniu ruchu w movePiece
           * @param wiersz docelowy, kolumna docelowa króla
           */
    void saveNewKingsPosition(char piece,int row, int column);
    /**
           * funkcja spprawdzająca czy potencjalny ruch króla jest możliwy
           * wywoływana przy sprawdzeniu czy ruch jest możliwy oraz przy sprawdzeniu szach mat
           * @param kolor króla, wiersz docelowy, kolumna docelowa króla
           * @return zwraca true gdy ruch króla jest możliwy
           */
    bool isKingsMoveValid(char color, int putWhere_row, int putWhere_column);
    /**
           * funkcja zapisująca ruch wiezy i ustawiająca możliwość orszady na false
           * wywoływana po wykonaniu ruchu przez wieżę w movePiece
           * @param parametry poruszonej wieży wiersz i kolumna
           */
    void saveCastlePossib(int whatPiece_row,int whatPiece_column);
    /**
           * funkcja sprawdzająca czy roszada na dane pole jest możliwa
           * wywoływana w sprawdzeniu dostępności pól (dla króla) oraz przy wykonywaniu ruchu
           * @param kolor króla, parametry poruszonejgo króla docelowy wiersz i docelowa kolumna
           */
    bool isCastleMove(char pieceColor,int putWhere_row, int putWhere_column);
    /**
           * funkcja usuwająca pionek z tablicy board (zamieniająca wartość na EMPTY)
           * @param wiersz kolumna
           */
    void removePiece(int row,int column);
    /**
           * funkcja dodająca pionek do tablicy board
           * @param pionek, wiersz, kolumna
           */
    void addPiece(char piece, int row, int column);
    /**
           * funkcja resetująca wartości struktury Move - na początku każdej nowej gry
           * @param move
           */
    void resetMove(Move move);
    /**
           * getter i setter pola whosCheckMate
           */
    char getWhosCheckMate() const;
    void setWhosCheckMate(char value);
    /**
           * getter i setter pola Player
           */
    Player *getWhite() const;
    Player *getBlack() const;

};

#endif // CHESSGAME_H
