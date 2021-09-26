#include <NinjaDev.h>
extern PKMDWORD njEndModifier(PKMDWORD);
PKMDWORD njCnkModPolygon(Uint16* plist, NJS_CNK_MOD_BUF* buf, Uint16 val, PKMDWORD sq)
{
    PKMDWORD pSQ = sq;
    Uint16 count;
    int calc;
    _builtin_prefetch(plist + 3);
    count = val & 0x3FFF;
    calc = ((val >> -0xE) & 3) << 1;

    _nj_draw_polygon_ += count * 3;
    _nj_calc_polygon_ += count * 3;

    do
    {
        float* tri1 = (float*)&buf[*plist++];
        float* tri2 = (float*)&buf[*plist++];
        float* tri3 = (float*)&buf[*plist++];
        float x,y,z;
        _builtin_prefetch(tri1);
        _builtin_prefetch(tri2);
        _builtin_prefetch(tri3);

        *pSQ = KMY_PARAM_ENDOFSTRIP;
        pSQ += 4;

        x = *tri1++;
        y = *tri1++;
        z = *tri1;
        *(float*)pSQ-- = z;
        *(float*)pSQ-- = y;
        *(float*)pSQ-- = x;
        pSQ += 6;

        x = *tri2++;
        y = *tri2++;
        z = *tri2;
        *(float*)pSQ-- = z;
        *(float*)pSQ-- = y;
        *(float*)pSQ-- = x;
        x = *tri3++; //fmov.s  @r6+, fr4
        pSQ += 4;        //add #16, r14 
        *(float*)pSQ-- = x; //fmov.s  fr4, @-r14
        _builtin_prefetch(pSQ); //pref    @r14

        pSQ += 3;

        x = *tri3++;
        y = *tri3;
        *(float*)(pSQ--) = y;
        *(float*)(pSQ--) = x;
        _builtin_prefetch(pSQ);

        pSQ += 8;
        (Uint8*)plist += calc;
        if(count == 2)
            pSQ = njEndModifier(pSQ);
        
        _builtin_prefetch(plist + 3);
    } while (--count);

    return pSQ;
}