#include <NinjaDev.h>

extern int _nj_calc_vertex_;
void njPtclVlist(Uint16* vl, float h)
{
    Uint16 type;
    Uint32 size;
    Uint32 count;
    
    while((type = *vl++) != 0xFF)
    {
        size = *vl++;
        vl++;
        count = *vl++;
        _nj_calc_vertex_ += count;
        switch((Uint8)type)
        {
            case 34:
                njPtclDrawPolygon((NJS_POINT3*)vl,count,h);
                break;
            case 41:
                njPtclDrawPolygon2((NJS_POINT3*)vl,count,h);
                break;
            default:
                return;
        }

        (Uint8*)vl += ((size * 2) - 2) * 2;
    }
}
Sint32	njPtclDrawModel( NJS_CNK_MODEL *model, Float h )
{
    Sint32* vlist;
    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP)
        if(model->r > 0 && njCnkModelClip(model))
            return -1;
    vlist = model->vlist;
    if(vlist)
        njPtclVlist((Uint16*)vlist, h);
    return 0;
}

void	njPtclDrawObject( NJS_CNK_OBJECT *obj, Float h )
{
    Uint32 clip;
    do
    {
        Uint32 eval = obj->evalflags;
        if((eval & 7) == 7)
        {
             if(!(eval & 8))
                njPtclDrawModel(obj->model, h);
            if(!(eval & NJD_EVAL_BREAK))
                njPtclDrawObject(obj->child, h);
            
        }
        else
        {
           njPushMatrixEx();
            if(!(eval & 1))
                njTranslateEx((NJS_VECTOR*)obj->pos);
            if(!(eval & 2))
                njRotateEx((Angle*)obj->ang, eval & 0x20);
            if(!(eval & 4))
                njScaleEx((NJS_VECTOR*)obj->scl);
            if(!(eval & 8))
                clip = njPtclDrawModel(obj->model, h);
            if(!(eval & NJD_EVAL_BREAK))
                if(eval & NJD_EVAL_CLIP && !clip)
                    njPtclDrawObject(obj->child, h);
            njPopMatrixEx();
        }
        obj = obj->child;
    } while (obj);
    
}