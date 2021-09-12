#include "mainwindow.h"
#include <vector>
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
    layout_wysokosc2->setSpacing(0);
    chessLabel();
    startNewGame();
    createBoard();
    addPieces();

    displayCheckAndCaptured();
    layout_dlugosc->addLayout(layout_wysokosc);
    layout_dlugosc->addLayout(layout_dlugosc2);
    layout_dlugosc->addLayout(layout_wysokosc2);

}


void MainWindow::startNewGame()
{
    train_button = new QPushButton();
    train_button->setText(tr("Rozpocznij nowa gre"));
    train_button->setStyleSheet("background-color: rgb(255,220,220);margin: 6px;");
    connect(train_button,SIGNAL(clicked()),this,SLOT(validateButtonClick()));

    layout_wysokosc->addWidget(train_button,0);

}

void MainWindow::chessLabel()
{

    turnSign = new QLabel();
    turnSign->setText("Teraz kolej gracza białego");
    turnSign->setStyleSheet("font-size: 20px;");
    turnSign->setMinimumSize(300,100);
    layout_wysokosc->addWidget(turnSign,1);
}

void MainWindow::createBoard()
{
   board = new Board();
   board ->setFixedSize(800,800);
   layout_dlugosc2 -> addWidget(board);
}

void MainWindow::addPieces()
{
    board ->addPieces();
}

void MainWindow::setTurn(QString napis)
{
    turnSign->setText(napis);

}

void MainWindow::displayCheckAndCaptured()
{
    QLabel  *blackCapturedSign = new QLabel();
    blackCapturedSign->setText("Pionki zbite przez gracza czarnego:");
    layout_wysokosc2->addWidget(blackCapturedSign,1);

    capturedByBlack = new QWidget();
    blackgridlayout = new QGridLayout();
    blackgridlayout->setSpacing(5);
    capturedByBlack -> setLayout(blackgridlayout);


    layout_wysokosc2->addWidget(capturedByBlack,2);

    checkSign = new QLabel();
    checkSign->setText("");
    checkSign->setStyleSheet("font-size: 15px;");
    checkSign->setMinimumSize(300,100);
    layout_wysokosc2->addWidget(checkSign,3);

    QLabel  *whiteCapturedSign = new QLabel();
    whiteCapturedSign->setText("Pionki zbite przez gracza białego:");
    layout_wysokosc2->addWidget(whiteCapturedSign,4);

    capturedByWhite = new QWidget();
    whitegridlayout = new QGridLayout();
    whitegridlayout->setSpacing(5);
    capturedByWhite -> setLayout(whitegridlayout);
    layout_wysokosc2->addWidget(capturedByWhite,5);

    capturedFieldsInit();

}

void MainWindow::setCheck(QString napis)
{
    checkSign->setText(napis);

}

void MainWindow::addToCaptured(char color,char c, int qty)
{
    if(qty==0){
        return;
    }
    if(color=='w'){
        QLabel *pionek;
        if(qty<=4){
            pionek = capturedByWhiteL[0][qty-1];
        }else if(qty<=8){
            pionek = capturedByWhiteL[1][qty-5];
        }else if(qty<= 12){
            pionek = capturedByWhiteL[2][qty-9];
        }else{
            pionek = capturedByWhiteL[3][qty-13];

        }
        pionek ->setPixmap((QPixmap(":/new/prefix1/"+ QString(c) +".png")).scaled(40,40));

    }else{
        QLabel *pionek;
        if(qty<=4){
            pionek = capturedByBlackL[0][qty-1];
        }else if(qty<=8){
            pionek = capturedByBlackL[1][qty-5];
        }else if(qty<= 12){
            pionek = capturedByBlackL[2][qty-9];
        }else{
            pionek = capturedByBlackL[3][qty-13];

        }
        pionek ->setPixmap((QPixmap(":/new/prefix1/"+ QString(tolower(c)) +"w.png")).scaled(40,40));

    }
}

void MainWindow::capturedFieldsInit()
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QLabel *pionek = new QLabel();
            pionek -> setFixedSize(50,50);
            capturedByBlackL[i][j] = pionek;
            blackgridlayout->addWidget(pionek,i,j);
            QLabel *pionek2 = new QLabel();
            pionek2 -> setFixedSize(50,50);
            capturedByWhiteL[i][j] = pionek2;
            whitegridlayout->addWidget(pionek2,i,j);
        }
    }
}

void MainWindow::clearCaptured()
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            capturedByBlackL[i][j] -> setPixmap(QPixmap("w.png"));
            capturedByWhiteL[i][j] -> setPixmap(QPixmap("w.png"));
        }
    }
}

void MainWindow::clearBoard()
{
    board ->clearAllAfterMove();
}



void MainWindow::validateButtonClick()
{
    board ->validateButtonClick();
}




