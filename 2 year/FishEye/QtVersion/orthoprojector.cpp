#include "orthoprojector.h"

void orthoProjector::Project(double &x, double &y, double phi, double psi)
{
    Angle2f angle;

    if (!computAngle(x, y, angle))
    {
        x = 0;
        y = 0;
        return;
    }

    Vec3f vec = TopCoordinate(angle);
    Angle2f turnAngle; turnAngle.xy = phi; turnAngle.xz = psi;
    turn(turnAngle, vec); // нашёл вектор после поворота
    VecToAngle2(vec, angle); // нашёл углы после поворота

    x = (angle.xy+M_PI)/(2*M_PI);
    y = 1 - (angle.xz+M_PI/2)/(M_PI);
}
