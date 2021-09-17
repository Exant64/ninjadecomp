#include <NinjaDev.h>
#include <ninjadir.h>

Uint32 _nj_direct_culling_mode_ = 0x8000000;
NJS_ARGB _nj_direct_col = {1,1,1,1};
NJS_ARGB _nj_direct_spec = {0,0,0,0};

Uint32 unk_A90;
Uint32 _nj_direct_compile_mode_;
NJS_DIRECT_COMPILE_LIGHT * _nj_direct_compile_light_;
NJS_DIRECT_HEAD* unk_A9C;
Uint32 _nj_direct_vertex_cnt_;
Uint32 _nj_direct_global_cnt_;
NJS_DIRECT_HEAD* unk_AA8;

void	njCnkDirectCullingMode( Uint32 mode )
{
    switch(mode)
    {
        case 2:
            _nj_direct_culling_mode_ = 0x10000000;
            break;
        case 3:
            _nj_direct_culling_mode_ = 0x18000000;
            break;
        default:
            _nj_direct_culling_mode_ = 0x8000000;
            break;
    }
}

void* njCnkDirectGlobalOpaqueD8(NJS_DIRECT_GLOBAL_D8* gl)
{
    NJS_DIRECT_GLOBAL_D8* global = gl;
    gl++;
    global->TEXTUREADDR = _nj_parameterkm_.TexturePARAMBUFFER;
    global->TSPPARAM = (_nj_parameterkm_.TSPPARAMBUFFER & 0x3EFFFFF) | 0x20080000;
    global->ISPPARAM = (_nj_parameterkm_.ISPPARAMBUFFER & 0xE7FFFFFF) | _nj_direct_culling_mode_;
    global->GP = global->GLOBALPARAM = _nj_parameterkm_.GLOBALPARAMBUFFER;
    _nj_direct_global_cnt_++;
    return gl;
}

void* njCnkDirectGlobalTransD8(NJS_DIRECT_GLOBAL_D8* gl)
{
    NJS_DIRECT_GLOBAL_D8* global = gl;
    gl++;
    global->TEXTUREADDR = _nj_parameterkm_.TexturePARAMBUFFER;
    global->TSPPARAM = _nj_parameterkm_.TSPPARAMBUFFER;
    global->ISPPARAM = (_nj_parameterkm_.ISPPARAMBUFFER & 0xE7FFFFFF) | _nj_direct_culling_mode_;
    global->GP = global->GLOBALPARAM = _nj_parameterkm_.GLOBALPARAMBUFFER;
    _nj_direct_global_cnt_++;
    return gl;
}

void* njCnkDirectGlobalOpaque(NJS_DIRECT_GLOBAL* gl)
{
    NJS_DIRECT_GLOBAL* global = gl;
    
    global->sa = _nj_direct_spec.a;
    global->sr = _nj_direct_spec.r;
    global->sg = _nj_direct_spec.g;
    global->sb = _nj_direct_spec.b;

    global->da = _nj_direct_col.a;
    global->dr = _nj_direct_col.r;
    global->dg = _nj_direct_col.g;
    global->db = _nj_direct_col.b;

    gl++;
    global->TEXTUREADDR = _nj_parameterkm_.TexturePARAMBUFFER;
    global->TSPPARAM = (_nj_parameterkm_.TSPPARAMBUFFER & 0x3EFFFFF) | 0x20080000;
    global->ISPPARAM = (_nj_parameterkm_.ISPPARAMBUFFER & 0xE7FFFFFF) | _nj_direct_culling_mode_;
    global->GP = global->GLOBALPARAM = _nj_parameterkm_.GLOBALPARAMBUFFER;
    _nj_direct_global_cnt_++;
    return gl;
}

void* njCnkDirectGlobalTrans(NJS_DIRECT_GLOBAL* gl)
{
    NJS_DIRECT_GLOBAL* global = gl;
    
    global->sa = _nj_direct_spec.a;
    global->sr = _nj_direct_spec.r;
    global->sg = _nj_direct_spec.g;
    global->sb = _nj_direct_spec.b;

    global->da = _nj_direct_col.a;
    global->dr = _nj_direct_col.r;
    global->dg = _nj_direct_col.g;
    global->db = _nj_direct_col.b;

    gl++;
    global->TEXTUREADDR = _nj_parameterkm_.TexturePARAMBUFFER;
    global->TSPPARAM = _nj_parameterkm_.TSPPARAMBUFFER;
    global->ISPPARAM = (_nj_parameterkm_.ISPPARAMBUFFER & 0xE7FFFFFF) | _nj_direct_culling_mode_;
    global->GP = global->GLOBALPARAM = _nj_parameterkm_.GLOBALPARAMBUFFER;
    _nj_direct_global_cnt_++;
    return gl;
}

void njCnkDirectVlist(Uint16* vlist, NJS_DIRECT_BUF* buf)
{
    Uint16* vl = vlist;
    Uint16 type;
    
    while((type = *vl++) != 0x00FF)
    {
        Uint32 size;
        Uint32 v1;
        Uint32 num;

        size = *vl++;
        v1 = *vl++;
        num = *vl++;
        buf += v1;

        switch((Uint8)type)
        {
            case NJD_CV_VN:
                njCnkDirectVertexVN((Float*)vl,buf,num);
                unk_A90 = 0;
                break;
            case NJD_CV:
                njCnkDirectVertexV((Float*)vl,buf,num);
                unk_A90 = 0;
                break;
            case NJD_CV_D8:
                njCnkDirectVertexVD8((Float*)vl,buf,num);
                unk_A90 = 1;
                break;
            case NJD_CV_VN_D8:
                njCnkDirectVertexVND8((Float*)vl,buf,num);
                unk_A90 = 1;
                break;
            default:
                return;
        }

        if(_nj_direct_compile_mode_ == 1)
            unk_A90 = 1;

        (Uint8*)vl += ((size * 2) - 2) * 2;
    }
}
void njCnkSetMaterial( Uint32 data, Uint32 *plist, Float *diff, Float *ambi, Float *spec );
Sint32 njSetkmCnkTextureNum(Uint32 a, Uint32 b);
void njSetkmCnkBlendMode(Uint32 p);
Uint32	njCnkDirectPlist( Uint16* vl, NJS_DIRECT_BUF* buf, NJS_DIRECT_GLOBAL* head )
{
    Sint16 type;
    Uint16 size;
    Uint16 val;
    int i = 0;

    while((type = *vl++) != 0x00FF)
    {
        Uint16 data = type;
        if(type < 8)
        {
            if(type == 1)
                njSetkmCnkBlendMode(data);
            else if(type == 2)
                ;
            else if(type == 3)
                ;
        }
        else
        {
            if(type < 16)
                njSetkmCnkTextureNum(data,*vl++);
            else
            {
                if(type < 64)
                {
                    njCnkSetMaterial(data,(Uint32*)vl, (Float*)&_nj_direct_col, 0, (Float*)&_nj_direct_spec);
                    (Uint8*)vl += (*vl++ << 1);
                }
                else
                {
                    size = *vl++;
                    val = *vl++;

                    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_CONSTANT_ATTR)
                    {
                        type &= _nj_constant_attr_and_;
                        type |= _nj_constant_attr_or_;
                    }

                    if(!unk_A90)
                    {

                    }
                    else
                    {

                    }

                    _nj_direct_vertex_cnt_++;
                    (Uint8*)vl += ((size-1) * 2);       
                }
                
            } 
                
        }
    }
    return i;
}

void* _njCnkDirectModelCompile( NJS_CNK_MODEL* mdl, void* ptr)
{
    NJS_DIRECT_HEAD* head = (NJS_DIRECT_HEAD*)ptr;
    unk_A9C = head;

    njCalcPoint(0, &mdl->center, (NJS_POINT3*)&head->x);
    head->r = mdl->r;
    head++;
    {
        Uint16* vlist = (Uint16*)mdl->vlist;
        if(vlist)
            njCnkDirectVlist(vlist, (NJS_DIRECT_BUF*)_nj_vertex_buf_);
    }  
    //plist calls
    {
        Uint32* plist = mdl->plist;
        njCnkDirectPlist(plist, (NJS_DIRECT_BUF*)_nj_vertex_buf_,head);
    }

    head->mode = unk_A90;
    
}

void _njCnkDirectObjectCompile( NJS_CNK_OBJECT *obj )
{
    Uint32 clip;
    do
    {
        Uint32 eval = obj->evalflags;
        if((eval & 7) == 7)
        {
             if(!(eval & 8))
                unk_AA8 = _njCnkDirectModelCompile(obj->model, unk_AA8);
            if(!(eval & NJD_EVAL_BREAK))
                _njCnkDirectObjectCompile(obj->child);
            
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
                unk_AA8 = _njCnkDirectModelCompile(obj->model, unk_AA8);
            if(!(eval & NJD_EVAL_BREAK))
                    _njCnkDirectObjectCompile(obj->child);
            njPopMatrixEx();
        }
        obj = obj->child;
    } while (obj);
    
}

void	*njCnkDirectModelCompile( NJS_CNK_MODEL *model, void *ptr )
{
    njGetkmPointer();
    njPushMatrixEx();
    njUnitMatrix(0);

    _nj_direct_compile_mode_ = 0;

    _njCnkDirectModelCompile(model,ptr);

    njPopMatrixEx();
    unk_A9C->next = 0;

    njSetkmPointer();
}

void	*njCnkDirectObjectCompile( NJS_CNK_OBJECT *obj, void *ptr )
{
    njGetkmPointer();
    njPushMatrixEx();
    njUnitMatrix(0);

    _nj_direct_compile_mode_ = 0;

    unk_AA8 = ptr;
    _njCnkDirectObjectCompile(obj);

    njPopMatrixEx();
    unk_A9C->next = 0;

    njSetkmPointer();
}

void* njCnkDirectModelCompileLight( NJS_CNK_MODEL *model, void *ptr, NJS_DIRECT_COMPILE_LIGHT *l )
{
    njGetkmPointer();
    njPushMatrixEx();
    njUnitMatrix(0);

    _nj_direct_compile_mode_ = 1;
    _nj_direct_compile_light_ = l;

    _njCnkDirectModelCompile(model,ptr);
   
    njPopMatrixEx();
     unk_A9C->next = 0;
    njSetkmPointer();
}

void * njCnkDirectObjectCompileLight( NJS_CNK_OBJECT *obj, void *ptr, NJS_DIRECT_COMPILE_LIGHT *l )
{
    njGetkmPointer();
    njPushMatrixEx();
    njUnitMatrix(0);

    _nj_direct_compile_mode_ = 1;
    _nj_direct_compile_light_ = l;

    unk_AA8 = (NJS_DIRECT_HEAD*)ptr;
    _njCnkDirectObjectCompile(obj);
    
    njPopMatrixEx();
    unk_A9C->next = 0;
    njSetkmPointer();

    return unk_AA8;
}