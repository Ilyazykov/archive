#ifndef ORTHOPROJECTOR_H
#define ORTHOPROJECTOR_H
#include "iprojector.h"

class orthoProjector : public IProjector
{
public:
    void Project(double &x, double &y, double phi, double psi);

    void VecToAngle2(const Vec3f& vec, Angle2f &angle)
    {
        angle.xy = atan2(vec.x,vec.y);
        float temp = sqrt(vec.y*vec.y+vec.x*vec.x);
        angle.xz = atan(1/temp);
        if (vec.z<0) angle.xz = -angle.xz;
    }
};

#endif // ORTHOPROJECTOR_H
