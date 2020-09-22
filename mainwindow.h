#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVector>
#include <QString>
#include <QRandomGenerator>
#include <QTime>
#include <QLabel>
#include <QFont>
#include "doodle.h"
#include "bullet.h"
#include "platform.h"
#include "platformcollapse.h"
#include "platformmove.h"
#include "monster.h"
#include "bullet.h"
#include "platformdown.h"
#include "bomb.h"
#include "rocket.h"
#include "shield.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int h=250;
    int platform_num;
    int temp=0;
    int score=0;
    bool pause=0;

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Doodle *doodle;
    QVector <Platform*> platform;
    QVector <Monster*> monster;
    QVector <Bomb*> bomb;
    QVector <Rocket*> rocket;
    QVector <Shield*> shield;
    QRandomGenerator *ran;
    QLabel *score_bg;
    QLabel* score_show;
    QLabel* pause_pic;
    QTimer* timer_prop;


signals:
    void die();

public slots:
    void check_bounce();
    void always_on();
    void game_over();
    void generate_mons();
    void check_lose();
    void generate_bomb();
    void generate_rocket();
    void generatebomb2();




};

#endif // MAINWINDOW_H
