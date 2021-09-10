#include <NinjaDev.h>
void njSetPaletteBank(int bank)
{
    _nj_current_ctx_->PaletteBank = bank;
    kmSetVertexRenderState(_nj_current_ctx_);
}

void njSetPaletteBankLN(NJS_TEXMEMLIST* mem, int bank)
{
    Uint32 type = (mem->texinfo.texsurface.Type >> 16) & 0xFF00;
    int val;

    if(type == 0x500 || type == 0x600)
        val = 0x3F;
    else if(type == 0x500 || type == 0x600)
        val = 0x30;
    else
        return;

    mem->texparambuffer = mem->texparambuffer & 0xF81FFFFF;
    mem->texparambuffer = mem->texparambuffer | ((val & bank) << 0x15);
    mem->bank = bank;
}

void 	njSetPaletteBankNum(Uint32 n,Sint32 bank)
{
    njSetPaletteBankLN((NJS_TEXMEMLIST*)_nj_current_texlist->textures[n].texaddr,bank);
}
Sint32 njSearchTexList(NJS_TEXMEMLIST *texmemlist,Uint32 size,Uint32 globalIndex);
void 	njSetPaletteBankNumG(Uint32 globalIndex,Sint32 bank)
{
    int ret = njSearchTexlist(_nj_texmemlist, _nj_texmemsize, globalIndex);

    if(ret)
        njSetPaletteBankLN(&_nj_texmemlist[ret], bank);
}
extern Uint32 _nj_palette_mode_;
extern Uint32 _nj_palette_bpp_;
void 	njSetPaletteMode(Uint32 mode)
{
    _nj_palette_mode_ = mode;
    switch(mode)
    {
        default:
        case 0:        
            _nj_palette_bpp_ = 16;
            kmSetPaletteMode(0);
            break;
        case 1:
            _nj_palette_bpp_ = 16;
            kmSetPaletteMode(1);
            break;
        case 2:
            _nj_palette_bpp_ = 16;
            kmSetPaletteMode(2);
            break;
        case 6: 
            _nj_palette_bpp_ = 32;
            kmSetPaletteMode(3);
            break;
    }
    
}
Uint32	njGetPaletteMode()
{
    return _nj_palette_mode_;
}
//unfinished