#include <QApplication>
#include <iostream>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    start();
    return a.exec();
}
