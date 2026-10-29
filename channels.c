/* Channel routines (incorporating parts of DCC chat) */

#include "header.h"

/* Use VDI font metrics rather than assuming an eight-pixel line. */
void drawnicklist(short hand,GRECT box)
{
 short xy[4],cw,ch,cellw,cellh,y,i,c;
 if(hand<0||hand>=NOFWIN)return;
 xy[0]=box.g_x;xy[1]=box.g_y;xy[2]=box.g_x+box.g_w-1;xy[3]=box.g_y+box.g_h-1;
 vs_clip(ws.handle,1,xy);
 clearwin(box.g_x,box.g_y,box.g_w,box.g_h,col[CNLBACK]);
 xy[0]=xy[2]=wn[hand].wwa.g_x+wn[hand].wwa.g_w-NLW;
 xy[1]=wn[hand].wwa.g_y;xy[3]=xy[1]+wn[hand].wwa.g_h-ith*2-VT+3;
 vsl_color(ws.handle,col[CNLDIVIDE]);v_pline(ws.handle,2,xy);
 c=wn[hand].chan;
 if(c>=0&&c<30){
  vst_font(ws.handle,1);vst_point(ws.handle,10,&cw,&ch,&cellw,&cellh);
  if(cellh<1)cellh=16;
  vst_effects(ws.handle,0);vst_alignment(ws.handle,0,0,&cw,&ch);
  vst_color(ws.handle,col[CNICKLIST]);vswr_mode(ws.handle,MD_TRANS);
  y=wn[hand].wwa.g_y+cellh;
  for(i=0;i<FR_USER_LIMIT;i++)if(chan[c].nl[i][0]){
   if(y>xy[3])break;
   v_gtext(ws.handle,xy[0]+6,y,chan[c].nl[i]);y+=cellh;
  }
 }
 vs_clip(ws.handle,0,NULL);
}

void nicklistredraw(short hand)
{
 if(hand<0||hand>=NOFWIN||wn[hand].hand<0)return;
 initiateredraw(hand,wn[hand].wwa.g_x+wn[hand].wwa.g_w-SIDEW,
  wn[hand].wwa.g_y,SIDEW,wn[hand].wwa.g_h-ith*2-VT+4);
}

void alternickto(char *nick,char *newnick)
{
 short c;
 for(c=0;c<30;c++)if(chan[c].stat==2){
  fr_users_change(chan[c].nl,&chan[c].nn,nick,newnick);
  nicklistredraw(chan[c].win);
 }
}
void closchan(short cnum)
{
BOOLEAN aflag=FALSE;
short mcto=0;
char temps[2048];
if(chan<0){
form_alert(1,"[1][You're not in|a channel!][ooops!]");
return;
}
while(mcto<30 && !aflag){
if(cnum!=mcto && chan[mcto].win==chan[cnum].win){wn[chan[cnum].win].chan=mcto;aflag=TRUE;}
mcto++;
}
if(!aflag){
wn[chan[cnum].win].chan=-1;
dowindinfo(chan[cnum].win);
cycchan(FORWARDS);
}
if(chan[cnum].stat==2){
sprintf(temps,":%s PART %s\r",cn[wn[chan[cnum].win].cnn].nick,chan[cnum].name);
srt(temps,cn[wn[chan[cnum].win].cnn].cn);
}
if(chan[cnum].stat>2)closedccchat(cnum);
chan[cnum].stat=0;
fr_history_reset(cnum);
memset(chan[cnum].nl,0,sizeof(chan[cnum].nl));chan[cnum].nn=0;chan[cnum].names_pending=0;
if(aflag)dowindinfo(chan[cnum].win);
chan[cnum].win=-1;
return;
}



short findfreechannel(void)
{
short mcto=0;
if(cwin==-1)return -1;
while(mcto<30){
if(!chan[mcto].stat){return mcto;}
mcto++;
}
return -1;
}
short findthechannel(char *nch)
{
short mcto=0;
if(cwin==-1)return -1;
while(mcto<30){
if(chan[mcto].stat==1 && !stricmp(chan[mcto].name,nch)){return mcto;}
mcto++;
}
return -1;
}

short getchanhan(char *p)
{
short mcto=29;
while(mcto>-1){
if(!stricmp(chan[mcto].name,p) && chan[mcto].stat)return mcto;
mcto--;
}
return -1;
}

short citw(char *p, short twin)
{
short mcto=0;
while(mcto<30){
if(!stricmp(p,chan[mcto].name)){
if(wn[chan[mcto].win].hand>-1 && wn[twin].cnn==wn[chan[mcto].win].cnn){return chan[mcto].win;}
}
mcto++;
}
return -1;
}

short findlastchannel(void)
{
short counter=0;
short se;
se=wn[cwin].chan-1;
if(se<0 || se>29)se=29;
if(chan[se].stat>1)return se;
while(chan[se].stat<2 ){
se--;
counter++;
if(counter==31)return -1;
if(se<0)se=29;
}
return se;
}

short findnextchannel(void)
{
short counter=0;
short se;
se=wn[cwin].chan+1;
if(se<0 || se>29)se=0;
if(chan[se].stat>1)return se;
while(chan[se].stat<2){
se++;
counter++;
if(counter==31)return -1;
if(se>29){se=0;}
}
return se;
}	

short cycchan(short dri)
{
short ret;
short junk=0;
if(dri==FORWARDS){
ret=findnextchannel();
if(ret==-1)return -1;
}
if(dri==BACKWARDS){
ret=findlastchannel();
if(ret==-1)return -1;
}
if(ret>-1 && chan[ret].win!=cwin){
wind_set(wn[chan[ret].win].hand,WF_TOP,junk,junk,junk,junk);
cwin=chan[ret].win;
}
wn[cwin].chan=ret;
dowindinfo(cwin);
return 0;
}
