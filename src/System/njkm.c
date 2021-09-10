#include <NinjaDev.h>
//unfinished, only decompiled these two functions cuz i was curious wtf they do
extern Uint32 _nj_parameterkm_[];
void njGetkmPointer()
{
    _nj_parameterkm_[0] = _nj_current_ctx_->GLOBALPARAMBUFFER;
    _nj_parameterkm_[1] = _nj_current_ctx_->ISPPARAMBUFFER;
    _nj_parameterkm_[2] = _nj_current_ctx_->TSPPARAMBUFFER;
    _nj_parameterkm_[3] = _nj_current_ctx_->TexturePARAMBUFFER;

    _nj_parameterkm_[4] = _nj_vertex_buffer_.pCurrentPtr[0];

    _nj_parameterkm_[7] = _nj_vertex_buffer_.pCurrentPtr[1];
    _nj_parameterkm_[8] = _nj_vertex_buffer_.pCurrentPtr[3];

    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_USE_PUNCHTHROUGH)
    {
        _nj_parameterkm_[5] = _nj_vertex_buffer_.pCurrentPtr[2];
        _nj_parameterkm_[6] = _nj_vertex_buffer_.pCurrentPtr[4];
    }
    else
    {
        _nj_parameterkm_[5] = _nj_vertex_buffer_.pCurrentPtr[4];
        _nj_parameterkm_[6] = _nj_vertex_buffer_.pCurrentPtr[2];
    }
}

void njSetkmPointer()
{
    _nj_current_ctx_->GLOBALPARAMBUFFER = _nj_parameterkm_[0];
    _nj_current_ctx_->ISPPARAMBUFFER = _nj_parameterkm_[1];
    _nj_current_ctx_->TSPPARAMBUFFER = _nj_parameterkm_[2];
    _nj_current_ctx_->TexturePARAMBUFFER = _nj_parameterkm_[3];

    _nj_vertex_buffer_.pCurrentPtr[0] = _nj_parameterkm_[4];

    _nj_vertex_buffer_.pCurrentPtr[1] = _nj_parameterkm_[7];
    _nj_vertex_buffer_.pCurrentPtr[3] = _nj_parameterkm_[8];

    if(_nj_control_3d_flag_ & NJD_CONTROL_3D_USE_PUNCHTHROUGH)
    {
        _nj_vertex_buffer_.pCurrentPtr[2] = _nj_parameterkm_[5];
        _nj_vertex_buffer_.pCurrentPtr[4] = _nj_parameterkm_[6];
    }
    else
    {
        _nj_vertex_buffer_.pCurrentPtr[4] = _nj_parameterkm_[5];
        _nj_vertex_buffer_.pCurrentPtr[2] = _nj_parameterkm_[6];
    }
}

extern int _nj_sq_base_;
void njStartVertexNonTexOpaque()
{
    _nj_sq_base_ = _nj_parameterkm_[4] & 0xFC000000;
    _nj_sq_base_ = (_nj_parameterkm_[4] & 0x3FFFFFF) | 0xE0000000;
    
}