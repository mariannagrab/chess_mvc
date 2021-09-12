#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include "view\board.h"
/**
 *  klasa MainWindow dziedzicząca po QMainWindow
 *  odpowiada za stworzenie, wyświetlanie wszystkich elementów GUI,
 *  ich rozłożenie oraz update przy zmianie parametrów gry
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *widget;
    QWidget *wdg, *wdg1;
    QPushButton *train_button;
    QLabel *chess;
    QLabel *turnSign;
    QWidget *capturedByWhite,*capturedByBlack;
    QLabel *capturedByWhiteL[4][4],*capturedByBlackL[4][4];
    QGridLayout *blackgridlayout,*whitegridlayout;
    QLabel *checkSign;
    QHBoxLayout *layout_dlugosc;
    QHBoxLayout *layout_dlugosc2;
    QVBoxLayout *layout_wysokosc;
    QVBoxLayout *layout_wysokosc2;

    Board *board;

public:
    /**
           * Konstruktor.
           * tworzy layout, dodaje wszystkie elementu GUI oraz ustala ich parametry
           */
    explicit MainWindow(QWidget *parent = nullptr);
    /**
           * tworzy przycisk stwórz nową grę
           */
    void startNewGame();
    /**
           * tworzy Label informujący o kolejności ruchu
           */
    void chessLabel();
    /**
           * tworzy tablicę Board
           */
    void createBoard();
    /**
           * dodaje pionki do tablicy Board
           */
    void addPieces();
    /**
           * ustala napis informujący o kolejności ruchu
           */
    void setTurn(QString napis);
    /**
           * tworzy QWidget ze zbitymi pionkami
           */
    void displayCheckAndCaptured();
    void setCheck(QString napis);
    void addToCaptured(char color, char c, int qty);
    void capturedFieldsInit();
    void clearCaptured();
    void clearBoard();
signals:
    void clicked();
public slots:
    void validateButtonClick();

};

#endif // MAINWINDOW_H
