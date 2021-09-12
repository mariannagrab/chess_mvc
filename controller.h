#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model\chessgame.h"
#include "view\mainwindow.h"
/**
       * Kontroler gry
       * przesyła informację z modelu do GUI
       * odpowiada za rozpoczęcie gry oraz jej przebieg
       */
void start();
void newGame();
void quitGame();
/**
       * getPieceFromPosition - zwraca pionek z danej pozycjiz modelu
       */
char getPieceFromPosition(int row,int column);
/**
       * funkcja zwracająca dostępne pola do poruszenia w postaci wektora dla pionka położonego (whatPiece_row,whatPiece_column)
       * @param wiersz, kolumna pionka dla którego sprawdzane są możliwości ruchu
       * @return wskaźnik do wektora dostępnych pól <int wiersz1, int kolumna1,int wiersz2, int kolumna2 >
       */
vector<int>* checkAvailableMoves(int row, int column);
/**
       * funkcja zapisująca bieżący ruch do ThisMove w modelu
       * funkcja wykonująca ruch na tablicy board na podstawie informacji o ruchu ThisMove
       * @param wiersz, kolumna poruszającego się pionka oraz wiersz, kolumna dokąd pionek sieporusza
       */
   //
void movePiece(int whatPiece_row,int whatPiece_column, int putWhere_row, int putWhere_column);
/**
       * getter pola whosTurn modelu
       * @return kolor gracza którego jest teraz kolej
       */
char getWhosTurn();
/**
       * funkcja zwracająca kolor pionka
       * @return kolor pionka WHITE or BLACK
       */
char checkPieceColor(char piece);
/**
       * funkcja zmieniająca napis w mainwindow który gracz powinien wykonać teraz ruch
       */
void displayTurn();
/**
       * funkcja zmieniająca napis w mainwindow czy obecnie jest Szach oraz dla którego gracza
       */
void displayCheckInfo();
/**
       * funkcja wyświetlająca pop-up window w mainwindow z napisem koniec gry i szach mat dla którego gracza
       */
void displayEndOfGame();
/**
       * funkcja zwracająca informacje o szach mat
       * @return false gdy nie ma szach mat
       */
bool isCheckMate();
/**
       * funkcja wywołująca w mainwindow widget ze zmieniającymi się pionkami, które zostały zbite
       */
void displayCapturedPieces();
/**
       * funkcja zwracająca dopiero co zbity pionek przez gracza o danym
       * @param kolorze
       */
char getCapturedPiece(char color);
/**
       * funkcja zwracająca informację ile pionków zostało zbitych przez gracza o danym
       * @param kolorze
       * @return długość wektora captured
       */
int getCountCapturedPiece(char color);
/**
       * funkcja czyszcząca widget wyświetlający zbite pionki
       */
void clearCaptured();
/**
       * funkcja updatująca grę po każdym ruchu (odświetla kwadraty, czyści parametry)
       */
void updateGame();

#endif // CONTROLLER_H
