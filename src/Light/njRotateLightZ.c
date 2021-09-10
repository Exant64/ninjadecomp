#include <NinjaDev.h>

void njRotateLightZ(NJS_LIGHT_PTR pLight, Angle ang)
{
    njRotateZ(pLight->mtrx,ang);
}