TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += \
        controller.cpp \
        main.cpp \
        model/chessgame.cpp \
        model/player.cpp \
        view/board.cpp \
        view/boardpiece.cpp \
        view/mainwindow.cpp

HEADERS += \
    controller.h \
    model/chessgame.h \
    model/player.h \
    view/board.h \
    view/boardpiece.h \
    view/mainwindow.h

QT += widgets

FORMS +=

RESOURCES += images.qrc \

