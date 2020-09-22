#ifndef PLATFORMDOWN_H
#define PLATFORMDOWN_H

#include <QObject>
#include "platform.h"
#include <QTimer>
#include <QTime>


class PlatformDown : public Platform
{
    Q_OBJECT
public:
    explicit PlatformDown();
    void move();
    bool direction;
    void pause();
    void start();

    QTimer *tmovement;
    QTimer *dir;

signals:

public slots:
    void go_down();
    void change_dir();

};

#endif // PLATFORMDOWN_H
