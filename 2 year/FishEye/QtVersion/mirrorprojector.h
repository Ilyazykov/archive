#ifndef MIRRORPROJECTOR_H
#define MIRRORPROJECTOR_H
#include "iprojector.h"

class mirrorProjector : public IProjector
{
public:
    void Project(double &x, double &y, double phi, double psi);
};

#endif // MIRRORPROJECTOR_H
