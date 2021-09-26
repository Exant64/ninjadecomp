#include <NinjaDev.h>
#include <ninjadir.h>
typedef union{
    Uint16 s[2];
    Uint32 i;
} UVConv1;
typedef union{
    float f[2];
    Uint16 s[4];
} UVConv2;
extern Uint32 _nj_direct_culling_mode_;
void *njCnkDirectTexture( Sint16 *plist, NJS_DIRECT_BUF *vbuf, Uint32 j, void *ptr,  Float div, Uint32 *vtx )
{
    UVConv1 conv1;
    UVConv2 conv2;

    Uint32 calc = ((j >> -0xE) & 3);
    Uint32 nVtx = 0;
    Uint32 calc2 = calc << 1;
    NJS_DIRECT_VERTEX* pV = (NJS_DIRECT_VERTEX*)ptr;
    j = j & 0x3FFF;
    do
    {
        Sint16 r9 = *plist++;
        Sint16 r12 = *plist++;
        NJS_DIRECT_BUF* vert = &vbuf[r12];
        
        if(r9 < 0)
        {
            r9 = -r9;
            if(_nj_direct_culling_mode_ != 0x8000000)
            {
                pV->px = vert->px;
                pV->py = vert->py;
                pV->pz = vert->pz;

                pV->nx = vert->nx;
                pV->ny = vert->ny;
                pV->nz = vert->nz;

                conv2.f[0] = div * (float)(*plist++) + 0.001953125f;
                conv2.f[1] = div * (float)(*plist++) + 0.001953125f;
                conv1.s[1] = conv2.s[1];
                conv1.s[0] = conv2.s[3];

                nVtx++;
                plist-=2;

                pV->uv = conv1.i;
                pV->param = 0xE0000000;
    
                pV++;
            }
        }

        r9 -= 2;

        pV->px = vert->px;
        pV->py = vert->py;
        pV->pz = vert->pz;
        pV->nx = vert->nx;
        pV->ny = vert->ny;
        pV->nz = vert->nz;
        conv2.f[0] = div * (float)(*plist++) + 0.001953125f;
        conv2.f[1] = div * (float)(*plist++) + 0.001953125f;
        conv1.s[1] = conv2.s[1];
        conv1.s[0] = conv2.s[3];
        nVtx++;
        pV->uv = conv1.i;
        pV->param = 0xE0000000;
        pV++;

        r12 = *plist++;
        vert = &vbuf[r12];

        conv2.f[0] = div * (float)(*plist++) + 0.001953125f;
        conv2.f[1] = div * (float)(*plist++) + 0.001953125f;
        conv1.s[1] = conv2.s[1];
        conv1.s[0] = conv2.s[3];

        do
        {
            nVtx++;

            pV->px = vert->px;
            pV->py = vert->py;
            pV->pz = vert->pz;
            pV->nx = vert->nx;
            pV->ny = vert->ny;
            pV->nz = vert->nz;
            pV->uv = conv1.i;
            pV->param = 0xE0000000;
            pV++;

            r12 = *plist++;
            vert = &vbuf[r12];

            conv2.f[0] = div * (float)(*plist++) + 0.001953125f;
            conv2.f[1] = div * (float)(*plist++) + 0.001953125f;
            conv1.s[1] = conv2.s[1];
            conv1.s[0] = conv2.s[3];

            (Uint8*)plist += calc2;
        } while (--r9);
        
        pV->px = vert->px;
        pV->py = vert->py;
        pV->pz = vert->pz;
        pV->nx = vert->nx;
        pV->ny = vert->ny;
        pV->nz = vert->nz;
        pV->uv = conv1.i;
        pV->param = 0xF0000000;
        pV++;
        nVtx++;
    } while (--j);

    *vtx = nVtx;
}