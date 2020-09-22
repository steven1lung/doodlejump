#include "shield.h"

Shield::Shield() : QObject()
{
    QPixmap pic(":/pic/qrc/prop-1.png");
    setPixmap(pic.scaledToWidth(50));
}
