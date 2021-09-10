#include <NinjaDev.h>

void njExecuteFade(Float f)
{
    NJS_FOG_TABLE fog;
    float* pF = fog;
    do
    {
        *pF = f;
    } while (pF < &fog[128]);
    kmSetFogTable(fog);
}