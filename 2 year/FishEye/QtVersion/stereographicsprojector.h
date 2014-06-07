#ifndef STEREOGRAPHICSPROJECTOR_H
#define STEREOGRAPHICSPROJECTOR_H
#include "iprojector.h"

class stereographicsProjector : public IProjector
{
public:
    void Project(double &x, double &y, double phi, double psi);

    void VecToAngle1(const Vec3f& vec, Angle2f &angle)
    {
        angle.xy = atan2(vec.x,vec.y);
        float temp = sqrt(vec.y*vec.y+vec.x*vec.x);
        angle.xz = atan(1/temp);
        if (vec.z<0)
        {
            angle.xz += M_PI;
            angle.xy += M_PI;
        }
    }
};

#endif // STEREOGRAPHICSPROJECTOR_H
