#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QVector>

class Monster : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Monster();


signals:

public slots:
    void check_bound();
};

#endif // MONSTER_H
