#include "gamecollect.h"
#include "ui_gamecollect.h"
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include <QThread>
#include <qboard.h>
#include <iostream>
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>


GameCollect::GameCollect(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameCollect)
{
    ui->setupUi(this);
    //Set Central Widget to Add other widgets
    centralWidget = new QWidget();
    this->setCentralWidget(centralWidget);
    centralWidget->setMaximumWidth(1920);
    centralWidget->setMaximumHeight(1080);
    centralWidget->setObjectName("Central");
    centralWidget->setStyleSheet("QWidget#Central {background-image: url(:/Image1/North.jpg);}");

    size = 7;
    mainLayout = new QHBoxLayout();

    centralWidget->setLayout(mainLayout);
    mainGameWidget = new QWidget();
    mainGameWidget->setMinimumWidth(600);
    mainGameWidget->setMinimumHeight(600);
    mainGameWidget->setMaximumWidth(600);
    mainGameWidget->setMaximumHeight(600);

    buttonStart = new QPushButton("Start");
    buttonStart->setMaximumWidth(100);

    buttonStop = new QPushButton("Stop");
    buttonStop->setMaximumWidth(100);

    centralWidget->layout()->addWidget(mainGameWidget);
    gameBoard = new QBoard(mainGameWidget);
    gameBoard->InitLabels(size);

    connect(gameBoard, &QBoard::sgl_gameOver, this, &GameCollect::slt_gameOver);

}

GameCollect::~GameCollect()
{
    delete ui;
}

void GameCollect::slt_gameOver()
{
    //QMessageBox::warning(this, "Game Over", "Game Over");
    QWidget* finish = new QWidget(nullptr);
    QLabel *label = new QLabel(finish);
    finish->setMinimumWidth(1320);
    finish->setMinimumHeight(1080);
    finish->setMaximumWidth(1320);
    finish->setMaximumHeight(1080);
    label->setGeometry(finish->geometry());
    QPixmap map(":/Image1/North.jpg");
    label->setPixmap(map.scaled(label->size(),Qt::KeepAspectRatio));


    finish->setObjectName("Finish");
    //finish->setStyleSheet("QWidget#Finish {background-image: url(:/Image1/final.png);}");
    finish->show();
    //exit(-1);


}

void GameCollect::keyPressEvent(QKeyEvent *pe)
{

        //std::cout<<pe->key()<<std::endl;
        switch (pe->key()) {
        case Qt::Key_Up:
            gameBoard->moveUp();
            gameBoard->checkEnd();
            break;
        case Qt::Key_Down:
            gameBoard->moveDown();
            gameBoard->checkEnd();
            break;
        case Qt::Key_Left:
            gameBoard->moveLeft();
            gameBoard->checkEnd();
            break;
        case Qt::Key_Right:
            gameBoard->moveRight();
            gameBoard->checkEnd();
            break;
        default:
            std::cout<<pe->key()<<std::endl;/*
            QWidget::keyPressEvent(event);*/
        }

}


