#include <NinjaDev.h>

PKMDWORD BSG_0;
int isQuadTrans;
extern int* _nj_listtype_;
void njQuadTextureStart( Sint32 trans )
{
    njGetkmPointer();
    isQuadTrans = trans;
    if(trans)
    {
        Uint32 val;
        BSG_0 = NJD_GET_MAPPING_ADDRESS(_nj_parameterkm_.PrimTransPoly); //StartVertexTexTrans in njKm accesses this value too
        NJD_GET_SQ(_nj_parameterkm_.PrimTransPoly);
    }
    else
    {
        Uint32 val;

        BSG_0 = NJD_GET_MAPPING_ADDRESS(_nj_parameterkm_.OpaquePoly); // StartVertexTexOpaque
        NJD_GET_SQ(_nj_parameterkm_.OpaquePoly);
    }
}

void njQuadTextureEnd()
{
    njEndVertex(BSG_0);
    njSetkmPointer();
}

void	njSetQuadTexture( Sint32 texid, Uint32 col )
{
    int* ptr;
    njSetkmTextureNum(texid);
    {
        Uint32* ptr = (Uint32*)BSG_0;
        if(isQuadTrans)
        {
            ptr+=5;
            *(--ptr) = col;
            *(--ptr) = _nj_parameterkm_.TexturePARAMBUFFER;
            *(--ptr) = (_nj_parameterkm_.TSPPARAMBUFFER & 0xFFF7FFFF) | 0x100000;
            *(--ptr) = _nj_parameterkm_.ISPPARAMBUFFER;
        
            //PVR_CMD_SPRITE | 16_BIT | use_texture | PVR_LIST_TR_POLY | 
            *(--ptr) = (_nj_parameterkm_.GLOBALPARAMBUFFER & 0x30080) | 0xA2800009;
            _builtin_prefetch((void*)ptr);
            ptr+=8;

            _nj_listtype_ = &_nj_parameterkm_.PrimTransPoly;
            BSG_0 = ptr;
        }
        else
        {
            ptr+=5;
            *(--ptr) = col;
            *(--ptr) = _nj_parameterkm_.TexturePARAMBUFFER;
            *(--ptr) = (_nj_parameterkm_.TSPPARAMBUFFER & 0x3EFFFFF) | 0x20080000;
            *(--ptr) = _nj_parameterkm_.ISPPARAMBUFFER;
            *(--ptr) = (_nj_parameterkm_.GLOBALPARAMBUFFER & 0x30080) | 0xA0800009;
            _builtin_prefetch((void*)ptr);
            ptr+=8;

            _nj_listtype_ = &_nj_parameterkm_.OpaquePoly;
            BSG_0 = ptr;
        }
    }
}

void	njSetQuadTextureG( Sint32 gid, Uint32 col )
{
    int* ptr;
    njSetkmTextureNumG(gid);
    {
        Uint32* ptr = (Uint32*)BSG_0;
        if(isQuadTrans)
        {
            ptr+=5;
            *(--ptr) = col;
            *(--ptr) = _nj_parameterkm_.TexturePARAMBUFFER;
            *(--ptr) = (_nj_parameterkm_.TSPPARAMBUFFER & 0xFFF7FFFF) | 0x100000;
            *(--ptr) = _nj_parameterkm_.ISPPARAMBUFFER;
            *(--ptr) = (_nj_parameterkm_.GLOBALPARAMBUFFER & 0x30080) | 0xA2800009;
            _builtin_prefetch((void*)ptr);
            ptr+=8;

            _nj_listtype_ = &_nj_parameterkm_.PrimTransPoly;
            BSG_0 = ptr;
        }
        else
        {
            ptr+=5;
            *(--ptr) = col;
            *(--ptr) = _nj_parameterkm_.TexturePARAMBUFFER;
            *(--ptr) = (_nj_parameterkm_.TSPPARAMBUFFER & 0x3EFFFFF) | 0x20080000;
            *(--ptr) = _nj_parameterkm_.ISPPARAMBUFFER;
            *(--ptr) = (_nj_parameterkm_.GLOBALPARAMBUFFER & 0x30080) | 0xA0800009;
            _builtin_prefetch((void*)ptr);
            ptr+=8;

            _nj_listtype_ = &_nj_parameterkm_.OpaquePoly;
            BSG_0 = ptr;
        }
    }
    
}

void njSetQuadTextureColor(Uint32 col)
{
    Uint32* ptr = (Uint32*)BSG_0;
    if(isQuadTrans)
    {
        ptr+=5;
        *(--ptr) = col;
        *(--ptr) = _nj_parameterkm_.TexturePARAMBUFFER;
        *(--ptr) = (_nj_parameterkm_.TSPPARAMBUFFER & 0xFFF7FFFF) | 0x100000;
        *(--ptr) = _nj_parameterkm_.ISPPARAMBUFFER;
        *(--ptr) = (_nj_parameterkm_.GLOBALPARAMBUFFER & 0x30080) | 0xA2800009;
        _builtin_prefetch((void*)ptr);
        ptr+=8;

        _nj_listtype_ = &_nj_parameterkm_.PrimTransPoly;
        BSG_0 = ptr;
    }
    else
    {
        ptr+=5;
        *(--ptr) = col;
        *(--ptr) = _nj_parameterkm_.TexturePARAMBUFFER;
        *(--ptr) = (_nj_parameterkm_.TSPPARAMBUFFER & 0x3EFFFFF) | 0x20080000;
        *(--ptr) = _nj_parameterkm_.ISPPARAMBUFFER;
        *(--ptr) = (_nj_parameterkm_.GLOBALPARAMBUFFER & 0x30080) | 0xA0800009;
        _builtin_prefetch((void*)ptr);
        ptr+=8;

        _nj_listtype_ = &_nj_parameterkm_.OpaquePoly;
        BSG_0 = ptr;
    }
}

//ill be honest, i have no clue if these are correct but i hope they are
//these were a pain in the ass to decomp

//called PVR_PACK_16BIT_UV in KOS
typedef union NJS_QUAD_UV{
    float f[2];
    int i[2];
} NJS_QUAD_UV;

void njDrawQuadTexture( NJS_QUAD_TEXTURE *q, Float z )
{
    float x1 = *(((float*)q)++);
    float y1 = *(((float*)q)++);
    float x2 = *(((float*)q)++);
    float y2 = *(((float*)q)++);
    float* pkm = (float*)BSG_0;
    //pvr_sprite_txr_t
    pkm += 8;
    *(--pkm) = x2;
    *(--pkm) = z;
    *(--pkm) = y1;
    *(--pkm) = x2;
    *(--pkm) = z;
    *(--pkm) = y1;
    *(--pkm) = x1;
    *(int*)(--pkm) = 0xFFFF0000;
    _builtin_prefetch(pkm);
    pkm += 16;
    {
        //might be wrong, its supposed to be TOFLOAT16, probably macro but dont know how to do it
        *(Uint32*)(--pkm) = (Uint32)((*(((Uint32*)q)++) & 0xFFFF0000) | (*(((Uint32*)q)++) >> 16));
        *(Uint32*)(--pkm) = (Uint32)((*(((Uint32*)q)) >> 16) | (*(((Uint32*)q)++) & 0xFFFF0000));//TOFLOAT16(u2, v1);
        *(Uint32*)(--pkm) = (Uint32)((*(((Uint32*)q++)) & 0xFFFF0000) | (*(((Uint32*)q)) >> 16));
    }
    pkm--;
    *(--pkm) = y2;
    *(--pkm) = x1;
    *(--pkm) = z;
    *(--pkm) = y2;
    _builtin_prefetch(pkm);
    BSG_0 = (PKMDWORD)(pkm + 16);
}

void njDrawQuadTextureEx( NJS_QUAD_TEXTURE_EX* q)
{
     float x = *(((float*)q)++);
    float y = *(((float*)q)++);
    float z = *(((float*)q)++);
    float vx1 = *(((float*)q)++);
    float vy1 = *(((float*)q)++);
    float vx2 = *(((float*)q)++);
    float vy2 = *(((float*)q)++);
    float* pkm = (float*)BSG_0;
    NJS_QUAD_UV uv;
    //pvr_sprite_txr_t
    pkm += 8;
    *(--pkm) = vx2 + x + vx1;
    *(--pkm) = z;
    *(--pkm) = y + vy1;
    *(--pkm) = x + vx1;
    *(--pkm) = z;
    *(--pkm) = y;
    *(--pkm) = x;
    *(int*)(--pkm) = 0xF0000000;
    _builtin_prefetch(pkm);
    ((float*)q)++;
    pkm += 16;
    {
        float u = *(((float*)q)++);
        float v = *(((float*)q)++);
        float vu1 = *(((float*)q)++);
        float vv1 = *(((float*)q)++);
        float vu2 = *(((float*)q)++);
        float vv2 = *(((float*)q));
        
        uv.f[0] = u + vu1 + vu2;
        uv.f[1] = v + vv1 + vv2;
        *(Uint32*)(--pkm) = (Uint32)(((*(Uint32*)&uv.i[0]) & 0xFFFF0000) | ((*(Uint32*)&uv.i[1] >> 16)));
        uv.f[0] = u + vu1;
        uv.f[1] = v + vv1;
        *(Uint32*)(--pkm) = (Uint32)(((*(Uint32*)&uv.i[0]) & 0xFFFF0000) | ((*(Uint32*)&uv.i[1] >> 16)));
        uv.f[0] = u;
        uv.f[1] = v;
        *(Uint32*)(--pkm) = (Uint32)(((*(Uint32*)&uv.i[0]) & 0xFFFF0000) | ((*(Uint32*)&uv.i[1] >> 16)));
    }
    pkm--; 
    *(--pkm) = y + vy2;
    *(--pkm) = x + vx2;
    *(--pkm) = z;
    *(--pkm) = vy2 + y + vy1;
    _builtin_prefetch(pkm);
    BSG_0 = (PKMDWORD)(pkm + 16);
}