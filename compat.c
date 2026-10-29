#include "compat.h"
struct fnx_gempar fnx_gempar={0,aes_global,0,0,0,0};
size_t stccpy(char *dst,const char *src,size_t size)
{
 size_t n;if(!size)return 0;n=strlen(src);if(n>=size)n=size-1;memcpy(dst,src,n);dst[n]=0;return n;
}
void stcl_d(char *dst,long value){sprintf(dst,"%ld",value);}
void objc_xywh(OBJECT *tree,short obj,GRECT *r)
{objc_offset(tree,obj,&r->g_x,&r->g_y);r->g_w=tree[obj].ob_width;r->g_h=tree[obj].ob_height;}
long getcookie(long tag,long *value){return Getcookie(tag,value)==0;}
int dfind(struct _dta *info,const char *path,int attr)
{void *old=Fgetdta();long ret;Fsetdta(info);ret=Fsfirst(path,attr);Fsetdta(old);return ret;}
int dnext(struct _dta *info)
{void *old=Fgetdta();long ret;Fsetdta(info);ret=Fsnext();Fsetdta(old);return ret;}
