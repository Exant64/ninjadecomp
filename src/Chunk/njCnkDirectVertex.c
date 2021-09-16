#include <NinjaDev.h>
#include <ninjadir.h>
extern int _nj_direct_compile_mode_;
extern NJS_DIRECT_COMPILE_LIGHT * _nj_direct_compile_light_;
void njCnkDirectVertexVN( Float *vlist, NJS_DIRECT_BUF *buf, Int num )
{
    int n = num;
    do
    {
        njCalcPoint (0, (NJS_POINT3*)vlist, (NJS_POINT3*)&buf->px);
        vlist += 3;
        njCalcVector(0, (NJS_POINT3*)vlist, (NJS_POINT3*)&buf->nx);
        njUnitVector((NJS_POINT3*)&buf->nx);
        vlist += 3;

        if(_nj_direct_compile_mode_ == 1)
        {
            float r = _nj_direct_compile_light_->r;
            float g = _nj_direct_compile_light_->g;
            float b = _nj_direct_compile_light_->b;
            float dot = _nj_direct_compile_light_->x * buf->nx + _nj_direct_compile_light_->y * buf->ny + _nj_direct_compile_light_->z * buf->nz;
            float inten = -_nj_direct_compile_light_->inten * dot;
            float ambient = _nj_direct_compile_light_->ambient;
            float a = 1;

            inten += ambient;
            if(ambient > inten)
                inten = ambient;
            if(inten > 1)
                inten = 1;
            inten *= 255;
            if(r < 0) r = 0;
            if(r > 1) r = 1;

            if(g < 0) g = 0;
            if(g > 1) g = 1;

            if(b < 0) b = 0;
            if(b > 1) b = 1;

            //this is probably copypasted from somewhere, proof being that alpha is being clamped even though its hardcoded to be 1
            if(a < 0) a = 0;
            if(a > 1) a = 1;
            
            r*=inten;
            g*=inten;
            b*=inten;
            a*= 255;

            //casting the floats to "unsigned" specifically produces that 4F000000 float conversion/signed check code
            buf->col = ( (unsigned long)(((unsigned long)a)<<24)|(unsigned long)(((unsigned long)r)<<16) |(unsigned long)(((unsigned long)g)<<8)|((unsigned long)b) );//ARGB(a,r,g,b);;
        }
        else
            buf->col = 0xFFFFFFFF;
        
        
        buf++;
        
    } while (--n);
    
}

void njCnkDirectVertexV( Float *vlist, NJS_DIRECT_BUF *buf, Int num )
{

    int n = num;
    do
    {
        njCalcPoint(0, (NJS_POINT3*)vlist, (NJS_POINT3*)&buf->px);
        buf->nx = 0;
        buf->ny = 0;
        buf->nz = 1;
        vlist += 3;
        buf->col = 0xFFFFFFFF;
        
        buf++;
        
    } while (--n);    
}

void	njCnkDirectVertexVD8( Float *vlist, NJS_DIRECT_BUF *buf, Int num )
{
    int n = num;
    do
    {
        njCalcPoint(0, (NJS_POINT3*)vlist, (NJS_POINT3*)&buf->px);
        buf->nx = 0;
        buf->ny = 0;
        buf->nz = 1;
        vlist += 3;
        buf->col = *((Uint32*)vlist++);
        
        buf++;
        
    } while (--n);   
}

void njCnkDirectVertexVND8( Float *vlist, NJS_DIRECT_BUF *buf, Int num )
{
    int n = num;
    do
    {
        njCalcPoint (0, (NJS_POINT3*)vlist, (NJS_POINT3*)&buf->px);
        vlist += 3;
        njCalcVector(0, (NJS_POINT3*)vlist, (NJS_POINT3*)&buf->nx);
        njUnitVector((NJS_POINT3*)&buf->nx);
        vlist += 3;
        buf->col = *((Uint32*)vlist++);
        
        buf++;
        
    } while (--n);
    
}
