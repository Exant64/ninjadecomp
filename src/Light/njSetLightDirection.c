#include <NinjaDev.h>

void njSetLightDirection(NJS_LIGHT_PTR pLight, Float x, Float y, Float z)
{
  pLight->vctr.x = x;
  pLight->vctr.y = y;
  pLight->vctr.z = z;
  njUnitVector(&pLight->vctr);
  pLight->ltcal.lvctr = pLight->vctr;
}