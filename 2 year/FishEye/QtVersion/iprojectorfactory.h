#ifndef IPROJECTORFACTORY_H
#define IPROJECTORFACTORY_H

#include <QLabel>
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QImage>
#include <QPainter>
#include <QRgb>

class IProjectorFactory : public QObject
{
    Q_OBJECT

private:
    int numProjectors;
    QString* nameProjectors;

    QString selectedProjector;
    int width;
    int height;
    double rotateXY;
    double rotateXZ;
    QString openPicturePath;
    QString savePicturePath;

    QImage *imgOpen;
    QImage *imgSave;

public:
    IProjectorFactory(QObject *parent = 0);
    ~IProjectorFactory();
    int getNumProjectors();
    QString getNameProjectors(int iPoint);
    void todo(void);

public slots:
    void changeRotateRight();
    void changeRotateLeft();
    void changeRotateUp();
    void changeRotateDown();
    void changeWidth(int);
    void changeHeight(int);
    void changeSelectedProjector(QString);
    void changeOpenPicturePath();
    void changeSavePicturePath();

signals:
    void imageIsChanged(QImage*);
};

#endif // IPROJECTORFACTORY_H
