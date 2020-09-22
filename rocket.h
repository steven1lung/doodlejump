#ifndef ROCKET_H
#define ROCKET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
class Rocket : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Rocket(QObject *parent = nullptr);
    QTimer* timer;

    void pause();
    void start();

signals:

public slots:
    void check();
};

#endif // ROCKET_H
