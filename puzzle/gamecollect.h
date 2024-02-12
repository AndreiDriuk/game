#ifndef GAMECOLLECT_H
#define GAMECOLLECT_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QVector>
#include <qboard.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GameCollect; }
QT_END_NAMESPACE

class GameCollect : public QMainWindow
{
    Q_OBJECT

public:
    GameCollect(QWidget *parent = nullptr);
    ~GameCollect();
    QPushButton *buttonStart;
    QPushButton *buttonStop;

    QHBoxLayout *mainLayout;
    QGridLayout *figureLayout;

    QLabel* labelStart;

    QWidget *centralWidget;
    QWidget* mainGameWidget;
    QBoard *gameBoard;

    int size;

public slots:
    void slt_gameOver();

protected:
    virtual void keyPressEvent(QKeyEvent *pe);
//    virtual void paintEvent(QPaintEvent *event);


private:
    Ui::GameCollect *ui;
};
#endif // GAMECOLLECT_H
