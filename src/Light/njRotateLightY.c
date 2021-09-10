#include <NinjaDev.h>

void njRotateLightY(NJS_LIGHT_PTR pLight, Angle ang)
{
    njRotateY(pLight->mtrx,ang);
}