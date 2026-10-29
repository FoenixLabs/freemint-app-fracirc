#!/usr/bin/env python3
from pathlib import Path
import tempfile,subprocess
root=Path(__file__).resolve().parents[1]
code=(root/'channelview.c').read_text().replace('#include "header.h"','')
stub=r'''
#include <assert.h>
#include <stdio.h>
#include <string.h>
#define NOFWIN 6
#define CLW 200
#define SIDEW 400
#define NLW 200
#define VT 15
#define CNLBACK 13
#define CNLDIVIDE 16
#define CNICKLIST 12
#define MD_TRANS 2
#define WF_TOP 21
#define vs_clip(...) ((void)0)
#define clearwin(...) ((void)0)
#define vsl_color(...) ((void)0)
#define v_pline(...) ((void)0)
#define vst_font(...) ((void)0)
#define vst_point(h,p,a,b,c,d) (*(d)=16)
#define vst_effects(...) ((void)0)
#define vst_alignment(...) ((void)0)
#define vst_color(...) ((void)0)
#define vswr_mode(...) ((void)0)
#define wind_set(...) ((void)0)
#define nicklistredraw(...) ((void)0)
#define dowindinfo(...) ((void)0)
typedef struct {short g_x,g_y,g_w,g_h;} GRECT;
struct {GRECT wwa;short chan,cnn,hand,channel_page;} wn[6];
struct {short stat,win;char name[201];} chan[30];
short ith=8,cwin=0,found=10;char labels[40][256];int label_count;
short wind_find(short x,short y){return found;}
void v_gtext(short h,short x,short y,const char *s){snprintf(labels[label_count++],256,"%s",s);}
struct {short handle;} ws;
char col[25];
'''
test=r'''
int main(void){
 short list[31],i;GRECT box={400,0,200,300};
 wn[0].wwa=(GRECT){0,0,800,300};wn[0].hand=10;wn[0].cnn=0;wn[0].chan=0;
 wn[1].cnn=0;wn[1].hand=11;wn[2].cnn=1;
 chan[0].stat=2;chan[0].win=0;strcpy(chan[0].name,"#one");
 chan[1].stat=2;chan[1].win=1;strcpy(chan[1].name,"#two");
 chan[2].stat=2;chan[2].win=2;strcpy(chan[2].name,"#other-server");
 chan[3].stat=1;chan[3].win=0;
 assert(entries(0,list)==3&&list[0]==-1&&list[1]==0&&list[2]==1);
 drawchannels(0,box);assert(!strcmp(labels[2],"> #one"));
 assert(!clickchannels(0,650,30));assert(clickchannels(0,410,50));
 assert(cwin==1&&wn[1].chan==1);
 found=99;assert(!clickchannels(0,410,20));found=10;
 for(i=0;i<30;i++){chan[i].stat=2;chan[i].win=0;}
 wn[0].wwa.g_h=160;assert(pagesize(0)==6);
 assert(clickchannels(0,550,7*16+1));assert(wn[0].channel_page==6);
 assert(clickchannels(0,410,7*16+1));assert(wn[0].channel_page==0);
 return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
 p=Path(d);(p/'test.c').write_text(stub+code+test)
 subprocess.run(['cc','-std=c99','-Wno-unused-variable',str(p/'test.c'),'-o',str(p/'test')],check=True)
 subprocess.run([str(p/'test')],check=True)
print('PASS: joined channel filtering, active selection, click routing and pagination')
