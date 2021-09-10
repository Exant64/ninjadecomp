#include <stdarg.h>
#include "ninja.h"
#define _STRICT_UNION_
#include "KAMUI.H"
#include "sg_chain.h"
#include "sg_tmr.h"
enum	{
	NJD_SYSTEM_CTX,
	NJD_MODIFIER0_CTX,
	NJD_MODIFIER1_CTX,
	NJD_2PARAM_CTX,
	NJD_DEBUG_CTX,
	NJD_NINDOWS_CTX,
	NJD_CONTEXT_MAX
};
extern void	njSetCurrentContext( int ctx );

extern void _NJ_GO_TO_LOOP();

extern Int volatile  _nj_eor_flag_;
extern Int volatile  _nj_eov_flag_;
extern Int volatile  _nj_render_flag_;

extern void (*_nj_eor_function_)(void);
extern void (*_nj_eor_function2_)();
extern	KMSURFACEDESC	_nj_framebuffer_surface0_;
extern	KMSURFACEDESC	_nj_framebuffer_surface1_;

extern PPKMSURFACEDESC _nj_ppSurfaceArray;

extern	KMVERTEXCONTEXT	_nj_context_[NJD_CONTEXT_MAX];
extern	KMVERTEXCONTEXT	*_nj_current_ctx_;
extern	Uint32			_nj_ctx_color_mode_[NJD_CONTEXT_MAX];
extern	Uint32			*_nj_color_mode_;
extern	KMVERTEXBUFFDESC	_nj_vertex_buffer_;
extern	KMVERTEXCONTEXT	_nj_background_ctx_;

typedef struct LIGHT_BUF_THING
{
	float pad[48];
}LIGHT_BUF_THING;

//kamui structs that are missing from kamui1 but are in kamui2 (possibly differently too, like in the case of systemconfig)
typedef struct NJ_KMSYSTEMCONFIGSTRUCT
{
	int dwSize;
	int field_4;
	int ppSurfaceDescArray;
	int field_12;
	int field_16;
	int field_20;
	int field_24;
	int nTextureMemorySize;
	PKMVERTEXBUFFDESC pBufferDesc;
	int field_36;
	int field_40;
	float field_44;
	float field_48;
	float field_52;
	float field_56;
	float field_60;
	int field_64;
	int field_68;
	int field_72;
	int field_76;
	int field_82;
	int field_86;
	int field_92;
	int field_96;
} NJ_KMSYSTEMCONFIGSTRUCT, *PNJ_KMSYSTEMCONFIGSTRUCT;
/*
 * for PAL Extension Mode
 */
typedef struct _tagKMPALEXTINFO
{
	IN	KMDISPLAYMODE	nDisplayMode;
	OUT	KMINT32			nPALExtMode;
} KMPALEXTINFO,*PKMPALEXTINFO;

extern Int _nj_palext_height_ratio_;

extern DWORD* _nj_debug_char_;
extern int _nj_blank_count_;
extern NJ_KMSYSTEMCONFIGSTRUCT _nj_SystemConfigStruct_;

void kmSetSystemConfiguration(PNJ_KMSYSTEMCONFIGSTRUCT);

extern Uint32 _nj_usr_vertex_buffer_ptr_;
extern Uint32 _nj_usr_vertex_buffer_size_;

void njCharacter(Sint16 x,Sint16 y,Sint8 ch);

/*
 * NJS_LIGHT_QUEUE
 */
typedef struct {
	Int         ltptr[NJD_LIGHT_MAX];
	Int         num;            /* the maximum number of light  */
} NJS_LIGHT_QUEUE;


/*
 * NJS_LIGHT_CONTROLLER
 */
typedef struct {
	NJS_LIGHT_PTR   lt[NJD_LIGHT_MAX];
	Int             ltptr;      /* stack pointer                */
} NJS_LIGHT_CONTROLLER;

extern NJS_LIGHT_QUEUE _nj_light_queue_;
extern NJS_LIGHT_CONTROLLER _nj_light_control_;
extern NJS_LIGHT_MATERIAL _nj_light_material_;


/************************/
/*	 Texture Funcion	*/
/************************/
char *strupr( char *string );

/* njTexFile.c */
Sint32 njTexFopen(const char* filename);
void njTexFclose(void);
void njTexFread(void* buf,Uint32 size);
void njTexFseek(Uint32 size,Uint32 type);
Uint8 *njTexFtell(void);
void njTexFSet(Uint8 *ptr);
void njTexChangeFBuffer(Uint32 size);

/* njTexture.c */
void *njMallocTextureBuffer(Uint32 nbytes);
void njFreeTextureBuffer(Uint32 nbytes);
void *njCacheTextureMalloc(unsigned size);
void njCacheTextureFree(void *block);

Sint32 njLoadTextureLN(NJS_TEXLIST *texlist,Uint32 n);

/* njTexBmp.c */
Sint32 njLoadBmp(NJS_TEXINFO* info,Uint32 attr);
Sint32 njGetSurfaceBmp(NJS_TEXINFO* info,Uint32 attr);
Sint32 njGetInfoBmp(NJS_TEXINFO* info,Uint32 attr);

/* njTexTga.c */
Sint32 njLoadTga(NJS_TEXINFO* info,Uint32 attr);
Sint32 njGetSurfaceTga(NJS_TEXINFO* info,Uint32 attr);
Sint32 njGetInfoTga(NJS_TEXINFO* info,Uint32 attr);

/* njTexPvr.c */
Sint32 njLoadPvr(NJS_TEXINFO* info,Uint32 attr);
Sint32 njGetSurfacePvr(NJS_TEXINFO* info,Uint32 attr);
Sint32 njGetInfoPvr(NJS_TEXINFO* info,Uint32 attr);

/* njTexinner.c */
Sint32 njTexDownloadMipMap(void* addr,NJS_TEXINFO *info);
Sint32 njTexDownloadCache(void *addr,NJS_TEXINFO *info);
void   njTwiddle(Uint16 *dst,Uint16* src,Sint32 size);
Sint32 njCheckFileName(char* namedst,const char* namesrc);
Uint32 njGetFileGlobalIndex(NJS_TEXNAME *texname);

/* njTexLoad.c */
void *njTextureMalloc(NJS_TEXSURFACE *texsurface);
Sint32 njSetTexInfo(Sint32* nTextureType,Sint32 nWidth,Sint32 nHeight,Sint32 bit,Sint32 cn);
Sint32 njCreateTextureSurface(NJS_TEXSURFACE *texsurface,Sint32 nWidth,Sint32 nHeight,Sint32 nTextureType);
Sint32  njLoadTexMemFromFile(NJS_TEXNAME *texname,NJS_TEXINFO *info);
Sint32 njLoadCacheFromFile(NJS_TEXNAME *texname,NJS_TEXINFO *info);
Sint32 njLoadTexMemFromMemory(NJS_TEXNAME *texname,NJS_TEXINFO *info);
Sint32 njLoadTexMemFromCache(NJS_TEXNAME *texname,NJS_TEXINFO *info);
Sint32 njGetInfoMemory(NJS_TEXINFO* info);

/* njTexList.c */
void   njInitTexMemList(NJS_TEXMEMLIST *addr,Uint32 size);
void   njEntryTexMemList(Uint32 *texname_addr,NJS_TEXINFO *info,Uint32 globalIndex,Uint32 type);
void   njFreeTexMemList(NJS_TEXMEMLIST *texmladdr);
NJS_TEXINFO *njTexMemList(Uint32 globalIndex);

Sint32 njSearchTexList(NJS_TEXMEMLIST *texmemlist,Uint32 size,Uint32 globalIndex);
Sint32 njSearchTexList2(NJS_TEXMEMLIST *texmemlist_st,Uint32 size,NJS_TEXMEMLIST *texmemlist);

/* njSetTextureParam.c */
void njSetTextureParam(NJS_TEXMEMLIST *texmemlist);