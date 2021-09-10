#include <NinjaDev.h>

void njSetFogColor(Uint32 c)
{
    KMPACKEDARGB argb;
    argb.dwPacked = c;
    kmSetFogTableColor(argb);
}