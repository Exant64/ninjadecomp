#include <NinjaDev.h>

void njSetFadeColor(Uint32 c)
{
    KMPACKEDARGB argb;
    argb.dwPacked = c;
    kmSetFogTableColor(argb);
}