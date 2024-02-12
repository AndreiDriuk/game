#include "qboardlabel.h"
#include <iostream>

QBoardLabel::QBoardLabel(QString name, QWidget *wgt)
    : QWidget(wgt)
{
    label = new QLabel(name, wgt );
    mainLabel = label;
}

void QBoardLabel::setGeometry(int x, int y, QSize labelSize)
{
    posX = x;
    posY = y;
    sizeL = labelSize;
    label->setGeometry(x, y, labelSize.width(), labelSize.height());
}

void QBoardLabel::setCSSStyle(QString cssStyle, QFont f)
{
    label->setStyleSheet(label->styleSheet()+cssStyle);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(f);
}

void QBoardLabel::setUpLabel(QBoardLabel *upBoard)
{
    upBoardLabel = upBoard;
    if(upBoard &&upBoard->getDownLabel()!=this){
        upBoard->setDownLabel(this);
    }
}

void QBoardLabel::setDownLabel(QBoardLabel *downBoard)
{
    downBoardLabel = downBoard;
    if(downBoard &&downBoard->getUpLabel()!=this){
        downBoard->setUpLabel(this);
    }
}

void QBoardLabel::setRightLabel(QBoardLabel *rightBoard)
{
    rightBoardLabel = rightBoard;
    if(rightBoard && rightBoard->getLeftLabel()!=this){
        rightBoard->setLeftLabel(this);
    }
}

void QBoardLabel::setLeftLabel(QBoardLabel *leftBoard)
{
    leftBoardLabel = leftBoard;
    if(leftBoard && leftBoard->getRightLabel()!=this){
        leftBoard->setRightLabel(this);
    }
}

void QBoardLabel::moveTo(int x, int y)
{
    //panim->setDuration(1);
    posX = x;
    posY = y;
    label->setGeometry(posX, posY, sizeL.width(), sizeL.height());
}

void QBoardLabel::checkNumbers()
{
    std::cout<<"For number "<<number<<" ";
    if(leftBoardLabel)
        std::cout<<" left: "<< leftBoardLabel->getNumber();
    else{
        std::cout<<" left: "<< -1;
    }
    if(rightBoardLabel)
        std::cout<<" right: "<< rightBoardLabel->getNumber();
    else{
        std::cout<<" right: "<< -1;
    }

    if(upBoardLabel)
        std::cout<<" up: "<< upBoardLabel->getNumber();
    else{
        std::cout<<" up: "<< -1;
    }

    if(downBoardLabel)
        std::cout<<" down: "<< downBoardLabel->getNumber();
    else{
        std::cout<<" down: "<< -1;
    }

    std::cout<<std::endl;
}


