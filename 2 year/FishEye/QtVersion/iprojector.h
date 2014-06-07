#ifndef IPROJECTOR_H
#define IPROJECTOR_H

#define _USE_MATH_DEFINES
#include <QString>
#include <QPointF>
#include <cmath>

struct Angle2f
{
    float xy;
    float xz;
};

struct Vec2f
{
    float x;
    float y;
};

struct Vec3f
{
    float x;
    float y;
    float z;
};

class IProjector
{
public:
    virtual void Project(double &x, double &y, double phi, double psi) = 0;

    float abs(float num)
    {
        return (num>0)?num:(-num);
    }
    bool computAngle(const float &x, const float &y, Angle2f &angle)
    {
            float realX = y - 0.5f;
            float realY = x - 0.5f;
            float temp = sqrt(realX*realX+realY*realY);
            if (temp > 0.5f) return false;

            angle.xy = atan2(realY, realX);

            angle.xz = M_PI*(0.5 - temp);

            return true;
    }
    Vec3f TopCoordinate(const Angle2f &angle)
    {
        Vec3f vec;
        vec.y = abs(1/( tan(angle.xz)*sqrt(tan(angle.xy)*tan(angle.xy)+1)));
        vec.x = abs(tan(angle.xy)/(tan(angle.xz)*sqrt(tan(angle.xy)*tan(angle.xy)+1)));

        if (sin(angle.xy) < 0)
        {
            vec.x = -vec.x;
        }

        if (cos(angle.xy) < 0)
        {
            vec.y = -vec.y;
        }

        if (sin(angle.xz)>0) vec.z = 1;
        else vec.z = -1;

        return vec;
    }
    void turn(Angle2f turnAngle, Vec3f& vec)
    {
            float x = vec.x;	float y = vec.y;	float z = vec.z;

            vec.y = y*cos(turnAngle.xz) + z*sin(turnAngle.xz);
            vec.z = -y*sin(turnAngle.xz) + z*cos(turnAngle.xz);

            x = vec.x;	y = vec.y;	z = vec.z;

            vec.x = x*cos(turnAngle.xy) - y*sin(turnAngle.xy);
            vec.y = x*sin(turnAngle.xy) + y*cos(turnAngle.xy);


            float lol;
            if (vec.z > 0) lol = 1/vec.z;
            else lol = -1/vec.z;
            vec.x *= lol;
            vec.y *= lol;
            vec.z *= lol;
    }
    void VecToAngle(const Vec3f& vec, Angle2f &angle)
    {
            angle.xy = atan(vec.x/vec.y);
            if (vec.y<0) angle.xy += M_PI;
            float temp = sqrt(vec.y*vec.y+vec.x*vec.x);
            angle.xz = atan(1/temp);
            if (vec.z<0) angle.xz += M_PI;
    }
    void normaAngle(Angle2f &angle)
    {
            while (angle.xz < M_PI/2) angle.xz +=M_PI*2;
            while (angle.xz >= 2*M_PI+M_PI/2) angle.xz -=M_PI*2;

            if (angle.xz > M_PI/2+M_PI)
            {
                    angle.xz = M_PI - angle.xz;
                    angle.xy += M_PI*2;
            }

            while (angle.xy >= 7 * M_PI / 4) angle.xy -= M_PI*2;
            while (angle.xy < - M_PI / 4) angle.xy += M_PI*2;
    }
};

#endif // IPROJECTOR_H
