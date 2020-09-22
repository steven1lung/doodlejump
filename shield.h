#ifndef SHIELD_H
#define SHIELD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>


class Shield : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Shield();


signals:

public slots:
};

#endif // SHIELD_H
