#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //setup scene
    setWindowTitle("CovidJump");
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,450,650);
    QPixmap bg(":/pic/qrc/background.png");
    scene->setBackgroundBrush(bg);

    //connect
    connect(this,SIGNAL(die()),this,SLOT(game_over()));


    //new
    ran=new QRandomGenerator();


    //add platforms
    QTime t;
    t=QTime::currentTime();
    qsrand(static_cast<uint>((t.msec()+t.second()*1000)));




    platform_num=6;
    for(int num=0;num<platform_num;num++){
        Platform* plat;
        int choose=ran->bounded(4);
        switch (choose) {
        case 0:{
            plat=new Platform();
            break;
        }
        case 1:{
            plat = new PlatformMove();
            break;
        }
        case 2:{
            plat = new PlatformCollapse();
            break;
        }
        case 3:{
            plat = new PlatformDown();
            break;
        }
        default:{
            plat=new Platform();
        }
        }

        scene->addItem(plat);
        plat->setPos(ran->bounded(350),ran->bounded(150*(num-1),150*num));
        platform.push_back(plat);
        plat->move();
    }














    //add player
    doodle = new Doodle(this);
    scene->addItem(doodle);
    doodle->setPos(0,650-75);
    connect(doodle,SIGNAL(die()),this,SLOT(game_over()));




    //set player focus
    doodle->setFlag(QGraphicsItem::ItemIsFocusable);
    doodle->setFocus();




//    if(!doodle->jumpFlag && doodle->collidesWithItem(plat)){
//        qDebug()<<"bounce";
//    }

    QTimer* bounce_timer=new QTimer();
    connect(bounce_timer,SIGNAL(timeout()),this,SLOT(check_bounce()));
    bounce_timer->start(2);

    QTimer* always_timer=new QTimer();
    connect(always_timer,SIGNAL(timeout()),this,SLOT(always_on()));
    always_timer->start(10);


    timer_prop=new QTimer(this);
    timer_prop->start(10000);
//    connect(timer_prop,SIGNAL(timeout()),this,SLOT(generatebomb2()));








    QTimer* bomb_timer=new QTimer();
    connect(timer_prop,SIGNAL(timeout()),this,SLOT(generatebomb2()));
    bomb_timer->start(7000);
    timer_prop=bomb_timer;




    QTimer* check_lose=new QTimer();
    connect(check_lose,SIGNAL(timeout()),this,SLOT(check_lose()));
    check_lose->start(10);
    //add features

    QPixmap ppic(":/pic/qrc/pause.png");
    pause_pic=new QLabel(this);
    pause_pic->setPixmap(ppic.scaledToWidth(100));
    pause_pic->setGeometry(175,225,100,100);
    pause_pic->hide();


    QPixmap pic2(":/pic/qrc/background2.png");
    score_bg=new QLabel(this);
    score_bg->setPixmap(pic2);
    score_bg->setGeometry(0,0,450,90);

    QFont font("Chilanka",40);
    score_show=new QLabel(this);
    score_show->setText(QString::number(score));

    score_show->setFont(font);
    score_show->setGeometry(280,0,200,100);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_bounce()
{
    for(int i=0;i<platform.length();i++)
        if(!doodle->jumpFlag && doodle->collidesWithItem(platform[i])){
            doodle->dy=-10;
            if(platform[i]->type==1){
                platform[i]->setPos(ran->bounded(350),0);

            }

        }
//    QList<QGraphicsItem*> collide=collidingItems();
//    for(int i=0;i<collide.length();i++){
//        if(typeid (*(collide[i]))==typeid (Monster)){
//            delete  collide[i];
//            delete this;
//            return;
//        }
//    }




}

void MainWindow::always_on()
{
    if(doodle->pause){
        //later
        pause_pic->show();
        for(auto i:platform) i->pause();
        for(auto i:doodle->bullet_list) i->pause();
        for(auto i:bomb) i->pause();
        for(auto i:rocket) i->pause();
        timer_prop->stop();
    }
    else{
        pause_pic->hide();
        for(auto i:platform) i->start();
        for(auto i:doodle->bullet_list) i->start();
        for(auto i:bomb) i->startgo();
        for(auto i:rocket) i->start();
        timer_prop->start(7000);
    }


    if(doodle->dy<1) doodle->jumpFlag=1;
    else doodle->jumpFlag=0;

    if(doodle->y()<h){
        if(doodle->dy<0) score+=-doodle->dy;
        else score+=doodle->dy;
        score_show->setText(QString::number(score));


        doodle->setY(h);

        for(auto i:platform){
            i->setY(i->y()-doodle->dy);
            if(i->y()>750){
                i->setPos(ran->bounded(350),0);
//                int choose =ran->bounded(3);
                generate_mons();

                doodle->life=0;
            }

        }
        for(int i=0;i<monster.length();i++){
            monster.at(i)->setY(monster.at(i)->y()-doodle->dy);
            if(monster.at(i)->y()>650){
                monster.remove(i);
            }
        }
        for(int i=0;i<rocket.length();i++){
            rocket.at(i)->setY(rocket.at(i)->y()-doodle->dy);
            if(rocket.at(i)->y()>650) rocket.remove(i);
        }
        for(int i=0;i<shield.length();i++){
            shield.at(i)->setY(shield.at(i)->y()-doodle->dy);
            if(shield.at(i)->y()>700) shield.remove(i);
        }
        for(int i=0;i<bomb.length();i++){
            bomb.at(i)->setY(bomb.at(i)->y()-doodle->dy);
        }
    }
}

void MainWindow::game_over()
{
//    pause_pic->show();
    for(auto i:platform) i->pause();
    for(auto i:doodle->bullet_list) i->pause();
    for(auto i:bomb) i->pause();
    for(auto i:rocket) i->pause();
    timer_prop->stop();
    temp=score;
    int static i=0;
    if(!i){
        QPixmap end(":/pic/qrc/background-end.png");
        QGraphicsScene* sceneE=new QGraphicsScene();
        sceneE->setSceneRect(0,70,450,750);
        sceneE->setBackgroundBrush(end);
        score_bg->hide();
        score_show->hide();
        ui->graphicsView->setScene(sceneE);
        ++i;
        QFont font("Chilanka",30);
        QLabel *label=new QLabel(this);

        label->setGeometry(70,150,350,550);
        label->setFont(font);
        label->setText("\n\n\nCOVID-19 Has Killed :\n\n"+QString::number(temp)+"\n\nPeople");
        label->show();


    }
}

void MainWindow::generate_mons()
{
    int choose=ran->bounded(10);
    if(choose==0){
        //add monster
        Monster* mon=new Monster();
        monster.push_back(mon);
        scene->addItem(mon);
        int x=ran->bounded(platform_num);
        while(platform[x]->type!=0) x=ran->bounded(platform_num);

        mon->setPos(platform[x]->x()+18,platform[x]->y()-35);
    }
    else if(choose==1){
        if(ran->bounded(3)==0){
            Rocket* roc=new Rocket(this);
            rocket.push_back(roc);
            scene->addItem(roc);
            int x=ran->bounded(platform_num);
            while(platform[x]->type!=0) x=ran->bounded(platform_num);
            roc->setPos(platform[x]->x()+18,platform[x]->y()-35);
        }
    }
    else if(choose==2){
        //if(ran->bounded(2)==0){
            Shield* temp=new Shield();
            shield.push_back(temp);
            scene->addItem(temp);
            int x=ran->bounded(platform_num);
            while(platform[x]->type!=0) x=ran->bounded(platform_num);
            temp->setPos(platform[x]->x()+18,platform[x]->y()-35);
        //}
    }


}

void MainWindow::check_lose()
{
    //this below is not check lose LOL



    for(int count=0;count<doodle->bullet_list.length();count++){
        QList<QGraphicsItem*> collide=doodle->bullet_list[count]->collidingItems();
        for(int i=0;i<collide.length();i++){
            if(typeid (*(collide[i]))==typeid (Bomb)){
                collide[i]->hide();
                scene->removeItem(doodle->bullet_list.at(i));
                doodle->bullet_list.remove(count);
                break;
//                delete  collide[i];
//                delete this;
//                return;
            }
        }
    }









    QList<QGraphicsItem*> collide_bomb=doodle->collidingItems();
    for(int i=0;i<collide_bomb.length();i++){
        if(typeid (*(collide_bomb[i]))==typeid (Bomb)&&doodle->rocketing==0&&doodle->shield_on==0)
            game_over();
        else if(typeid (*(collide_bomb[i]))==typeid (Rocket)&&doodle->rocketing==0){
            //go up
            doodle->doodle_fly();
        }
    }
    if(!doodle->shield_on){
        for(int i=0;i<shield.length();i++){
            QList<QGraphicsItem*> collide_shield=shield.at(i)->collidingItems();
            for(int x=0;x<collide_shield.length();x++){
                if(typeid (*(collide_shield.at(i)))==typeid (Doodle)&&doodle->rocketing==0){
                    doodle->shield();

                    shield.at(i)->hide();

                    break;
                }
            }
        }
    }




    for(int i=0;i<monster.length();++i){
        if(doodle->collidesWithItem(monster.at(i))&&doodle->rocketing==0&&doodle->shield_on==0)
            game_over();
    }
}

void MainWindow::generate_bomb()
{
//    qDebug()<<"bomb!";
//    int x=ran->bounded(375);
//    Bomb *b=new Bomb();
//    bomb.push_back(b);
//    scene->addItem(b);
//    b->setPos(x,0);
//    for(int i=0;i<bomb.length();i++)
//        if(bomb.at(i)->y()>650) {



//        }
}

void MainWindow::generate_rocket()
{
    Rocket* roc=new Rocket(this);
    rocket.push_back(roc);
    scene->addItem(roc);
}

void MainWindow::generatebomb2()
{
    //will work to here
    int x=ran->bounded(375);
    Bomb *b=new Bomb();
    scene->addItem(b);
//    b->show();
    bomb.push_back(b);

    b->setPos(x,0);

    for(int i=0;i<bomb.length();i++){
        if(bomb.at(i)->y()>650) {
            scene->removeItem(bomb.at(i));
            bomb.remove(i);

        }
    }
}



