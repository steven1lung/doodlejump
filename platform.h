#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "monster.h"
#include <QRandomGenerator>
#include <QGraphicsScene>

class Platform : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int type=0;
    explicit Platform(QObject *parent = nullptr);
    bool monster_gen;
    Monster* mons;



    virtual void move();
    virtual void pause();
    virtual void start();

signals:

public slots:
    void monster_move();
    void generate();

};

#endif // PLATFORM_H
