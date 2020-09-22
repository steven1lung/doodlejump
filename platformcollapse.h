#ifndef PLATFORMCOLLAPSE_H
#define PLATFORMCOLLAPSE_H

#include <QObject>
#include "platform.h"

class PlatformCollapse:public Platform
{
Q_OBJECT
public:
    PlatformCollapse();
    void move();
    void pause();
    void start();

};

#endif // PLATFORMCOLLAPSE_H
