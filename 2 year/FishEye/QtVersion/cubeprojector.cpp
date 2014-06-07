#include "cubeprojector.h"

void cubeProjector::Project(double &x, double &y, double phi, double psi)
{
    if (!computAngle(x, y, angle))
    {
        x = 0;
        y = 0;
        return;
    }

        Vec2f point; point.x = 0; point.y = 0;

        vec = TopCoordinate(angle);

        Angle2f turnAngle; turnAngle.xy = phi; turnAngle.xz = psi;// угол направления взгляда
        turn(turnAngle, vec);
        VecToAngle(vec, angle);

        normaAngle(angle); // нормализует угол
        if (abs(vec.x) < 1 && abs(vec.y) < 1)
        {
                point = pointTopBottom(vec);
                x = point.x;
                y = point.y;
                return;
        }
        else
        {
                if	(angle.xy < M_PI/4)		point = pointFront(angle);
                else if	(angle.xy < 3 * M_PI / 4)	point = pointRight(angle);
                else if	(angle.xy < 5 * M_PI / 4)	point = pointBack(angle);
                else					point = pointLeft(angle);
                x = point.x; y = point.y; return;
        }
}
