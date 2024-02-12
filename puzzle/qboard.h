#ifndef QBOARD_H
#define QBOARD_H

#include <QWidget>
#include <qboardlabel.h>
#include <QVector>
#include <QKeyEvent>


class QBoard : public QWidget
{
    Q_OBJECT
public:
    explicit QBoard(QWidget *parent);
    void InitLabels(qint32 size);
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void changeLabels(QBoardLabel* lbl);
    void changeLabelsInColumns();
    void mix();
    void checkEnd();

signals:
    void sgl_gameOver();
//protected:
//    virtual void keyPressEvent(QKeyEvent *event);


private:
    QVector<QBoardLabel*> labelsvc;
    QBoardLabel*** label2D;
    QBoardLabel* emptyLabel;
    qint32 BoardSize;
    int size;

signals:

};

#endif // QBOARD_H
