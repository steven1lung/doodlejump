#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include "monster.h"
#include <QVector>
#include "bomb.h"

class Bullet : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Bullet();
    void pause();
    void start();

    QTimer *timer;
    QTimer* self;

signals:


public slots:
    void move();
    void delete_self();

};

#endif // BULLET_H
