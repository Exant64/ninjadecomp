#include <NinjaDev.h>

void njScalorARGB(NJS_ARGB *dst, NJS_ARGB *src, float mul)
{
  dst->a = src->a * mul;
  dst->r = src->r * mul;
  dst->g = src->g * mul;
  dst->b = src->b * mul;
}

void njSetLightColor(NJS_LIGHT_PTR pLight, float r, float g, float b)
{
    pLight->attr.argb.r = r;
    pLight->attr.argb.g = g;
    pLight->attr.argb.b = b;
    njScalorARGB(&pLight->ltcal.atten, &pLight->attr.argb, pLight->ltcal.intns);
    njScalorARGB(&pLight->ltcal.spc, &pLight->ltcal.atten, pLight->attr.ispc);
    njScalorARGB(&pLight->ltcal.dif, &pLight->ltcal.atten, pLight->attr.idif);
    njScalorARGB(&pLight->ltcal.amb, &pLight->ltcal.atten, pLight->attr.iamb);
}