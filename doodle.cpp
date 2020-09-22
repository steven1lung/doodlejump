#include "doodle.h"


double Doodle::dx=0;
double Doodle::dy=0;


Doodle::Doodle(QObject *parent): QObject(parent)
{
    //connect


    //set picture
    QPixmap picture(":/pic/qrc/player.png");
    setPixmap(picture.scaledToWidth(75));





/*
    //set timer
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(fall()));
    timer->start(2);*/
    move_timer = new QTimer();
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(2);


    /*
    QTimer* check_ground_timer = new QTimer();
    connect(check_ground_timer,SIGNAL(timeout()),this,SLOT(check_hit_ground()));
    check_ground_timer->start(2);
    jump_timer = new QTimer();
    connect(jump_timer,SIGNAL(timeout()),this,SLOT(jump_bon()));
    jump_stop_timer = new QTimer();
    connect(jump_stop_timer,SIGNAL(timeout()),this,SLOT(jump_stop()));



*/

    tryd=new QTimer();
    connect(tryd,SIGNAL(timeout()),this,SLOT(try_()));
    tryd->start(10);


    fly=new QTimer();
    connect(fly,SIGNAL(timeout()),this,SLOT(fly_up()));
    fly_5sec=new QTimer();
    connect(fly_5sec,SIGNAL(timeout()),this,SLOT(fly_stop()));

    shield_timer=new QTimer();
    connect(shield_timer,SIGNAL(timeout()),this,SLOT(shield_stop()));








}

void Doodle::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_P&&!event->isAutoRepeat()){
        if(!pause){
            move_timer->stop();
            tryd->stop();
            fly_5sec->stop();
            pause=1;
            if(shield_on) shield_timer->stop();
            }


        else if(pause){
            move_timer->start(2);
            tryd->start(10);
            fly_5sec->start(2000);
            pause=0;
            if(shield_on) shield_timer->start(5000);
        }
    }


    if(event->key()==Qt::Key_Left){
        if(x()<=-80) setPos(400,y());
        else LmoveFlag=1;
    }
    else if(event->key()==Qt::Key_Right){
        if(x()>=400) setPos(-80,y());
        else RmoveFlag=1;
    }

    if(event->key()==Qt::Key_Space&&!event->isAutoRepeat()){

        Bullet *bullet = new Bullet();
        bullet->setPos(x()+30,y());
        scene()->addItem(bullet);
        bullet_list.push_back(bullet);


    }

}

void Doodle::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left) LmoveFlag=0;
    else if(event->key()==Qt::Key_Right) RmoveFlag=0;

}

void Doodle::jump()
{
    jump_index=0;
//    jumpFlag=1;

    jump_timer->start(2);
    jump_stop_timer->start(600);
}

double Doodle::get_Y()
{
    return y();
}

void Doodle::set_original()
{
    QPixmap picture(":/pic/qrc/player.png");
    setPixmap(picture.scaledToWidth(75));
}

void Doodle::set_rocket()
{
    QPixmap picture(":/pic/qrc/playerrocket.png");
    setPixmap(picture.scaledToWidth(75));
}

void Doodle::doodle_fly()
{
    rocketing=1;
    jumpFlag=1;
    set_rocket();
//    fly->start(2);
    fly_5sec->start(2400);
    dy=-50;

}

void Doodle::set_shield()
{
    QPixmap fc(":/pic/qrc/forcefield.png");
    setPixmap(fc.scaledToWidth(75));

}

void Doodle::shield()
{

    set_shield();
    shield_on=1;
    shield_timer->start(10000);

}


void Doodle::fall()
{

    if(y()<=750-75&&!jumpFlag)
        setPos(x(),y()+1.5);


}

void Doodle::move()
{
    if(LmoveFlag==1)
        setPos(x()-1,y());
    else if(RmoveFlag==1)
        setPos(x()+1,y());
}

void Doodle::jump_bon()
{
    double distance[4]={2,0.75,0.4,0.2};
    int static i=0;
    if(jumpFlag){
        jump_index++;
        if(jump_index<100) i=0;
        else if(jump_index<150) i=1;
        else if(jump_index<250) i=2;
        else i=3;
//       qDebug()<<jump_index;
        setPos(x(),y()-distance[i]);

    }

}

void Doodle::check_hit_ground()
{
    if(y()>=750-75&&!jumpFlag){
        jump();
    }

}

void Doodle::jump_stop()
{
//    jumpFlag=0;
    jump_stop_timer->stop();
}

void Doodle::shield_stop()
{
    shield_on=0;
    set_original();

}

void Doodle::try_()
{
    for(int i=0;i<bullet_list.length();i++){
        if(bullet_list.at(i)->y()<0) bullet_list.remove(i);
    }

    dy+=0.2;
    setPos(x(),y()+dy);
    if(y()>=650-75) {
        if(!life) if(!rocketing) if(!shield_on) emit die();
        dy=-10;
    }
       if(dy>10) jumpFlag=0;
       else if (dy<0) jumpFlag=1;

}

void Doodle::fly_up()
{


}

void Doodle::fly_stop()
{
    set_original();
    fly->stop();
    rocketing=0;
}

