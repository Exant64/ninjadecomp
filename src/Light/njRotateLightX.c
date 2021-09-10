#include <NinjaDev.h>

void njRotateLightX(NJS_LIGHT_PTR pLight, Angle ang)
{
    njRotateX(pLight->mtrx,ang);
}