#ifndef PLATFORMMOVE_H
#define PLATFORMMOVE_H

#include <QObject>
#include "platform.h"
#include <QTimer>
#include <QTime>

class PlatformMove : public Platform
{
    Q_OBJECT
public:
    explicit PlatformMove();
    void move();
    QTimer* timer;
    bool direction;
    int go=0;
    void pause();
    void start();

    QTimer* dir;


signals:

public slots:
    void around();
    void change_dir();

};

#endif // PLATFORMMOVE_H
