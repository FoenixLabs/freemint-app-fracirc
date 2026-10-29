#include "header.h"
static short rowheight=16;
static short entries(short hand,short *list)
{
 short n=1,c;list[0]=-1;
 for(c=0;c<30;c++)if(chan[c].stat==2&&chan[c].win>=0&&chan[c].win<NOFWIN&&wn[chan[c].win].cnn==wn[hand].cnn)list[n++]=c;
 return n;
}
static short pagesize(short hand)
{
 short n=(wn[hand].wwa.g_h-ith*2-VT+4)/rowheight-2;return n>0?n:1;
}
void drawchannels(short hand,GRECT box)
{
 short xy[4],list[31],n,i,y,x,cw,ch,cellw,cellh,rows,first;
 if(hand<0||hand>=NOFWIN)return;
 xy[0]=box.g_x;xy[1]=box.g_y;xy[2]=box.g_x+box.g_w-1;xy[3]=box.g_y+box.g_h-1;
 vs_clip(ws.handle,1,xy);clearwin(box.g_x,box.g_y,box.g_w,box.g_h,col[CNLBACK]);
 x=wn[hand].wwa.g_x+wn[hand].wwa.g_w-SIDEW;
 xy[0]=xy[2]=x;xy[1]=wn[hand].wwa.g_y;xy[3]=xy[1]+wn[hand].wwa.g_h-ith*2-VT+3;
 vsl_color(ws.handle,col[CNLDIVIDE]);v_pline(ws.handle,2,xy);
 vst_font(ws.handle,1);vst_point(ws.handle,10,&cw,&ch,&cellw,&cellh);
 rowheight=cellh>0?cellh:16;vst_effects(ws.handle,0);vst_alignment(ws.handle,0,0,&cw,&ch);
 vst_color(ws.handle,col[CNICKLIST]);vswr_mode(ws.handle,MD_TRANS);
 y=wn[hand].wwa.g_y+rowheight;v_gtext(ws.handle,x+6,y,"Joined channels");
 n=entries(hand,list);rows=pagesize(hand);
 if(wn[hand].channel_page<0||wn[hand].channel_page>=n)wn[hand].channel_page=0;
 first=wn[hand].channel_page;
 for(i=first;i<n&&i<first+rows;i++){
  short c=list[i];char label[256];
  y+=rowheight;snprintf(label,sizeof(label),"%s%s",wn[hand].chan==c?"> ":"  ",c<0?"Server":chan[c].name);
  v_gtext(ws.handle,x+6,y,label);
 }
 if(n>rows)v_gtext(ws.handle,x+6,wn[hand].wwa.g_y+(rows+2)*rowheight,"< Prev     Next >");
 vs_clip(ws.handle,0,NULL);
}
int clickchannels(short hand,short x,short y)
{
 short left,list[31],n,row,rows,index,c,w;
 if(hand<0||hand>=NOFWIN)return 0;
 left=wn[hand].wwa.g_x+wn[hand].wwa.g_w-SIDEW;
 if(x<left||x>=left+CLW||y<wn[hand].wwa.g_y||y>=wn[hand].wwa.g_y+wn[hand].wwa.g_h-ith*2-VT+4)return 0;
 if(wind_find(x,y)!=wn[hand].hand)return 0;
 n=entries(hand,list);row=(y-wn[hand].wwa.g_y)/rowheight;rows=pagesize(hand);
 if(row==rows+1&&n>rows){
  index=wn[hand].channel_page+(x-left<CLW/2?-rows:rows);
  if(index>=0&&index<n)wn[hand].channel_page=index;
  nicklistredraw(hand);return 1;
 }
 index=wn[hand].channel_page+row-1;
 if(row<1||row>rows||index<0||index>=n)return 1;
 c=list[index];w=c<0?hand:chan[c].win;
 if(w!=hand){wind_set(wn[w].hand,WF_TOP,0,0,0,0);cwin=w;}
 wn[w].chan=c;dowindinfo(w);nicklistredraw(hand);return 1;
}
