#include <NinjaDev.h>

void njRotateLightXYZ(NJS_LIGHT_PTR pLight, Angle x, Angle y, Angle z)
{
    njRotateXYZ(pLight->mtrx,x,y,z);
}