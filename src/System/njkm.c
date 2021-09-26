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

PKMDWORD njEndModifier(PKMDWORD sq)
{
    sq += 2;
    *--sq = KMY_VOLUME_INSIDE_LAST;
    *--sq = (_nj_parameterkm_.GLOBALPARAMBUFFER & 0x30000) | KMY_PARAM_MODIFIER | KMY_LIST_OPAQUEMODIFIER | KMY_OBJ_LAST_MODIFIER; 
    _builtin_prefetch(sq);
    sq += 8;
    return sq;
}

PKMDWORD njStartModifier()
{
    PKMDWORD p;
    NJD_GET_SQ(_nj_parameterkm_.OpaqueMod);
    p = NJD_GET_MAPPING_ADDRESS(_nj_parameterkm_.OpaqueMod);
    p += 2;
    *--p = KMY_VOLUME_NORMAL;
    *--p = (_nj_parameterkm_.GLOBALPARAMBUFFER & 0x30000) | KMY_LIST_OPAQUEMODIFIER | KMY_PARAM_MODIFIER;
    _builtin_prefetch(p);
    _nj_listtype_ = &_nj_parameterkm_.OpaqueMod;
    p += 8;
    return p;   
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
        _nj_parameterkm_.ISPPARAMBUFFER &= KMY_ZWRITE_DISABLE_MASK;
    else if(p == 0)
        _nj_parameterkm_.ISPPARAMBUFFER |= KMY_ZWRITE_DISABLE;
}

void njMipmapkmAdjust(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & KMY_MIPMAP_MASK) | p;
}

void njTextureFilterkmMode(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & KMY_FILTER_MASK) | p;
}

void njSuperSamplekmMode(Uint32 p)
{
    if(p == 1)
        _nj_parameterkm_.TSPPARAMBUFFER |= KMY_SUPER_SAMPLE;
    else if(p == 0)
        _nj_parameterkm_.TSPPARAMBUFFER &= KMY_SUPER_SAMPLE_MASK;
}

void njTextureClampkmMode(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & KMY_CLAMP_MASK) | p;
}

void njTextureFlipkmMode(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & KMY_FLIP_MASK) | p;
}

void njkmPolygonCullingSize(float val)
{
    kmSetCullingRegister(val);
}

void njPolygonCullingkmMode(Uint32 p)
{
    _nj_parameterkm_.ISPPARAMBUFFER = (_nj_parameterkm_.ISPPARAMBUFFER & KMY_CULLING_MASK) | p;
}


void njColorBlendingkmMode(Uint32 a, Uint32 b)
{
    if(b & 1)
        _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & 0x3FFFFFF) | b;
    else
    {
        if(a)
            _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & KMY_SRCBLEND_MASK) | (b & 0xE0000000);
        else
            _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & KMY_DSTBLEND_MASK) | (b & 0x1C000000);
    }
}

void njSpecularkmMode(Uint32 p)
{
    if(p == 1)
        _nj_parameterkm_.GLOBALPARAMBUFFER |= KMY_OBJ_OFFSET;
    else if(p == 0)
        _nj_parameterkm_.GLOBALPARAMBUFFER &= KMY_OBJ_OFFSET_MASK;
}

void njAlphakmMode(Uint32 p)
{
    if(p == 1)
    {
        _nj_parameterkm_.TSPPARAMBUFFER |= KMY_ALPHA_ENABLE;
    }
    else if(p == 0)
    {
        _nj_parameterkm_.TSPPARAMBUFFER &= KMY_ALPHA_ENABLE_MASK;
    }
}


void njIgnoreTextureAlphakmMode(Uint32 p)
{
    if(p == 1)
    {
        _nj_parameterkm_.TSPPARAMBUFFER |= KMY_IGNORE_TEXALPHA;
    }
    else if(p == 0)
    {
        _nj_parameterkm_.TSPPARAMBUFFER &= KMY_IGNORE_TEXALPHA_MASK;
    }
}

void njTextureShadingkmMode(Uint32 p)
{
    _nj_parameterkm_.TSPPARAMBUFFER = (_nj_parameterkm_.TSPPARAMBUFFER & KMY_SHADING_MASK) | p;
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