#ifndef NULLPROJECTOR_H
#define NULLPROJECTOR_H
#include "iprojector.h"

class nullProjector : public IProjector
{
public:
    void Project(double &x, double &y, double phi, double psi);
};

#endif // NULLPROJECTOR_H
