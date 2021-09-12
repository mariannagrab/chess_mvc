#ifndef BOARD_H
#define BOARD_H
#include "boardpiece.h"
#include <QLabel>
#include <QWidget>
/**
 *  klasa Board, dziedzicząca po QWidget
 *  tworzy 64 obiekty BoardPiece w GUI
 *  wyświetla je jako planszę [8][8]
 *  odpowiada za walidację klikniecia na kwadrat orz ich podświetlanie oraz odznaczanie
 *  odbiera sygnał z przycisku
 *  przechowuje informacje o zaznaczonych polach
 */
class Board : public QWidget
{
    Q_OBJECT
    BoardPiece *boarpieces[8][8]; /**< 64 biało-czarne kwadraty na planszy */
    BoardPiece *selectedBoardPiece; /**< BoardPiece który jest zaznaczony */

public:
    /**
           * Konstruktor.
           * ustawia grid layout i dodaje BoardPieces
           * łączy sygnał naciśnięcia na każdy kwadrat BoardPiece z funckją validateClick
           * ustawia kolory kwadratów na biały lub czarny
           */
    explicit Board(QWidget *parent = nullptr);
    /**
           * getter i setter pola selectedBoardPiece
           */
    BoardPiece *getSelectedBoardPiece() const;
    void setSelectedBoardPiece(BoardPiece *value);
    /**
           * funkcja dodaje pionki na planszy zgaodnie z ustawieniem z modelu
           */
    void addPieces();
    /**
           * funkcja odznacza podświetlenie kwadratów i czyści parametry związane z możliwością ruchu
           */
    void clearAllAfterMove();
public slots:
    /**
           * slot validateClick jest wywołany po naciśnięciu odpowiedniego kwadratu BoardPiece na planszy
           * waliduje ruch - dokładny opis znajduje się w ciele funkcji
           * @param wiersz, kolumna klikniętego kwadratu
           */
    void validateClick(int row, int column);
    /**
           * slot validateButtonClick wywołuje funkcję tworzącą nową grę
           */
    void validateButtonClick();

};

#endif // BOARD_H
