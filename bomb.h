#ifndef BOMB_H
#define BOMB_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsScene>


class Bomb : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bool stop=0;
    explicit Bomb();
    QTimer* timer_b;
    void pause();
    void startgo();
    double dy=0;
    bool destructive=1;

signals:

public slots:
    void fly();
};

#endif // BOMB_H
