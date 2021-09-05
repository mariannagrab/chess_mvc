#include "mainwindow.h"

#include <QHBoxLayout>
#include <QMenuBar>
#include <QIcon>
#include <QToolBar>
#include <QPushButton>
#include <QDesktopWidget>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

   widget = new QWidget;
    setCentralWidget(widget);
    layout_dlugosc = new QHBoxLayout;
    widget->setLayout(layout_dlugosc);
    layout_dlugosc2 = new QHBoxLayout;

    setWindowTitle(tr("Szachy"));
    layout_wysokosc = new QVBoxLayout;
    layout_wysokosc2 = new QVBoxLayout;

    layout_wysokosc->setAlignment(Qt::AlignCenter);
    layout_wysokosc2->setAlignment(Qt::AlignCenter);

    chessLabel();
    startNewGame();
    createBoard();
    displayTurn();
    displayCheckInfo();
   // resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
    layout_dlugosc->addLayout(layout_wysokosc);
    layout_dlugosc->addLayout(layout_dlugosc2);
    layout_dlugosc->addLayout(layout_wysokosc2);

}


void MainWindow::startNewGame()
{
   // wdg = new QWidget(this);
    train_button = new QPushButton();
    train_button->setText(tr("Rozpocznij nowa gre"));
    train_button->setStyleSheet("background-color: rgb(255,220,220);margin: 6px;");
    connect(train_button,SIGNAL(clicked()),this,SLOT(validateButtonClick()));

    layout_wysokosc->addWidget(train_button,0);

}

void MainWindow::chessLabel()
{
   // wdg1 = new QWidget(this);
    chess = new QLabel();
    chess->setText("Szachownica");
    chess->setStyleSheet("font-size: 15px;");
    //chess->setAlignment(Qt::AlignCenter);
    layout_wysokosc->addWidget(chess,1);
}

void MainWindow::createBoard()
{
   board = new Board();
   board ->setFixedSize(800,800);
   layout_dlugosc2 -> addWidget(board);
}

void MainWindow::displayTurn()
{
    turnSign = new QLabel();
    turnSign->setText("Teraz kolej gracza białego");
    turnSign->setStyleSheet("font-size: 15px;");
  //  turnSign->setMinimumSize(300,100);
    layout_wysokosc2->addWidget(turnSign,0);
}

void MainWindow::setTurn(QString napis)
{
    turnSign->setText(napis);
    //layout->addWidget(turnSign);

}

void MainWindow::displayCheckInfo()
{
    checkSign = new QLabel();
    checkSign->setText("Informacja o szachu");
    checkSign->setStyleSheet("font-size: 15px;");
    checkSign->setMinimumSize(300,100);
    layout_wysokosc2->addWidget(checkSign,1);
}

void MainWindow::validateButtonClick()
{
    board ->validateButtonClick();
}




