#ifndef DRAW_H
#define DRAW_H

#include <QPicture>
#include <QPainter>
#include <QImage>

class draw : public QObject
{
    Q_OBJECT

public:
    QPicture pic;
public slots:
    void drawPicture(QImage*);
signals:
    void drawLabel(QPicture);
};

#endif // DRAW_H
