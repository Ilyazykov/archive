#include "mirrorprojector.h"

void mirrorProjector::Project(double &x, double &y, double phi, double psi)
{
    x = 1.0 - x;
}
