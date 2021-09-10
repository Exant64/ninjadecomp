#include <NinjaDev.h>

void njSetUserLight(NJS_LIGHT_PTR pLight, NJF_LIGHT_FUNC func)
{
    pLight->attr.func = func;
}