/* Scrolling code (includes scrollback functions)*/
#include "header.h"


short fr_scroll_rows(short w)
{
 short rows=(wn[w].wwa.g_h-ith*2-VT)/(th>0?th:16);
 return rows>0?rows:1;
}
void fr_scroll_update(short w)
{
 short max;if(w<0||w>=NOFWIN||wn[w].hand<0)return;
 wn[w].hght=fr_scroll_rows(w);max=fr_scroll_limit(wn[w].clused,wn[w].hght);
 if(wn[w].scb<0)wn[w].scb=0;if(wn[w].scb>max)wn[w].scb=max;
 wind_set(wn[w].hand,WF_VSLSIZE,fr_scroll_thumb(wn[w].clused,wn[w].hght),0,0,0);
 wind_set(wn[w].hand,WF_VSLIDE,fr_scroll_position(wn[w].scb,wn[w].clused,wn[w].hght),0,0,0);
}
static void set_offset(short w,short offset)
{
 if(w<0||w>=NOFWIN)return;
 wn[w].scb=offset;fr_scroll_update(w);
 initiateredraw(w,wn[w].wwa.g_x,wn[w].wwa.g_y,wn[w].wwa.g_w-SIDEW,wn[w].wwa.g_h-ith*2-VT+4);
}
void fr_scroll_to(short w,short position)
{
 if(w<0||w>=NOFWIN)return;
 set_offset(w,fr_scroll_offset(position,wn[w].clused,fr_scroll_rows(w)));
}
void fr_scroll_by(short w,short amount)
{
 if(w<0||w>=NOFWIN)return;set_offset(w,wn[w].scb+amount);
}
short sbvslid(short position){fr_scroll_to(cwin,position);return 0;}
void drawvslid(void){fr_scroll_update(cwin);}
short scrollbbk(void){fr_scroll_by(cwin,-1);return 0;}
short scrollback(void){fr_scroll_by(cwin,1);return 0;}

void scrolldown(void)
{
short xy[8];
startupdate();
xy[0]=wn[cwin].wwa.g_x;xy[1]=wn[cwin].wwa.g_y;
xy[2]=wn[cwin].wwa.g_x+wn[cwin].wwa.g_w-1;xy[3]=wn[cwin].wwa.g_y+wn[cwin].wwa.g_h-ith*2-VT-th;
xy[4]=wn[cwin].wwa.g_x;xy[5]=wn[cwin].wwa.g_y+th;
xy[6]=wn[cwin].wwa.g_x+wn[cwin].wwa.g_w-1;xy[7]=wn[cwin].wwa.g_y+wn[cwin].wwa.g_h-ith*2-VT;
vro_cpyfm(ws.handle,S_ONLY,xy,&scr,&scr);
xy[0]=wn[cwin].wwa.g_x;xy[1]=wn[cwin].wwa.g_y;
xy[2]=wn[cwin].wwa.g_x+wn[cwin].wwa.g_w-1;xy[3]=wn[cwin].wwa.g_y;
xy[6]=wn[cwin].wwa.g_x;xy[7]=wn[cwin].wwa.g_y+th;
xy[4]=wn[cwin].wwa.g_x+wn[cwin].wwa.g_w-1;xy[5]=wn[cwin].wwa.g_y+th;
v_fillarea(ws.handle,4,xy);
finishupdate();
}


void scrollup(short hand, short howmany)
{
GRECT box;
GRECT area;
short xy[8],temp;
area.g_x=wn[hand].wwa.g_x;
area.g_y=wn[hand].wwa.g_y;
area.g_w=wn[hand].wwa.g_w-SIDEW;
area.g_h=wn[hand].wwa.g_h-ith*2-VT+3;
if(wn[hand].stat==WMDONTWRITE)return;
startupdate();
wind_get(wn[hand].hand,WF_FIRSTXYWH,&box.g_x,&box.g_y,&box.g_w,&box.g_h);
while (box.g_w && box.g_h){
if(rc_intersect(&area,&box)){
temp=th*howmany;
if(temp>box.g_h)temp=box.g_h;
xy[0]=box.g_x;xy[1]=box.g_y+temp;
xy[2]=box.g_x+box.g_w-1;xy[3]=box.g_y+box.g_h-1;
xy[4]=box.g_x;xy[5]=box.g_y;
xy[6]=box.g_x+box.g_w-1;xy[7]=box.g_y+box.g_h-temp;
vro_cpyfm(ws.handle,S_ONLY,xy,&scr,&scr);
box.g_y=box.g_y+box.g_h-temp;
box.g_h=temp+1;
dodirty(hand,box);
}
wind_get(wn[hand].hand,WF_NEXTXYWH,&box.g_x,&box.g_y,&box.g_w,&box.g_h);
}
finishupdate();
return;
}

void dodirty(short hand,GRECT box)
{
 short xy[4],row,age,index,rows=fr_scroll_rows(hand);
 xy[0]=box.g_x;xy[1]=box.g_y;xy[2]=box.g_x+box.g_w-1;xy[3]=box.g_y+box.g_h-1;
 vs_clip(ws.handle,1,xy);clearwin(box.g_x,box.g_y,box.g_w,box.g_h,col[CBACK]);
 vswr_mode(ws.handle,MD_TRANS);
 for(row=0;row<rows;row++){
  age=wn[hand].scb+row;if(age>=wn[hand].clused)break;
  index=wn[hand].clcnt-1-age;while(index<0)index+=150;
  writeoutput(hand,wn[hand].cl[index],row,wn[hand].clc[index]);
 }
 vs_clip(ws.handle,0,NULL);
}
