#include "projector.h"
//#include "mirrorprojector.h"
//#include "nullprojector.h"
//#include "stereographicprojector.h"
#include "cubeprojector.h"
#include <QImage>

IProjector * CreateProjectorByName(const char * pName)
{
        //if (strcmp(pName, "mirror") == 0)
                return new CMirrorProjector();
        //else if(strcmp(pName, "stereographic") == 0)
                return new CStereographicProjector();
        //else
    if (strcmp(pName, "cube") == 0)
        return new CCubeProjector();
    else
        return new CNullProjector();
}

int todo(char* pName, int width, int height, char* pathOpen, char* pathSave)
{
    QImage lImage;
    lImage.load(pathOpen);
    int lWidth = width;
    int lHeight = height;

    //IProjector* lProjector = CreateProjectorByName(pName);
    //lProjector->SetResolution(lWidth, lHeight);

    for (int x = 0; x < lWidth/*imgOld.dotsPerMeterX()*/; x++)
    {
        for (int y = 0; y < lHeight/*imgOld.dotsPerMeterY()*/; y++)
        {
            value = imgOld.pixel(x,y);
            imgNew.setPixel(x, y, value);
        }
    }
    //CvPoint2D32f lPoint = lProjector->Project
    //            (cvPoint2D32f(x / (float)lImageCopy.cols, y / (float)lImageCopy.rows), 0, 0);
    //lPoint.x *= lImage.cols;
    //lPoint.y *= lImage.rows;
}
