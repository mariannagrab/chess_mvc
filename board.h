#ifndef BOARD_H
#define BOARD_H

#include <QLabel>
#include <QWidget>
class BoardPiece : public QLabel
{
    Q_OBJECT
    const QSize siz = QSize(100,100);
    int row,column;
    bool isSelected;
    QString color;
    bool isMovePossThere;
public:
    explicit BoardPiece(int row, int column, QWidget *parent = nullptr);
    void setColor(bool color);
    void unhighlight();
    void highlight();
    bool getisSelected();
    void setisSelected(bool value);
    QString getColor();
    bool getisMovePossThere() const;
    void setisMovePossThere(bool value);

    int getRow() const;

    int getColumn() const;

signals:
    void clicked(int row, int column);
protected:
    void mousePressEvent(QMouseEvent *event);

};

class Board : public QWidget
{
    BoardPiece *boarpieces[8][8];
    BoardPiece *selectedBoardPiece;

    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    BoardPiece *getSelectedBoardPiece() const;
    void setSelectedBoardPiece(BoardPiece *value);
    void addPieces();
    void clearAllAfterMove();

public slots:
    void validateClick(int row, int column);
    void validateButtonClick();


signals:

};

#endif // BOARD_H
