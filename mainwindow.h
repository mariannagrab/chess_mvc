#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include "board.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    // start new game button
    QWidget *widget;
    QWidget *wdg, *wdg1;
    QPushButton *train_button;
    QLabel *chess;
    QLabel *turnSign;
    QLabel *checkSign;

    QHBoxLayout *layout_dlugosc;
    QHBoxLayout *layout_dlugosc2;
    QVBoxLayout *layout_wysokosc;
    QVBoxLayout *layout_wysokosc2;

    Board *board;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void  createActions();
    void startNewGame();
    void chessLabel();
    void newFile();
    void createBoard();
    void displayTurn();
    void setTurn(QString napis);
    void displayCheckInfo();
signals:
    void clicked();
public slots:
    void validateButtonClick();

};

#endif // MAINWINDOW_H
