//UNFINISHED FILE
#include <NinjaDev.h>

extern Uint32 _nj_texture_memory_size;
void njSetTextureMemorySize(Uint32 size)
{
    _nj_texture_memory_size = size;
}
void njChangeTextureMemorySize(Uint32 size )
{
    _nj_texture_memory_size = size;
    _nj_SystemConfigStruct_.nTextureMemorySize = size;
    kmSetSystemConfiguration(&_nj_SystemConfigStruct_);
    _nj_tex_max_free_size = njCalcTexture(0);
}
void njSetVertexBuffer(Uint32 *buffer,Sint32 size)
{
    _nj_usr_vertex_buffer_ptr_ = (Uint32)buffer | 0xA0000000;
    _nj_usr_vertex_buffer_size_ = size;
}
void njSetEORflag()
{
    _nj_eor_flag_ = 0;
    _nj_render_flag_ = 1;
    if(_nj_eor_function2_)
        _nj_eor_function2_();
}
void njSetEOVflag()
{
    _nj_eov_flag_ = 0;
}
void njSetERRflag(Int val)
{
    _nj_fatal_err_callback_ = val;
}
SYCHAIN BSG_4;
void njBlank()
{
    if(_nj_render_flag_)
    {
        syChainDeleteHandler(BSG_4);
    }
    _nj_blank_count_++;
}
void waitVsync()
{
    while (*((int*)0xA05F810C) & 0x3FF);
    while (! (*((int*)0xA05F810C) & 0x3FF));
}
void G2FifoIsEmpty(int * val)
{
    *val = (*(int*)0xA05F688C) & 32;
}
//todo
void njSetVideoMode() {}
void njSetVideoModeChange(){}

void njPalExtCallbackFunc(PKMPALEXTINFO pData)
{
    pData->nPALExtMode = _nj_palext_height_ratio_;
}

//todo
#define system_thing (*(int*)0xA05F689C)
void njInitSystem(Int v1, Int v2, Int v3)
{
    //unfinished,doing it backwards cuz the start of it is tough to understand
    //from kmSetDisplayMode and upwards

    _nj_SystemConfigStruct_.dwSize = sizeof(NJ_KMSYSTEMCONFIGSTRUCT);
    _nj_SystemConfigStruct_.field_4 = 1;

    _nj_ppSurfaceArray[0] = &_nj_framebuffer_surface0_;
    _nj_ppSurfaceArray[1] = &_nj_framebuffer_surface1_;
    _nj_SystemConfigStruct_.ppSurfaceDescArray = _nj_ppSurfaceArray;

    _nj_SystemConfigStruct_.field_16 = 0;
    _nj_SystemConfigStruct_.field_20 = 0;

    _nj_SystemConfigStruct_.nTextureMemorySize = _nj_texture_memory_size;

    _nj_SystemConfigStruct_.pBufferDesc = &_nj_vertex_buffer_;
    _nj_SystemConfigStruct_.field_36 = 0;
    _nj_SystemConfigStruct_.field_40 = 0;
    _nj_SystemConfigStruct_.field_44 = 0;
    _nj_SystemConfigStruct_.field_48 = 0;
    _nj_SystemConfigStruct_.field_52 = 0;
    _nj_SystemConfigStruct_.field_56 = 0;
    _nj_SystemConfigStruct_.field_60 = 0;

    _nj_render_flag_ = 0;
    _nj_eor_flag_ = 0;
    _nj_eov_flag_ = 1;
    _nj_fatal_err_callback_ = 0;
    kmSetEORCallback(njSetEORflag,0);
    kmfSetFatalErrorCallback(njSetERRflag);
    kmSetWaitVsyncCount(_nj_waitvsync_count);
    njInitGlobal();
    if((Uint8)system_thing < 10)
    {
        njSetBorderColor(0xFFFF6600);
        _NJ_GO_TO_LOOP();
    }
}

void njChangeSystem() {}
extern LIGHT_BUF_THING CSG_0;
extern float _nj_cnk_easy_multilight_buffer_[];
extern float _nj_cnk_simple_multilight_buffer_[];
void njInitGlobal()
{
    //todo

    int i;
    LIGHT_BUF_THING light_buf;

    njLightSystemInit();

    i = 0;
    do
    {
        njInitContext(&_nj_context_[i]);
        _nj_ctx_color_mode_[i] = 0x80012; //NJD_ARC1_OPAQUE|NJD_ARC1_FLOAT|NJD_ARC1_NORMAL
    } 
    while (i < 6);
    
    njInitContext(&_nj_background_ctx_);
    _nj_background_ctx_.RenderState = 0xC0;
    _nj_background_ctx_.SRCBlendingMode = 0xA; //NJD_COLOR_BLENDING_ONE
    _nj_background_ctx_.DSTBlendingMode = 0xB; //NJD_COLOR_BLENDING_ZERO
    kmProcessVertexRenderState(&_nj_background_ctx_);
    kmSetBackGroundRenderState(&_nj_background_ctx_);
    njInitSprite();
    kmSetCullingRegister(0.01f);
    njSetCurrentContext(0);
    
    
    light_buf = CSG_0;
    i = 0;
    do
    {
        _nj_cnk_easy_multilight_buffer_[i] = light_buf.pad[i];
        i++;
    } while (i < 48);
    
    light_buf = CSG_0;
    i = 0;
    do
    {
        _nj_cnk_simple_multilight_buffer_[i] = light_buf.pad[i];
        i++;
    } while (i < 48);
}
void njChangeGlobal(){}
void njInitVertexBuffer(){}

//CONTEXT
void njSetCurrentContext(int ctx)
{
    _nj_current_ctx_ = &_nj_context_[ctx];
    kmSetVertexRenderState(_nj_current_ctx_);
    _nj_color_mode_ = _nj_ctx_color_mode_[ctx];
}
//copied from katana r2 (pc version of ninja), i hope it didnt change since then
void njInitContext(PKMVERTEXCONTEXT ctx)
{
    ctx->RenderState = 0x3F3FFFF;
    ctx->ParamType = KM_POLYGON;
    ctx->ListType = KM_OPAQUE_POLYGON;
    ctx->ColorType = KM_FLOATINGCOLOR;
    ctx->CullingMode = KM_CULLSMALL;
    ctx->ShadingMode = KM_NOTEXTUREGOURAUD;
    ctx->UVFormat = KM_32BITUV;
    ctx->DepthMode = KM_GREATER;
    ctx->ScreenCoordination = KM_SCREEN;
    ctx->SelectModifier = KM_NOMODIFIER;
    ctx->bZWriteDisable = 0;
    ctx->SRCBlendingMode = KM_SRCALPHA;
    ctx->DSTBlendingMode = KM_INVSRCALPHA;
    ctx->bSRCSel = 0;
    ctx->bDSTSel = 0;
    ctx->FogMode = KM_NOFOG;
    ctx->bUseSpecular = 0;
    ctx->bUseAlpha = 0;
    ctx->bIgnoreTextureAlpha = 0;
    ctx->FlipUV = KM_NOFLIP;
    ctx->ClampUV = KM_NOCLAMP;
    ctx->FilterMode = KM_POINT_SAMPLE;
    ctx->bSuperSample = 0;
    ctx->MipMapAdjust = 4;
    ctx->TextureShadingMode = KM_MODULATE_ALPHA;
    ctx->pTextureSurfaceDesc = 0;
    ctx->bColorClamp = 0;
    ctx->PaletteBank = 0;
    ctx->fFaceColorAlpha = 1.0;
    ctx->fFaceColorRed = 1.0;
    ctx->fFaceColorGreen = 1.0;
    ctx->fFaceColorBlue = 1.0;
    ctx->fOffsetColorAlpha = 1.0;
    ctx->fOffsetColorRed = 0.0;
    ctx->fOffsetColorGreen = 0.0;
    ctx->fOffsetColorBlue = 0.0;
    kmProcessVertexRenderState(ctx);
}

//EOR
void njSetEORFunction(void (*func)(void))
{
    _nj_eor_function_ = func;
}
void njSetEORCallBackFunction(void (*func)(void))
{
    _nj_eor_function2_ = func;
}
void njExeEORFunction()
{
    if(_nj_eor_function_)
        _nj_eor_function_();
}

//todo
void njWaitVSync(){}

void njRenderStart()
{
    _nj_eor_flag_ = 1;
    kmRender();
    _nj_calc_vertex_ = 0;
    _nj_calc_polygon_ = 0;
    _nj_draw_polygon_ = 0;
}

extern int _nj_wait_vsync_in_;
extern int _nj_wait_vsync_out_;
void njFlipFrameBuffer()
{
    _nj_wait_vsync_in_ = syTmrGetCount();

    kmFlipFrameBuffer();
    _nj_vsync_count_++;

    _nj_wait_vsync_out_ = syTmrGetCount();

    _nj_start_vertex_op = _nj_vertex_buffer_.pCurrentPtr[0];
    _nj_start_vertex_om = _nj_vertex_buffer_.pCurrentPtr[1];
    _nj_start_vertex_tp = _nj_vertex_buffer_.pCurrentPtr[2];
    _nj_start_vertex_tm = _nj_vertex_buffer_.pCurrentPtr[3];
    _nj_start_vertex_pt = _nj_vertex_buffer_.pCurrentPtr[4];
}