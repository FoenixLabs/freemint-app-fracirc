#ifndef FNX_FRAC_COMPAT_H
#define FNX_FRAC_COMPAT_H
#include <gem.h>
#include <gemx.h>
#include <mint/basepage.h>
#include <mint/dcntl.h>
#include <mint/ostruct.h>
#define __MTAES__
#define __stdargs
#define __saveds
#define far
typedef BASEPAGE BASPAG;
#include <mint/osbind.h>
#include <mint/mintbind.h>
#include <mint/cookie.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "portab.h"
#include "transprt.h"
#include "vdiws.h"
#define WORD short
#define CJTAG "STiK"
#define LONG long
#define BYTE char
#define UWORD unsigned short
#define ULONG unsigned long
typedef unsigned char UBYTE;
struct fnx_gempar {short *contrl,*global,*intin,*intout;void **addrin,**addrout;};
extern struct fnx_gempar fnx_gempar;
#define GemParBlk fnx_gempar
typedef short BOOLEAN;
#define DISABLED OS_DISABLED
#define AD3DVALUE 6
#define FL3DIND 0x0200
#define FL3DMASK 0x0600
#define WHITEBAK OS_WHITEBAK
#define SELECTED OS_SELECTED
#define CHECKED OS_CHECKED
#define THICKENED 1
#define UNDERLINED 8
#define OUTLINED 16
#define FNSIZE 512
#define FMSIZE 128
#define BLACK 1
#define RBUTTON OF_RBUTTON
#define wind_title(h,s) wind_set_str(h,WF_NAME,s)
#define wind_info(h,s) wind_set_str(h,WF_INFO,s)
#define _DTA struct _dta
#define contrl control
#define global global
#define appl_id gl_apid
size_t stccpy(char *,const char *,size_t);
void stcl_d(char *,long);
void objc_xywh(OBJECT *,short,GRECT *);
long getcookie(long,long *);
int dfind(struct _dta *,const char *,int);
int dnext(struct _dta *);
#undef wind_create
#define wind_create(k,r) mt_wind_create(k,(r)->g_x,(r)->g_y,(r)->g_w,(r)->g_h,aes_global)
#undef wind_open
#define wind_open(h,r) mt_wind_open(h,(r)->g_x,(r)->g_y,(r)->g_w,(r)->g_h,aes_global)
#undef wind_get_grect
#define wind_get_grect(h,f,r) wind_get(h,f,&(r)->g_x,&(r)->g_y,&(r)->g_w,&(r)->g_h)
#endif
