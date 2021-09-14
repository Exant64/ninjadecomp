#include <NinjaDev.h>

//still unfinished

#define KM_PUNCHTHROUGH_POLYGON 4 //missing from the kamui1 headers even though its in kamui2

//struct maybe?
NJS_PARAMETERKM _nj_parameterkm_;

PKMDWORD _nj_sq_base_; 
PKMDWORD _nj_listtype_;
Uint32 _nj_TSPPARAMBUFFER_2_;
Uint32 _nj_TexturePARAMBUFFER_2_;

void njGetkmPointer()
{
    _nj_parameterkm_.GLOBALPARAMBUFFER = _nj_current_ctx_->GLOBALPARAMBUFFER;
    _nj_parameterkm_.ISPPARAMBUFFER = _nj_current_ctx_->ISPPARAMBUFFER;
    _nj_parameterkm_.TSPPARAMBUFFER = _nj_current_ctx_->TSPPARAMBUFFER;
    _nj_parameterkm_.TexturePARAMBUFFER = _nj_current_ctx_->TexturePARAMBUFFER;

    _nj_parameterkm_.OpaquePoly = _nj_vertex_buffer_.pCurrentPtr[KM_OPAQUE_POLYGON]; //opaque_polygon

    _nj_parameterkm_.OpaqueMod = _nj_vertex_buffer_.pCurrentPtr[KM_OPAQUE_MODIFIER];
    _nj_parameterkm_.TransMod = _nj_vertex_buffer_.pCurrentPtr[KM_TRANS_MODIFIER];

    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_USE_PUNCHTHROUGH)
    {
        _nj_parameterkm_.PrimTransPoly = _nj_vertex_buffer_.pCurrentPtr[KM_TRANS_POLYGON];
        _nj_parameterkm_.SecondTransPoly = _nj_vertex_buffer_.pCurrentPtr[KM_PUNCHTHROUGH_POLYGON];
    }
    else
    {
        _nj_parameterkm_.PrimTransPoly = _nj_vertex_buffer_.pCurrentPtr[KM_PUNCHTHROUGH_POLYGON];
        _nj_parameterkm_.SecondTransPoly = _nj_vertex_buffer_.pCurrentPtr[KM_TRANS_POLYGON];
    }
}

void njSetkmPointer()
{
    _nj_current_ctx_->GLOBALPARAMBUFFER = _nj_parameterkm_.GLOBALPARAMBUFFER;
    _nj_current_ctx_->ISPPARAMBUFFER = _nj_parameterkm_.ISPPARAMBUFFER;
    _nj_current_ctx_->TSPPARAMBUFFER = _nj_parameterkm_.TSPPARAMBUFFER;
    _nj_current_ctx_->TexturePARAMBUFFER = _nj_parameterkm_.TexturePARAMBUFFER;

    _nj_vertex_buffer_.pCurrentPtr[0] = _nj_parameterkm_.OpaquePoly;

    _nj_vertex_buffer_.pCurrentPtr[1] = _nj_parameterkm_.OpaqueMod;
    _nj_vertex_buffer_.pCurrentPtr[3] = _nj_parameterkm_.TransMod;

    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_USE_PUNCHTHROUGH)
    {
        _nj_vertex_buffer_.pCurrentPtr[2] = _nj_parameterkm_.PrimTransPoly;
        _nj_vertex_buffer_.pCurrentPtr[4] = _nj_parameterkm_.SecondTransPoly;
    }
    else
    {
        _nj_vertex_buffer_.pCurrentPtr[4] = _nj_parameterkm_.PrimTransPoly;
        _nj_vertex_buffer_.pCurrentPtr[2] = _nj_parameterkm_.SecondTransPoly;
    }
}

void njEndVertex(PKMDWORD pDST)
{
    *_nj_listtype_ = ((KMDWORD)pDST & 0x3FFFFFF) | *_nj_sq_base_;
}

//unfinished and missing 2p function
void njSetkmColorMode(Uint32 p)
{
    KMDWORD global = (_nj_parameterkm_.GLOBALPARAMBUFFER & 0xFDFFFF00) | (p & 0x20000FF);
    KMDWORD tsp = (_nj_parameterkm_.TSPPARAMBUFFER & 0xFFE7FFFF) | (p & 0x180000);
    KMDWORD isp = _nj_parameterkm_.ISPPARAMBUFFER;
    
    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_SHADOW)
    {
        if(_nj_control_3d_flag_ & NJD_CONTROL_3D_SHADOW_OPAQUE)
            if(p & NJD_ARC1_TRANS);

    }
    else
        global |= 0x80;

    _nj_parameterkm_.GLOBALPARAMBUFFER = global;
    _nj_parameterkm_.ISPPARAMBUFFER = isp;
    _nj_parameterkm_.TSPPARAMBUFFER = tsp;

    *_nj_color_mode_ = p;
}

Sint32 njSetkmTextureNum(Sint32 texid)
{
    return _nj_texglobal_color_;
}

Uint32 njSetkmTextureNum2p(Uint32 n)
{
    return _nj_texglobal_color_;
}

Sint32 njSetkmTextureNumG(Sint32 gid)
{
    return _nj_texglobal_color_;
}

Uint32 njSetkmTextureMemList(Uint32 n)
{
     NJS_TEXMEMLIST* mem = &_nj_texmemlist[n];

    if(_nj_current_texture == mem->globalIndex && _nj_current_texture_bank == mem->bank)
        return;

    _nj_current_texture = mem->globalIndex;
    _nj_current_texture_bank = mem->bank;

    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & 0xFFFFFFC0) | (mem->tspparambuffer & 0x3F);
    _nj_texglobal_color_ = mem->texinfo.texsurface.Type >> 16;
    _nj_parameterkm_.TexturePARAMBUFFER = mem->texparambuffer;

    return mem->texinfo.texsurface.Type;
}

void njSetkmModelAttr(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & 0x3F800FF) | (p & 0xFC07FF00);
}

void njZBufferkmMode(Uint32 p)
{
    if(p == 1)
        _nj_parameterkm_.ISPPARAMBUFFER &= ~NJD_KM_ZBUFFER_MODE;
    else if(p == 0)
        _nj_parameterkm_.ISPPARAMBUFFER |= NJD_KM_ZBUFFER_MODE;
}

void njMipmapkmAdjust(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & NJD_KM_MIPMAP_MASK) | p;
}

void njTextureFilterkmMode(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & NJD_KM_TEXFILTER_MASK) | p;
}

void njSuperSamplekmMode(Uint32 p)
{
    if(p == 1)
        _nj_parameterkm_.TSPPARAMBUFFER |= NJD_KM_SUPERSAMPLE_MODE;
    else if(p == 0)
        _nj_parameterkm_.TSPPARAMBUFFER &= ~NJD_KM_SUPERSAMPLE_MODE;
}

void njTextureClampkmMode(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & NJD_KM_TEXCLAMP_MASK) | p;
}

void njTextureFlipkmMode(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & NJD_KM_TEXFLIP_MASK) | p;
}

void njkmPolygonCullingSize(float val)
{
    kmSetCullingRegister(val);
}

void njPolygonCullingkmMode(Uint32 p)
{
    _nj_parameterkm_.ISPPARAMBUFFER = (_nj_parameterkm_.ISPPARAMBUFFER & NJD_KM_POLYCULL_MASK) | p;
}


void njColorBlendingkmMode(Uint32 a, Uint32 b)
{
    if(b & 1)
        _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & 0x3FFFFFF) | b;
    else
    {
        if(a)
            _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & 0x1FFFFFFF) | (b & 0xE0000000);
        else
            _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & 0xE3FFFFFF) | (b & 0x1C000000);
    }
}

void njSpecularkmMode(Uint32 p)
{
    if(p == 1)
        _nj_parameterkm_.GLOBALPARAMBUFFER |= NJD_KM_SPECULAR_MODE;
    else if(p == 0)
        _nj_parameterkm_.GLOBALPARAMBUFFER &= ~NJD_KM_SPECULAR_MODE;
}

void njAlphakmMode(Uint32 p)
{
    if(p == 1)
    {
        _nj_parameterkm_.TSPPARAMBUFFER |= NJD_KM_ALPHA_MODE;
    }
    else if(p == 0)
    {
        _nj_parameterkm_.TSPPARAMBUFFER &= ~NJD_KM_ALPHA_MODE;
    }
}


void njIgnoreTextureAlphakmMode(Uint32 p)
{
    if(p == 1)
    {
        _nj_parameterkm_.TSPPARAMBUFFER |= NJD_KM_IGNORETEXTUREALPHA_MODE;
    }
    else if(p == 0)
    {
        _nj_parameterkm_.TSPPARAMBUFFER &= ~NJD_KM_IGNORETEXTUREALPHA_MODE;
    }
}

void njTextureShadingkmMode(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & NJD_KM_TEXSHADE_MASK) | p;
}

Sint32 njSetkmCnkTextureNum(Uint32 a, Uint32 b)
{
    Uint32 n = b & 0x1FFF;

    NJS_TEXMEMLIST* mem = ((NJS_TEXMEMLIST*)_nj_current_texlist->textures[n].texaddr);

    if(_nj_current_texture == mem->globalIndex && _nj_current_texture_bank == mem->bank)
        return;

    _nj_current_texture = mem->globalIndex;
    _nj_current_texture_bank = mem->bank;

    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & 0xFFFFFFC0) | (mem->tspparambuffer & 0x3F);
    _nj_texglobal_color_ = mem->texinfo.texsurface.Type >> 16;
    _nj_parameterkm_.TexturePARAMBUFFER = mem->texparambuffer;

    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & 0xFFF800FF) | 
        ((a & 0xF000) << 3) | 
        (a & 0x0F00) | 
        (b & 0x2000) >> 1 | 
        (b & 0x4000) >> 1;

    return _nj_texglobal_color_; //why?
}

void njSetkmCnkBlendMode(Uint32 p)
{
    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_BLEND_MODE)
        p = _nj_cnk_blend_mode_;

    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & 0x3FFFFFF) | ((p << 18) & 0xFC000000);
}

void njSetCnkBlendMode(Uint32 p)
{
    _nj_cnk_blend_mode_ = p;
}

void njSetkmCellBlendMode(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & 0x3FFFFFF) | ((p << 18) & 0xFC000000);
}