#ifndef CUBEPROJECTOR_H
#define CUBEPROJECTOR_H

#include "iprojector.h"
#include <math.h>

class cubeProjector : public IProjector
{
    Angle2f angle;
    Vec3f vec;
public:
    void Project(double &x, double &y, double phi, double psi);
    Vec2f pointTopBottom(Vec3f vec)
    {
        Vec2f res;

            if (vec.z > 0)	res.x = 0.375f + vec.x/8.0f; //если верхн€€
            else res.x = 0.874f - vec.x/8.0f; //если нижн€€

            res.y = (3.0f + vec.y)/6.0f;

            return res;
    }

    void commonComput(float &x3d, float &y3d, Angle2f angle)
    {
            x3d = tan(angle.xy)/2;
            y3d = tan(angle.xz)*sqrt(tan(angle.xy)*tan(angle.xy)+1)/2;
    }

    Vec2f pointFront(Angle2f angle)
    {
        Vec2f res;

            res.x = 0.25f;		res.x += 0.125f;
            res.y = 2.0f/3.0f;	res.y += 1.0f/6.0f;

            float x3d; float y3d;
            commonComput(x3d, y3d, angle);
            x3d /= 4;
            y3d /= 3;

            res.x += x3d;
            res.y += y3d;

            return res;
    }

    Vec2f pointRight(Angle2f angle)
    {
            angle.xy -= 1 * M_PI/2;

            Vec2f res;

            res.x = 0.5f;		res.x += 0.125f;
            res.y = 2.0f/3.0f;	res.y -= 1.0f/6.0f;

            float x3d; float y3d;
            commonComput(x3d, y3d, angle);

            x3d /= 3;
            y3d /= 4;

            res.x += y3d;
            res.y -= x3d;

            return res;
    }

    Vec2f pointBack(Angle2f angle)
    {
            angle.xy -= 2 * M_PI/2;

            Vec2f res;
            res.x = 0.5f;		res.x -= 0.125f;
            res.y = 1.0f/3.0f;	res.y -= 1.0f/6.0f;

            float x3d; float y3d;
            commonComput(x3d, y3d, angle);

            x3d /= 4;
            y3d /= 3;

            res.x -= x3d;
            res.y -= y3d;

            return res;
    }

    Vec2f pointLeft(Angle2f angle)
    {
            angle.xy -= 3 * M_PI/2;

            Vec2f res;
            res.x = 0.25f;		res.x -= 0.125f;
            res.y = 1.0f/3.0f;	res.y += 1.0f/6.0f;

            float x3d; float y3d;
            commonComput(x3d, y3d, angle);

            x3d /= 3;
            y3d /= 4;

            res.x -= y3d;
            res.y += x3d;

            return res;
    }
};

#endif // CUBEPROJECTOR_H
