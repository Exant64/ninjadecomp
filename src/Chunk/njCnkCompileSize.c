#include <NinjaDev.h>

int unk_298;
int unk_29C;
extern Uint32 _nj_direct_compile_mode_;
extern Uint32 _nj_direct_culling_mode_;
Uint32 njCnkDirectTextureSize(Uint16* vl, Uint32 val)
{
    int calc = ((val >> -0xE) & 3) << 1;
    int i = 0;
    val = val & 0x3FFF;
    do
    {
        Uint16 t = *vl++;
        vl++;
        if(t < 0)
        {
            t = -t;
            if(_nj_direct_culling_mode_ != 0x8000000)
                i++;
        }

        vl += 5;
        i++;
        t -= 2;
        do
        {
            vl += 3;
            i++;
            (Uint8*)vl += calc;
        } while (--t);
        

        i++;
    } while (--val);
    return i * 32;
}
Uint32 njCnkDirectPolygonSize(Uint16* vl, Uint32 val)
{
    int calc = ((val >> -0xE) & 3) << 1;
    int i = 0;
    val = val & 0x3FFF;
    do
    {
        Uint16 t = *vl++;
        vl++;
        if(t < 0)
        {
            t = -t;
            if(_nj_direct_culling_mode_ != 0x8000000)
                i++;
        }

        vl += 1;
        i++;
        t -= 2;
        do
        {
            vl += 1;
            i++;
            (Uint8*)vl += calc;
        } while (--t);
        

        i++;
    } while (--val);
    return i * 32;
}
void njCnkDirectVlistSize(Uint16* vl)
{
    Uint16 type;
    Uint32 size;
    
    while((type = *vl++) != 0x00FF)
    {
        size = *vl++;
        vl+=2;
        switch((Uint8)type)
        {
            case NJD_CV_VN:
            case NJD_CV:
                unk_298 = 0;
                break;
            case NJD_CV_D8:
            case NJD_CV_VN_D8:
                unk_298 = 1;
                break;
            default:
                return;
        }

        if(_nj_direct_compile_mode_ == 1)
            unk_298 = 1;

        (Uint8*)vl += ((size * 2) - 2) * 2;
    }
}

Uint32	njCnkDirectPlistSize( Uint16* vl )
{
    Sint16 type;
    Uint16 size;
    Uint16 val;
    int i = 0;

    while((type = *vl++) != 0x00FF)
    {
        if(type < 8)
        {
            if(type == 1)
                ;
            else if(type == 2)
                ;
            else if(type == 3)
                ;
        }
        else
        {
            if(type < 16)
                vl++;
            else
            {
                if(type < 64)
                    (Uint8*)vl += (*vl++ << 1);
                else
                {
                    size = *vl++;
                    val = *vl++;

                    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_CONSTANT_ATTR)
                    {
                        type &= _nj_constant_attr_and_;
                        type |= _nj_constant_attr_or_;
                    }
                    if(!unk_298)
                    {
                        if((type << -8) & 2);
                        switch(type)
                        {
                            case 0x41:
                            case 0x42:
                                i += 32;
                                i += njCnkDirectTextureSize(vl, val);
                                break;
                            case 0x40:
                                i += 32;
                                i += njCnkDirectPolygonSize(vl, val);
                                break;
                        }
                    }
                    else
                    {
                        switch(type)
                        {
                            case 0x41:
                            case 0x42:
                                i += 16;
                                i += njCnkDirectTextureSize(vl, val);
                                break;
                            case 0x40:
                                i += 16;
                                i += njCnkDirectPolygonSize(vl, val);
                                break;
                        }
                        
                    }
                    (Uint8*)vl += ((size-1) * 2);       
                }
                
            } 
                
        }
    }
    return i;
}
Uint32	_njCnkDirectModelCompileSize( NJS_CNK_MODEL *obj )
{
    NJS_CNK_MODEL* pObj = obj;
    Uint32 size;
    if(pObj->vlist)
        njCnkDirectVlistSize(pObj->vlist);
    if(pObj->plist){
        size = njCnkDirectPlistSize(pObj->plist);
        return size + 0x20;
    }
    
}
Uint32	_njCnkDirectObjectCompileSize( NJS_CNK_OBJECT *obj )
{
    Uint32 eval;
    do
    {
        eval = obj->evalflags;
        if(!(eval & 8))
            unk_29C += _njCnkDirectModelCompileSize(obj->model);
        if(!(eval & 0x10))
            _njCnkDirectObjectCompileSize(obj->child);
    } while (obj = obj->child);
    
}
Uint32	njCnkDirectModelCompileSize( NJS_CNK_MODEL *model )
{
    _nj_direct_compile_mode_ = 0;
    return _njCnkDirectModelCompileSize(model);
}

Uint32	njCnkDirectObjectCompileSize( NJS_CNK_OBJECT *obj )
{
    _nj_direct_compile_mode_ = 0;
    unk_29C = 0;
    _njCnkDirectObjectCompileSize(obj);
    return unk_29C;
}

Uint32	njCnkDirectModelCompileLightSize( NJS_CNK_MODEL *model )
{
    _nj_direct_compile_mode_ = 1;
    return _njCnkDirectModelCompileSize(model);
}

Uint32	njCnkDirectObjectCompileLightSize( NJS_CNK_OBJECT *obj )
{
    _nj_direct_compile_mode_ = 1;
    unk_29C = 0;
    _njCnkDirectObjectCompileSize(obj);
    return unk_29C;
}