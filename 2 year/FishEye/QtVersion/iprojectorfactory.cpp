#include "iprojectorfactory.h"
#include "iprojector.h"
#include "mirrorprojector.h"
#include "nullprojector.h"
#include "stereographicsprojector.h"
#include "cubeprojector.h"
#include "orthoprojector.h"

#define NUM_PROJECTORS 5
#define ROTATE_ANGLE 0.3141592653589
QString FactoryNames[NUM_PROJECTORS] = {"none", "stereographic", "ortho", "cube", "mirror"};

IProjector * CreateProjectorByName(QString pName)
{
    if (pName == "mirror")
        return new mirrorProjector();
    else if(pName == "stereographic")
        return new stereographicsProjector();
    else if (pName == "ortho")
        return new orthoProjector();
    else if (pName == "cube")
        return new cubeProjector();
    else
        return new nullProjector();
}

//=====================================================================

IProjectorFactory::IProjectorFactory(QObject *parent) :
    QObject(parent)
{
    numProjectors = NUM_PROJECTORS;
    nameProjectors = new QString [numProjectors];
    for (int i = 0; i < numProjectors; i++)
    {
        nameProjectors[i] = FactoryNames[i];
    }
    selectedProjector = nameProjectors[0];
    rotateXY = 0;
    rotateXZ = M_PI/2;
    width = 500;
    height = 500;

    imgSave = NULL;
    imgOpen = NULL;
}

IProjectorFactory::~IProjectorFactory()
{
    if (imgSave) delete imgSave;
    if (imgOpen) delete imgOpen;
}

int IProjectorFactory::getNumProjectors()
{
    return numProjectors;
}

QString IProjectorFactory::getNameProjectors(int iPoint)
{
    return nameProjectors[iPoint];
}

void IProjectorFactory::changeRotateRight()
{
    rotateXY -= ROTATE_ANGLE;
    if (imgOpen)
    {
        todo();
        emit imageIsChanged(imgSave);
    }
}

void IProjectorFactory::changeRotateLeft()
{
    rotateXY += ROTATE_ANGLE;
    if (imgOpen)
    {
        todo();
        emit imageIsChanged(imgSave);
    }
}

void IProjectorFactory::changeRotateUp()
{
    rotateXZ -= ROTATE_ANGLE;
    if (imgOpen)
    {
        todo();
        emit imageIsChanged(imgSave);
    }
}

void IProjectorFactory::changeRotateDown()
{
    rotateXZ += ROTATE_ANGLE;
    if (imgOpen)
    {
        todo();
        emit imageIsChanged(imgSave);
    }
}

void IProjectorFactory::changeWidth(int num)
{
    width = num;
    if (imgOpen)
    {
        todo();
        emit imageIsChanged(imgSave);
    }
}

void IProjectorFactory::changeHeight(int num)
{
    height = num;
    if (imgOpen)
    {
        todo();
        emit imageIsChanged(imgSave);
    }
}

void IProjectorFactory::changeSelectedProjector(QString newProjector)
{
    selectedProjector = newProjector;
    if (imgOpen)
    {
        todo();
        emit imageIsChanged(imgSave);
    }
}

void IProjectorFactory::changeOpenPicturePath()
{
    openPicturePath = QFileDialog::getOpenFileName();
    imgOpen = new QImage(openPicturePath);
    todo();
    emit imageIsChanged(imgSave);
}

void IProjectorFactory::changeSavePicturePath()
{
    savePicturePath = QFileDialog::getSaveFileName();
    imgSave->save(savePicturePath, "png");
}

void IProjectorFactory::todo()
{
    QRgb value;

    QImage *tempSave = new QImage(width+1, height+1, QImage::Format_RGB32);

    IProjector *lProjector = CreateProjectorByName(selectedProjector);

    for (int x = 1; x < width; x++)
    {
        for (int y = 1; y < height; y++)
        {
            double relationX = (double)x / (double)width;
            double relationY = (double)y / (double)height;

            lProjector->Project(relationX, relationY, rotateXY, rotateXZ);

            value = imgOpen->pixel(relationX*imgOpen->width(),
                                   relationY*imgOpen->height());

            tempSave->setPixel(x, y, value);
        }
    }

    if (imgSave) delete imgSave;
    imgSave = tempSave;
}
