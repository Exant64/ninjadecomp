#include <NinjaDev.h>

void njTranslateLight(NJS_LIGHT_PTR pLight, Float x, Float y, Float z)
{
    njTranslate(pLight->mtrx, x,y,z);
}