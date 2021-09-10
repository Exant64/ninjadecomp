#include <NinjaDev.h>

extern KMVERTEXCONTEXT	*_nj_current_ctx_;
void njFogDisable()
{
	_nj_current_ctx_->RenderState = KM_FOGMODE;
	_nj_current_ctx_->FogMode = KM_NOFOG;
	kmProcessVertexRenderState(_nj_current_ctx_);
	kmSetVertexRenderState(_nj_current_ctx_);
}