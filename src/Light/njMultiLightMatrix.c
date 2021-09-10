#include <NinjaDev.h>

void njMultiLightMatrix(NJS_LIGHT_PTR pLight, NJS_MATRIX* mtx)
{
    njMultiMatrix(pLight->mtrx, mtx);
}