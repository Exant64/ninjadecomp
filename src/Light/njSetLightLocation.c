#include <NinjaDev.h>

void njSetLightLocation(NJS_LIGHT_PTR pLight, Float x, Float y, Float z)
{
    pLight->pnt.x = x;
    pLight->pnt.y = y;
    pLight->pnt.z = z;
    pLight->ltcal.lpnt = pLight->pnt;
}