#include "platformdown.h"

PlatformDown::PlatformDown()
{
    direction=qrand()%2;
    type=3;
    QPixmap pic(":/pic/qrc/board-4.png");
    setPixmap(pic.scaledToWidth(100));

    QTime t;
    t=QTime::currentTime();
    qsrand(static_cast<uint>((t.msec()+t.second()*1000)));

    tmovement = new QTimer();
    connect(tmovement,SIGNAL(timeout()),this,SLOT(go_down()));
    tmovement->start(10);

    dir = new QTimer();
    connect(dir,SIGNAL(timeout()),this,SLOT(change_dir()));
    dir->start(1500);
}

void PlatformDown::move()
{

    go_down();
}

void PlatformDown::pause()
{
    tmovement->stop();
    dir->stop();
}

void PlatformDown::start()
{
    tmovement->start(10);
    dir->start(1500);
}

void PlatformDown::go_down()
{
    if(!direction)
        setY(y()+0.5);
    else setY(y()-0.5);
}

void PlatformDown::change_dir()
{
    (direction)?direction=0:direction=1;
}
