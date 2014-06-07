#include "draw.h"

void draw::drawPicture(QImage* img)
{
    QPainter painter(&pic);
    painter.begin(img);
    painter.drawImage(0, 0, *img);
    painter.end();

    emit drawLabel(pic);
}
