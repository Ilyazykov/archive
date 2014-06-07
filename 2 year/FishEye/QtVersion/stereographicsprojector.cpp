#include "stereographicsprojector.h"

void stereographicsProjector::Project(double &x, double &y, double phi, double psi)
{
    Angle2f angle;
    if (computAngle(x, y, angle)) // нашёл углы на сфере без поворота
    {
        Vec3f vec = TopCoordinate(angle);
        Angle2f turnAngle; turnAngle.xy = phi; turnAngle.xz = psi;
        turn(turnAngle, vec);
        VecToAngle1(vec, angle);

        //normaAngle(angle);

        angle.xz = -angle.xz + M_PI/2;

        double step = (0.5*angle.xz)/(M_PI);

        x = sin(angle.xy)*step;
        y = cos(angle.xy)*step;

        x+=0.5;
        y+=0.5;        
    }
}
