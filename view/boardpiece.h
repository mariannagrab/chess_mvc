#ifndef BOARDPIECE_H
#define BOARDPIECE_H
#include <QLabel>
#include <QWidget>
/**
 *  klasa BoardPiece, dziedzicząca po QLabel
 *  tworzy kwadrat w GUI
 *
 */
class BoardPiece : public QLabel
{
    Q_OBJECT
    const QSize siz = QSize(100,100); /**< rozmiar kwadratu */
    int row,column; /**< wiersz kolumna - ustawienie na planszy Board */
    bool isSelected; /**< czy jest aktualnie zaznaczony (był kliknięty przez gracza) */
    QString color; /**< kolor kwadratu */
    bool isMovePossThere; /**< czy po kliknięciu na inny kwadrat ten kwadrat jest podświetlony, że jest tu możliwy ruch */
public:
    /**
           * Konstruktor.
           * tworzy kwadrat, ustawia jego rozmiary
           */
    explicit BoardPiece(int row, int column, QWidget *parent = nullptr);
    /**
           * setter pola color
           * @param true ustawia kolor na jasnoszary, false na ciemnoszary
           */
    void setColor(bool color);
    /**
           * odświetla dany kwadrat (przywraca mu kolor pola color)
           */
    void unhighlight();
    /**
           * zaznacza dany kwadrat (przydziela mu kolor tła czarwony)
           */
    void highlight();
    /**
           * getter i setter pola isSelected informacji czy kwadrat jest kliknięty rzez gracza
           */
    bool getisSelected();
    void setisSelected(bool value);
    /**
           * getter pola color - używany przy powrocie kwadratu po podświetleniu
           */
    QString getColor();
    /**
           * getter i setter pola isMovePossThere czy jest możliwy ruch pionka na to pole
           */
    bool getisMovePossThere() const;
    void setisMovePossThere(bool value);
    /**
           * getter pola Row
           */
    int getRow() const;
    /**
           * getter pola Column
           */
    int getColumn() const;
signals:
    /**
           * sygnał kliknięcia na BoardPiece wysyłany do klasy Board - validateclick()
           */
    void clicked(int row, int column);
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // BOARDPIECE_H
