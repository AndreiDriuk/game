#ifndef QBOARDLABEL_H
#define QBOARDLABEL_H

#include <QLabel>
#include<QWidget>
#include <QPropertyAnimation>

class QBoardLabel : public QWidget
{
    Q_OBJECT
public:
    QBoardLabel(QString name,  QWidget *wgt);
    QLabel* label;

    void setText(QString text);
    void setGeometry(int x, int y, QSize labelSize);
    void setCSSStyle(QString cssStyle, QFont f);
    void setUpLabel(QBoardLabel* upBoardLabel);
    void setDownLabel(QBoardLabel* downBoardLabel);
    void setRightLabel(QBoardLabel* rightBoardLabel);
    void setLeftLabel(QBoardLabel* leftBoardLabel);
    void moveTo(int x, int y);
    void setNumber(int n){number = n;}
    int getNumber(){return number;}
    int getX(){return posX;}
    int getY(){return posY;}

    void checkNumbers();

    QBoardLabel* getUpLabel(){return upBoardLabel;}
    QBoardLabel* getDownLabel(){return downBoardLabel;}
    QBoardLabel* getRightLabel(){return rightBoardLabel;}
    QBoardLabel* getLeftLabel(){return leftBoardLabel;}

    QLabel* getLabel(){ return currentLabel;}
    bool checkCurrentLabel(){return currentLabel==mainLabel;}

private:
    int posX;
    int posY;
    int number;
    const QLabel* mainLabel;
    QLabel* currentLabel;
    QSize sizeL;

    QBoardLabel* upBoardLabel = nullptr;
    QBoardLabel* downBoardLabel = nullptr;
    QBoardLabel* rightBoardLabel = nullptr;
    QBoardLabel* leftBoardLabel = nullptr;

};

#endif // QBOARDLABEL_H
