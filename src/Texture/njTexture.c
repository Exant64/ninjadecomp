#include <NinjaDev.h>

void njInitTextureGlobalIndex(Uint32 globalIndex)
{
    if(globalIndex >= 0xFFFFFFF0)
    {
        _nj_user_globalIndex = globalIndex;
    }
    else
    {
        _nj_user_globalIndex = 0xFFFFFFEF;
    }
}

void njInitTextureBuffer(Sint8 *addr,Uint32 size)
{
    _nj_texture_buffer_st = addr;
    _nj_texture_buffer_max_size = (size / 2048) * 2048;
}
extern NJS_TEXSURFACE _nj_tex_err_surface;
void njInitTexture(NJS_TEXMEMLIST *addr,Uint32 n)
{
    njInitTexMemList(addr,n);
    _nj_current_texture_path[0] = 0;
    _nj_loadtexreq_mode_ = 2;
    _nj_loadtexreq_i_ = 0;
    _nj_tex_err_surface.Type = 0;
    _nj_tex_err_surface.BitDepth = 0;
    _nj_tex_err_surface.PixelFormat = 0;
    _nj_tex_err_surface.nWidth = 0;
    _nj_tex_err_surface.nHeight = 0;
    _nj_tex_err_surface.TextureSize = 0;
    _nj_tex_err_surface.fSurfaceFlags = 0;
    _nj_tex_err_surface.pSurface = 0;
}

void njExitTexture()
{
    njReleaseTextureAll();
    njReleaseCacheTextureAll();
    _nj_tex_err_surface.Type = 0;
    _nj_tex_err_surface.BitDepth = 0;
    _nj_tex_err_surface.PixelFormat = 0;
    _nj_tex_err_surface.nWidth = 0;
    _nj_tex_err_surface.nHeight = 0;
    _nj_tex_err_surface.TextureSize = 0;
    _nj_tex_err_surface.fSurfaceFlags = 0;
    _nj_tex_err_surface.pSurface = 0;
}

Sint32 njLoadTexture(NJS_TEXLIST *texlist)
{
    Uint32 n;
	
    if(texlist->nbTexture <= 0){
		_nj_texerr_.texerr = NJD_TEXERR_OTHER;
        return (-1);
     }

    for(n = 0;n < texlist->nbTexture;n++){
		if(njLoadTextureLN(texlist,n) < 0){
			_nj_texerr_.n = n;
			return -1;
		}
	}
	
	return 1;
}

Sint32	njSetTexture(NJS_TEXLIST *texlist)
{
    if(!texlist)
        return -1;
    
    _nj_current_texlist = texlist;
    return 1;
}

Sint32	njSetTextureNum(Uint32 n)
{
    NJS_TEXMEMLIST* mem = ((NJS_TEXMEMLIST*)_nj_current_texlist->textures[n].texaddr);

    if(_nj_current_texture == mem->globalIndex && _nj_current_texture_bank == mem->bank)
        return;

    _nj_current_texture = mem->globalIndex;
    _nj_current_texture_bank = mem->bank;

    _nj_current_ctx_->TSPPARAMBUFFER = (_nj_current_ctx_->TSPPARAMBUFFER & 0xFFFFFFC0) | (mem->tspparambuffer & 0x3F);

    _nj_texglobal_color_ = mem->texinfo.texsurface.Type >> 16;
    _nj_current_ctx_->TexturePARAMBUFFER = mem->texparambuffer;

    kmSetVertexRenderState(_nj_current_ctx_);
}

Uint32	njCalcTexture(Uint32 flag)
{
    KMUINT32 SizeOfTexture;
    KMUINT32 MaxBlockSizeOfTexture;

    if(flag == NJD_TEXMEM_MAXSIZE)
        return _nj_tex_max_free_size;

    kmGetFreeTextureMem(&SizeOfTexture, &MaxBlockSizeOfTexture);

    if(flag == NJD_TEXMEM_FREESIZE)
        return SizeOfTexture;
    else
        return MaxBlockSizeOfTexture;
}

void njSetTexturePath(const char *path)
{
    strcpy(_nj_current_texture_path, path);
}

void njGarbageTexture(NJS_TEXMEMLIST *addr,Uint32 n)
{
    int i;
    Uint32* pSurface;
    kmGarbageCollectTexture();

    i = 0;
    while(i < n)
    {
        if(addr[i].globalIndex != -1 && addr[i].texaddr & 2)
        {
            if(addr[i].texaddr & 8)
            {
                pSurface = addr[i].texinfo.texsurface.pSurface;

                //???
                if(n > 0)
                {
                    int i2 = 0;
                    do
                    {
                        if(addr[i2].globalIndex == addr[i].globalIndex)
                            addr[i2].texinfo.texsurface.pSurface = pSurface;
                        i2++;
                    } while (i2 < n);
                    
                }
            }
            njSetTextureParam(&addr[i]);
        }
        i++;
    }
}

NJS_TEXERRSTAT *njGetTextureErrStat()
{
    return &_nj_texerr_;
}

void njInitTextureErrStat()
{
    _nj_texerr_.n = -1;
    _nj_texerr_.globalIndex = -1;
    _nj_texerr_.texerr = 0;
    _nj_texerr_.gdstat = 0;
    _nj_texerr_.gderr = 0;
}