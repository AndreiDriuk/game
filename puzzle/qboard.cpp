#include "qboard.h"
#include <iostream>
#include <QRandomGenerator>

QBoard::QBoard(QWidget *parent)
    : QWidget{parent}
{

}

void QBoard::InitLabels(qint32 s)
{
    size = s;
    QWidget* mainGameWidget = this->parentWidget();
    QSize gameBoardSize = mainGameWidget->size();
    QSize sizeLabel(gameBoardSize.width()/size-size, gameBoardSize.height()/size-size);
    QFont* f = new QFont("Serif", gameBoardSize.width()/size/4, QFont::Bold);
    label2D = new QBoardLabel**[size];

    for(int i = 0; i<size; ++i){
       label2D[i] = new QBoardLabel*[size];
        for(int j = 0; j<size; ++j){
            if(i!=size-1 || j!=size-1){

                label2D[i][j] = new QBoardLabel(QString::number(i*size+j+1), mainGameWidget);
                label2D[i][j]->setGeometry((gameBoardSize.width()/size+1)*j,(gameBoardSize.height()/size+1)*i, sizeLabel);
                label2D[i][j]->setNumber(i*size+j+1);
                //std::cout<<"i = " <<i<<" j = "<<j<<label2D[i][j]<<std::endl;
                QString labelSheet="QLabel{border: 1px solid black; border-radius: 10px; background: qlineargradient(x1:0, y1:1, х2:0, у2:0, stop:0.8 rgba(248, 176, 104, 0.9), stop:0.65 rgba(224, 112, 00, 0.7), stop:0.45 rgba(184, 88, 00, 0.7), stop:0.25 rgba(128, 64, 00, 0.7));} ";
                label2D[i][j]->setCSSStyle(labelSheet, *f);
            }else{
                emptyLabel = new QBoardLabel("", mainGameWidget);
                emptyLabel->setGeometry((gameBoardSize.width()/size+1)*j,(gameBoardSize.height()/size+1)*i, sizeLabel);
                label2D[i][j] = emptyLabel;
                label2D[i][j]->setNumber(0);
            }
        }
    }
    for(int i = 0; i<size; ++i){
        for(int j = 0; j<size; ++j){

            if(i==0){
                label2D[i][j]->setUpLabel(nullptr);
                label2D[i][j]->setDownLabel(label2D[i+1][j]);
                if(j==0){
                    label2D[i][j]->setLeftLabel(nullptr);
                    label2D[i][j]->setRightLabel(label2D[i][j+1]);
                }else if(j>0 &&j<size-1) {
                    label2D[i][j]->setLeftLabel(label2D[i][j-1]);
                    label2D[i][j]->setRightLabel(label2D[i][j+1]);
                }else if(j==size-1){
                    label2D[i][j]->setLeftLabel(label2D[i][j-1]);
                    label2D[i][j]->setRightLabel(nullptr);
                }
            }else if(i==size-1){
                label2D[i][j]->setDownLabel(nullptr);
                label2D[i][j]->setUpLabel(label2D[i-1][j]);
                if(j==0){
                    label2D[i][j]->setLeftLabel(nullptr);
                    label2D[i][j]->setRightLabel(label2D[i][j+1]);
                }else if(j>0 &&j<size-1) {
                    label2D[i][j]->setLeftLabel(label2D[i][j-1]);
                    label2D[i][j]->setRightLabel(label2D[i][j+1]);
                }else if(j==size-1){
                    label2D[i][j]->setLeftLabel(label2D[i][j-1]);
                    label2D[i][j]->setRightLabel(nullptr);
                }
            }else if (i>0 && i<size-1){
                label2D[i][j]->setDownLabel(label2D[i+1][j]);
                label2D[i][j]->setUpLabel(label2D[i-1][j]);
                if(j==0){
                    label2D[i][j]->setLeftLabel(nullptr);
                    label2D[i][j]->setRightLabel(label2D[i][j+1]);
                }else if(j>0 &&j<size-1) {
                    label2D[i][j]->setLeftLabel(label2D[i][j-1]);
                    label2D[i][j]->setRightLabel(label2D[i][j+1]);
                }else if(j==size-1){
                    label2D[i][j]->setLeftLabel(label2D[i][j-1]);
                    label2D[i][j]->setRightLabel(nullptr);
                }
            }
        }
    }
}


void QBoard::moveRight()
{
    QBoardLabel *leftLabel = emptyLabel->getLeftLabel();
    if((leftLabel))
    {
        int xEmpty = emptyLabel->getX();
        int yEmpty = emptyLabel->getY();
        int emptyNumber = emptyLabel->getNumber();
        QBoardLabel* upEmptyLabel = emptyLabel->getUpLabel();
        QBoardLabel* downEmptyLabel = emptyLabel->getDownLabel();
        QBoardLabel* rightEmptyLabel = emptyLabel->getRightLabel();
        QBoardLabel* leftEmptyLabel = emptyLabel->getLeftLabel();
        int leftNumber = leftLabel->getNumber();

        QBoardLabel* upChangedLabel = leftLabel->getUpLabel();
        QBoardLabel* downChangedLabel = leftLabel->getDownLabel();
        QBoardLabel* rightChangedLabel = leftLabel->getRightLabel();
        QBoardLabel* leftChangedLabel = leftLabel->getLeftLabel();

        emptyLabel->moveTo(leftLabel->getX(), leftLabel->getY());
        emptyLabel->setRightLabel(leftLabel);
        emptyLabel->setLeftLabel(leftChangedLabel);
        emptyLabel->setUpLabel(upChangedLabel);
        emptyLabel->setDownLabel(downChangedLabel);


        leftLabel->moveTo(xEmpty, yEmpty);
        leftLabel->setRightLabel(rightEmptyLabel);
        leftLabel->setLeftLabel(emptyLabel);
        leftLabel->setUpLabel(upEmptyLabel);
        leftLabel->setDownLabel(downEmptyLabel);
        emptyLabel->setNumber(leftLabel->getNumber());
        leftLabel->setNumber(emptyNumber);
    }

}

void QBoard::moveLeft()
{
    QBoardLabel *rightLabel = emptyLabel->getRightLabel();
    if((rightLabel))
    {
        int xEmpty = emptyLabel->getX();
        int yEmpty = emptyLabel->getY();
        int emptyNumber = emptyLabel->getNumber();
        QBoardLabel* upEmptyLabel = emptyLabel->getUpLabel();
        QBoardLabel* downEmptyLabel = emptyLabel->getDownLabel();
        QBoardLabel* rightEmptyLabel = emptyLabel->getRightLabel();
        QBoardLabel* leftEmptyLabel = emptyLabel->getLeftLabel();

        QBoardLabel* upChangedLabel = rightLabel->getUpLabel();
        QBoardLabel* downChangedLabel = rightLabel->getDownLabel();
        QBoardLabel* rightChangedLabel = rightLabel->getRightLabel();
        QBoardLabel* leftChangedLabel = rightLabel->getLeftLabel();

        emptyLabel->moveTo(rightLabel->getX(), rightLabel->getY());
        emptyLabel->setRightLabel(rightLabel->getRightLabel());
        emptyLabel->setLeftLabel(rightLabel);
        emptyLabel->setUpLabel(rightLabel->getUpLabel());
        emptyLabel->setDownLabel(rightLabel->getDownLabel());

        rightLabel->moveTo(xEmpty, yEmpty);

        rightLabel->setRightLabel(emptyLabel);
        rightLabel->setLeftLabel(leftEmptyLabel);
        rightLabel->setUpLabel(upEmptyLabel);
        rightLabel->setDownLabel(downEmptyLabel);
        emptyLabel->setNumber(rightLabel->getNumber());
        rightLabel->setNumber(emptyNumber);
    }
}

void QBoard::moveUp()
{
    QBoardLabel *downLabel = emptyLabel->getDownLabel();
    if((downLabel))
    {
        int xEmpty = emptyLabel->getX();
        int yEmpty = emptyLabel->getY();
        int emptyNumber = emptyLabel->getNumber();
        QBoardLabel* upEmptyLabel = emptyLabel->getUpLabel();
        QBoardLabel* downEmptyLabel = emptyLabel->getDownLabel();
        QBoardLabel* rightEmptyLabel = emptyLabel->getRightLabel();
        QBoardLabel* leftEmptyLabel = emptyLabel->getLeftLabel();

        QBoardLabel* upChangedLabel = downLabel->getUpLabel();
        QBoardLabel* downChangedLabel = downLabel->getDownLabel();
        QBoardLabel* rightChangedLabel = downLabel->getRightLabel();
        QBoardLabel* leftChangedLabel = downLabel->getLeftLabel();

        emptyLabel->moveTo(downLabel->getX(), downLabel->getY());
        emptyLabel->setDownLabel(downChangedLabel);
        emptyLabel->setLeftLabel(leftChangedLabel);
        emptyLabel->setRightLabel(rightChangedLabel);
        emptyLabel->setUpLabel(downLabel);

        downLabel->moveTo(xEmpty, yEmpty);
        downLabel->setRightLabel(rightEmptyLabel);
        downLabel->setLeftLabel(leftEmptyLabel);
        downLabel->setDownLabel(emptyLabel);
        downLabel->setUpLabel(upEmptyLabel);

        emptyLabel->setNumber(downLabel->getNumber());
        downLabel->setNumber(emptyNumber);
    }
}

void QBoard::moveDown()
{
    QBoardLabel *upLabel = emptyLabel->getUpLabel();
    if((upLabel))
    {
        int xEmpty = emptyLabel->getX();
        int yEmpty = emptyLabel->getY();
        int emptyNumber = emptyLabel->getNumber();

        QBoardLabel* upEmptyLabel = emptyLabel->getUpLabel();
        QBoardLabel* downEmptyLabel = emptyLabel->getDownLabel();
        QBoardLabel* rightEmptyLabel = emptyLabel->getRightLabel();
        QBoardLabel* leftEmptyLabel = emptyLabel->getLeftLabel();

        QBoardLabel* upChangedLabel = upLabel->getUpLabel();
        QBoardLabel* downChangedLabel = upLabel->getDownLabel();
        QBoardLabel* rightChangedLabel = upLabel->getRightLabel();
        QBoardLabel* leftChangedLabel = upLabel->getLeftLabel();

        emptyLabel->moveTo(upLabel->getX(), upLabel->getY());
        emptyLabel->setUpLabel(upChangedLabel);
        emptyLabel->setLeftLabel(leftChangedLabel);
        emptyLabel->setRightLabel(rightChangedLabel);
        emptyLabel->setDownLabel(upLabel);

        upLabel->moveTo(xEmpty, yEmpty);
        upLabel->setRightLabel(rightEmptyLabel);
        upLabel->setLeftLabel(leftEmptyLabel);
        upLabel->setDownLabel(downEmptyLabel);
        upLabel->setUpLabel(emptyLabel);
        emptyLabel->setNumber(upLabel->getNumber());
        upLabel->setNumber(emptyNumber);
    }
}

void QBoard::changeLabels(QBoardLabel *change)
{
    QBoardLabel* upEmptyLabel = emptyLabel->getUpLabel();
    QBoardLabel* downEmptyLabel = emptyLabel->getDownLabel();
    QBoardLabel* rightEmptyLabel = emptyLabel->getRightLabel();
    QBoardLabel* leftEmptyLabel = emptyLabel->getLeftLabel();

    QBoardLabel* upChangeLabel = change->getUpLabel();
    QBoardLabel* downChangeLabel = change->getDownLabel();
    QBoardLabel* rightChangeLabel = change->getRightLabel();
    QBoardLabel* leftChangeLabel = change->getLeftLabel();

    int posX = emptyLabel->getX();
    int posY = emptyLabel->getY();
    emptyLabel->moveTo(change->getX(), change->getY());
    change->moveTo(posX, posY);

    if(rightEmptyLabel==change){
        emptyLabel->setLeftLabel(change);
        change->setRightLabel(emptyLabel);

    }else if(leftChangeLabel==change){
        emptyLabel->setRightLabel(change);
        change->setLeftLabel(emptyLabel);

    }else if(upChangeLabel==change){
        emptyLabel->setDownLabel(change);
        change->setUpLabel(emptyLabel);

    }else if(downChangeLabel==change){
        emptyLabel->setUpLabel(change);
        change->setDownLabel(emptyLabel);
    }

}

void QBoard::mix(){
    QRandomGenerator *generator = QRandomGenerator::system();
    moveUp();
    moveUp();
    moveLeft();
    moveLeft();
    for(int i = 0; i<100000; ++i){
        int move = generator->bounded(4);
        //std::cout<<move<<std::endl;
        switch(move){
            case 0:
                moveUp();
                break;
            case 1:
                moveRight();
                break;
            case 2:
                moveDown();
                break;
            case 3:
                moveLeft();
                break;
        }
    }

}

void QBoard::checkEnd()
{
    bool isFinished = true;
    for(int i = 0; i<size; ++i){
        for(int j = 0; j<size; ++j){
            if(i!=size-1 || j!=size-1){
                //std::cout<<(label2D[i][j]->getNumber())<<"  "<< (label2D[i][j]->getNumber()==i*size+j+1)<<std::endl;
                isFinished&=((label2D[i][j]->getNumber())==i*size+j+1);
            }else{
               isFinished&=(label2D[i][j]->getNumber()==0);
            }
        }
    }
    if(isFinished){
        std::cout<<"end"<<std::endl;
        emit sgl_gameOver();
    }


}




