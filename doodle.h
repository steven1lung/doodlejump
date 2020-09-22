#ifndef DOODLE_H
#define DOODLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QVector>
#include <QTimer>
#include <QPixmap>
#include <QtGlobal>
#include "bullet.h"
#include "bomb.h"



class Doodle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Doodle(QObject *parent = nullptr);

//    QGraphicsPixmapItem *bullet;
    bool jumpFlag=0;
    bool LmoveFlag=0;
    bool RmoveFlag=0;
    bool rocketing=0;
    bool pause=0;
    bool shield_on=0;
    bool life=1;
    int jump_index;
    QTimer* jump_timer;
    QTimer* jump_stop_timer;
    QVector <Bullet*> bullet_list;
    QTimer* move_timer;
    QTimer* tryd;
    QTimer* fly;
    QTimer* fly_5sec;
    QTimer* shield_timer;



    double static y_give;

    double static dy,dx;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void shoot();
    void jump();
    double get_Y();
    void set_original();
    void set_rocket();
    void doodle_fly();
    void set_shield();
    void shield();



signals:
    void bounce();
    void die();


public slots:
    void fall();
    void move();
    void jump_bon();
    void check_hit_ground();
    void jump_stop();
    void shield_stop();
    //void bullet_move();

    void try_();
    void fly_up();
    void fly_stop();


};

#endif // DOODLE_H
