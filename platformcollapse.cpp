#include "platformcollapse.h"

PlatformCollapse::PlatformCollapse()
{
    type=1;
    QPixmap pic(":/pic/qrc/board-1.png");
    setPixmap(pic.scaledToWidth(100));
    monster_gen=0;
}

void PlatformCollapse::move()
{

}

void PlatformCollapse::pause()
{

}

void PlatformCollapse::start()
{

}



