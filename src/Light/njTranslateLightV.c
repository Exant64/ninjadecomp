#include <NinjaDev.h>


void njTranslateLightV(NJS_LIGHT_PTR pLight, NJS_VECTOR* vec)
{
    njTranslateV(pLight->mtrx, vec);
}