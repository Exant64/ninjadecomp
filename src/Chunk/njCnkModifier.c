#include <NinjaDev.h>


NJS_MODIFIER_WORK _nj_modifier_work;
extern PKMDWORD njStartModifier();
extern PKMDWORD njStartTransModifier();
extern int njCnkModVertex(NJS_MODIFIER_WORK*);
extern PKMDWORD njCnkModPolygon(Uint16* plist, NJS_CNK_MOD_BUF* buf, Uint16 val, PKMDWORD sq);
extern void njEndVertex(PKMDWORD);
int _njCnkModDrawModel( NJS_CNK_MODEL *model )
{
    Uint16* vlist, *plist;
    Uint16 type, offset,num;
    NJS_CNK_MOD_BUF* buf = (NJS_CNK_MOD_BUF*)_nj_vertex_buf_;
    NJS_CNK_MOD_BUF* oBuf;
    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP)
        if(njCnkModelClip(model))
            return 1;
    vlist = model->vlist;
    
    type = *vlist++;
    vlist++;
    offset = *vlist++;
    num = *vlist++;

    oBuf = &buf[offset];

    _nj_modifier_work.vNum = num;
    _nj_modifier_work.pVlist = vlist;
    _nj_modifier_work.pVertexBuf = oBuf;

    _nj_modifier_work.pSQ = NJD_GET_MAPPING_ADDRESS(oBuf);
    NJD_SEND_SQ(oBuf);

    _nj_modifier_work.a5 = _nj_screen_.dist * _nj_scr_aspect_x_;
    _nj_modifier_work.a6 = _nj_screen_.dist * _nj_scr_aspect_y_;
    _nj_modifier_work.cx = _nj_screen_.cx;
    _nj_modifier_work.cy = _nj_screen_.cy;

    _nj_calc_vertex_ += num;

    if(type != NJD_CV) 
        return 0;
    if(njCnkModVertex(&_nj_modifier_work) >= num)
        return 0;

    plist = model->plist;
    while((type = *plist++) != 0x00FF)
    {
        type = (Uint8)type;
        if(type >= NJD_MATOFF)
        {
            if(type >= NJD_VOLOFF)
            {
                Uint16 size = *plist++;
                Uint16 val_ = *plist++;
                if(type == NJD_CO_P3)
                {
                    PKMDWORD sq = njStartModifier();
                    PKMDWORD end = njCnkModPolygon(plist,buf,val_,sq);
                    njEndVertex(end);
                    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_TRANS_MODIFIER)
                    {
                        PKMDWORD sq = njStartTransModifier();
                        PKMDWORD end = njCnkModPolygon(plist,buf,val_,sq);
                        njEndVertex(end);
                    }
                }
                (Uint8*)plist += (size - 1) << 1;
                _builtin_prefetch(plist);
            }
            else
            {
                Uint16 val = *plist++;
                (Uint8*)plist += val << 1;
            }
        }
    }
    
    return 0;
}

void _njCnkModDrawObject( NJS_CNK_OBJECT *obj )
{
    Uint32 clip;
    do
    {
        Uint32 eval = obj->evalflags;
        if((eval & 7) == 7)
        {
             if(!(eval & 8))
                _njCnkModDrawModel(obj->model);
            if(!(eval & NJD_EVAL_BREAK))
                _njCnkModDrawObject(obj->child);
            
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
                clip = _njCnkModDrawModel(obj->model);
            if(!(eval & NJD_EVAL_BREAK))
                if(eval & NJD_EVAL_CLIP && clip)
                    _njCnkModDrawObject(obj->child);
            njPopMatrixEx();
        }
        obj = obj->child;
    } while (obj);
}
void    njCnkModDrawModel( NJS_CNK_MODEL *model )
{
    NJS_CNK_MODEL* volatile p = model;
    njGetkmPointer();
    _njCnkModDrawModel(p);
    njSetkmPointer();
}
void    njCnkModDrawObject( NJS_CNK_OBJECT *object )
{
    NJS_CNK_OBJECT* volatile p = object;
    njGetkmPointer();
    _builtin_prefetch(p);
    _njCnkModDrawObject(p);
    njSetkmPointer();
}