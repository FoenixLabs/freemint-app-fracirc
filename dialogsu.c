#include "header.h"
#include "fracirc2.h"
short __stdargs __saveds andabout(DIALOG *dialog,EVNT *events,WORD obj,WORD clicks, void *data);

short is_dw_open(DIALOG *dialog)
{
short i;
for(i=0;i <= 127; i++){
if(dials[i] == dialog)return 1;
}
return 0;
}

void wd_close(DIALOG *dialog)
{
short i=0;
while(i<128){
if(dials[i]==dialog){dials[i]=0;i=130;}
i++;
}
wdlg_close(dialog,0,0);
}

void add_dial(DIALOG *dialog)
{
short i=0;
while(i<128){
if(dials[i]==0){dials[i]=dialog;i=130;}
i++;
}
}
void finishdialogs(void)
{
 DIALOG *all[]={hdccsend,hdomacros,hpathset,habout,hsortconnect,hopenchan,hsetcols,hdisplay,huserset,hserverset,hfontform,hgeneralform,hautonotify,hamacform,hdccfform,htoolbox,hftalk};
 unsigned i;for(i=0;i<sizeof(all)/sizeof(all[0]);i++)if(all[i])wdlg_delete(all[i]);
}

extern short anddccsendform(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddccsendform(struct HNDL_OBJ_args a){return anddccsendform(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short anddomacros(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddomacros(struct HNDL_OBJ_args a){return anddomacros(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andpathset(DIALOG *,EVNT *,short,short,void *);
static short wrap_andpathset(struct HNDL_OBJ_args a){return andpathset(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andabout(DIALOG *,EVNT *,short,short,void *);
static short wrap_andabout(struct HNDL_OBJ_args a){return andabout(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andsortconnect(DIALOG *,EVNT *,short,short,void *);
static short wrap_andsortconnect(struct HNDL_OBJ_args a){return andsortconnect(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andopenchan(DIALOG *,EVNT *,short,short,void *);
static short wrap_andopenchan(struct HNDL_OBJ_args a){return andopenchan(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andsetcols(DIALOG *,EVNT *,short,short,void *);
static short wrap_andsetcols(struct HNDL_OBJ_args a){return andsetcols(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short anddisplay(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddisplay(struct HNDL_OBJ_args a){return anddisplay(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short anduserset(DIALOG *,EVNT *,short,short,void *);
static short wrap_anduserset(struct HNDL_OBJ_args a){return anduserset(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andserverset(DIALOG *,EVNT *,short,short,void *);
static short wrap_andserverset(struct HNDL_OBJ_args a){return andserverset(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andfontform(DIALOG *,EVNT *,short,short,void *);
static short wrap_andfontform(struct HNDL_OBJ_args a){return andfontform(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andgeneralform(DIALOG *,EVNT *,short,short,void *);
static short wrap_andgeneralform(struct HNDL_OBJ_args a){return andgeneralform(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andautonotify(DIALOG *,EVNT *,short,short,void *);
static short wrap_andautonotify(struct HNDL_OBJ_args a){return andautonotify(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andamacform(DIALOG *,EVNT *,short,short,void *);
static short wrap_andamacform(struct HNDL_OBJ_args a){return andamacform(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short anddccfform(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddccfform(struct HNDL_OBJ_args a){return anddccfform(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andtoolbox(DIALOG *,EVNT *,short,short,void *);
static short wrap_andtoolbox(struct HNDL_OBJ_args a){return andtoolbox(a.dialog,a.events,a.obj,a.clicks,a.data);}

extern short andftalk(DIALOG *,EVNT *,short,short,void *);
static short wrap_andftalk(struct HNDL_OBJ_args a){return andftalk(a.dialog,a.events,a.obj,a.clicks,a.data);}
extern short anddcinf0(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddcinf0(struct HNDL_OBJ_args a){return anddcinf0(a.dialog,a.events,a.obj,a.clicks,a.data);}
extern short anddcinf1(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddcinf1(struct HNDL_OBJ_args a){return anddcinf1(a.dialog,a.events,a.obj,a.clicks,a.data);}
extern short anddcinf2(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddcinf2(struct HNDL_OBJ_args a){return anddcinf2(a.dialog,a.events,a.obj,a.clicks,a.data);}
extern short anddcinf3(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddcinf3(struct HNDL_OBJ_args a){return anddcinf3(a.dialog,a.events,a.obj,a.clicks,a.data);}
extern short anddcinf4(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddcinf4(struct HNDL_OBJ_args a){return anddcinf4(a.dialog,a.events,a.obj,a.clicks,a.data);}
extern short anddcinf5(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddcinf5(struct HNDL_OBJ_args a){return anddcinf5(a.dialog,a.events,a.obj,a.clicks,a.data);}
extern short anddcinf6(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddcinf6(struct HNDL_OBJ_args a){return anddcinf6(a.dialog,a.events,a.obj,a.clicks,a.data);}
extern short anddcinf7(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddcinf7(struct HNDL_OBJ_args a){return anddcinf7(a.dialog,a.events,a.obj,a.clicks,a.data);}
extern short anddcinf8(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddcinf8(struct HNDL_OBJ_args a){return anddcinf8(a.dialog,a.events,a.obj,a.clicks,a.data);}
extern short anddcinf9(DIALOG *,EVNT *,short,short,void *);
static short wrap_anddcinf9(struct HNDL_OBJ_args a){return anddcinf9(a.dialog,a.events,a.obj,a.clicks,a.data);}
void initdialogs(void)
{
OBJECT *tree;
if(rsrc_gaddr(R_TREE,dccsendform,&tree))hdccsend=wdlg_create(wrap_anddccsendform,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,macroform,&tree))hdomacros=wdlg_create(wrap_anddomacros,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,pathset,&tree))hpathset=wdlg_create(wrap_andpathset,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,aboutform,&tree))habout=wdlg_create(wrap_andabout,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,sortconnect,&tree)){fr_connect_tree(tree);extern OBJECT fr_connection_tree[];hsortconnect=wdlg_create(wrap_andsortconnect,fr_connection_tree,0L,0,0L,WDLG_BKGD);}
if(rsrc_gaddr(R_TREE,openchanform,&tree))hopenchan=wdlg_create(wrap_andopenchan,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,colourform,&tree))hsetcols=wdlg_create(wrap_andsetcols,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,displayform,&tree))hdisplay=wdlg_create(wrap_anddisplay,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,userset,&tree))huserset=wdlg_create(wrap_anduserset,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,serverset,&tree))hserverset=wdlg_create(wrap_andserverset,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,fontform,&tree))hfontform=wdlg_create(wrap_andfontform,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,generalform,&tree))hgeneralform=wdlg_create(wrap_andgeneralform,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,autonotifylist,&tree))hautonotify=wdlg_create(wrap_andautonotify,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,automacros,&tree))hamacform=wdlg_create(wrap_andamacform,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dccchatform,&tree))hdccfform=wdlg_create(wrap_anddccfform,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,toolbox,&tree))htoolbox=wdlg_create(wrap_andtoolbox,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,ftalkform,&tree))hftalk=wdlg_create(wrap_andftalk,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dcinf0,&tree))dcc[0].dcw=wdlg_create(wrap_anddcinf0,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dcinf1,&tree))dcc[1].dcw=wdlg_create(wrap_anddcinf1,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dcinf2,&tree))dcc[2].dcw=wdlg_create(wrap_anddcinf2,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dcinf3,&tree))dcc[3].dcw=wdlg_create(wrap_anddcinf3,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dcinf4,&tree))dcc[4].dcw=wdlg_create(wrap_anddcinf4,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dcinf5,&tree))dcc[5].dcw=wdlg_create(wrap_anddcinf5,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dcinf6,&tree))dcc[6].dcw=wdlg_create(wrap_anddcinf6,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dcinf7,&tree))dcc[7].dcw=wdlg_create(wrap_anddcinf7,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dcinf8,&tree))dcc[8].dcw=wdlg_create(wrap_anddcinf8,tree,0L,0,0L,WDLG_BKGD);
if(rsrc_gaddr(R_TREE,dcinf9,&tree))dcc[9].dcw=wdlg_create(wrap_anddcinf9,tree,0L,0,0L,WDLG_BKGD);
}
