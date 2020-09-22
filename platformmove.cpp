#include "platformmove.h"
#include <QDebug>
PlatformMove::PlatformMove()
{
    type=2;
    QPixmap pic(":/pic/qrc/board-2.png");
    setPixmap(pic.scaledToWidth(100));

    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(around()));
    timer->start(5);

    dir = new QTimer();
    connect(dir,SIGNAL(timeout()),this,SLOT(change_dir()));
    dir->start(2000);


    QTime t;
    t=QTime::currentTime();
    qsrand(static_cast<uint>((t.msec()+t.second()*1000)));



    direction=qrand()%2;

    monster_gen=1;

}

void PlatformMove::move()
{
    around();

}

void PlatformMove::pause()
{
    dir->stop();
    timer->stop();
}

void PlatformMove::start()
{
    timer->start(5);
    dir->start(2000);
}

void PlatformMove::around()
{

        if(!direction)
            setX(x()+0.5);
        else setX(x()-0.5);


}

void PlatformMove::change_dir()
{
    (direction)?direction=0:direction=1;
}




