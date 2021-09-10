#include <NinjaDev.h>

void njSetTextureInfo(NJS_TEXINFO *info,Uint16 *tex,Sint32 Type,Sint32 nWidth,Sint32 nHeight)
{
    info->texaddr = tex;
    info->texsurface.nWidth = nWidth;
    info->texsurface.nHeight = nHeight;
    info->texsurface.Type = Type << 16;
}
void	njSetTextureName(NJS_TEXNAME *texname,void *addr,Uint32 globalIndex,Uint32 attr)
{
    texname->filename = addr;
    texname->attr = attr;
    
    //unused tst instruction in the asm output (this flag is described to be checked in the documentation but it looks like they never do anything with it)
    if(texname->texaddr & 0x40000000);

    texname->texaddr = globalIndex;
   
}