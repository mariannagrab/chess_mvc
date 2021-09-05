TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += \
        board.cpp \
        chessgame.cpp \
        controller.cpp \
        main.cpp \
        mainwindow.cpp \
        player.cpp

HEADERS += \
    board.h \
    chessgame.h \
    controller.h \
    mainwindow.h \
    player.h

QT += widgets

FORMS +=

RESOURCES += images.qrc \

