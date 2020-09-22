#include "bullet.h"

Bullet::Bullet() : QObject()
{

    QPixmap pic(":/pic/qrc/bullet.png");
    setPixmap(pic.scaledToWidth(20));

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(2);

    self=new QTimer();
    connect(self,SIGNAL(timeout()),this,SLOT(delete_self()));
    self->start(2000);


}

void Bullet::pause()
{

    timer->stop();
    self->stop();
}

void Bullet::start()
{
    timer->start(2);
    self->start(2000);
}

void Bullet::move()
{
//        QList<QGraphicsItem*> collide=collidingItems();
//        for(int i=0;i<collide.length();i++){
//            if(typeid (*(collide[i]))==typeid (Monster)){
////                Monster::monster.remove(i);
//                delete  collide[i];
//                delete this;
//                return;
//            }
//        }

    setPos(x(),y()-1.25);
}

void Bullet::delete_self()
{
    delete this;

}
