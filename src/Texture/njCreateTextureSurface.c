#include <NinjaDev.h>

Sint32 njCheckTextureFormatLow(NJS_TEXSURFACE *texsurface,Sint32 nWidth,Sint32 nHeight,Sint32 nTextureType);
Sint32 njCreateTextureSurface(NJS_TEXSURFACE *texsurface,Sint32 nWidth,Sint32 nHeight,Sint32 nTextureType)
{
    int ret;
    Sint32 format = njCheckTextureFormatLow(texsurface,nWidth,nHeight,nTextureType);
    if(!format)
        ret = format;
    else
    {
        int alloc;
        if ( (Uint16)texsurface->Type == 3 )
            alloc = kmiVQalloc(texsurface);
        else
            alloc = kmiTXalloc(texsurface->TextureSize, texsurface);
        if(alloc == 3)
            kmiDefaultInterruptHandler(4);
            
        ret = alloc;
    }
    return ret;
}