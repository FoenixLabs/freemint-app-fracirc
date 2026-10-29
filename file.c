 /* Fracirc file operations module, 26/1/97 */

#include "header.h"
short writeanurl(char *ps)
{
long fh;
fh=Fopen(path.url,1);
if(fh)Fseek(0,fh,SEEK_END);
if(fh<0){
fh=Fcreate(path.url,0);
Fwrite(fh,29,"+= Fracirc URL-grab list =+\n");
}
if(fh<0){form_alert(1,"[1][Error opening URL file][Oooh!]");return 0;}
Fwrite(fh,(int16)strlen(ps),ps);
Fwrite(fh,2,"\n");
return 0;
}
short openlog()
{
lh=Fopen(path.log,1);
if(lh)Fseek(0,lh,SEEK_END);
if(lh<0){
lh=Fcreate(path.log,0);
logop=1;
tlog("*****Fracirc V1.10 Log file******");
}
if(lh<0){form_alert(1,"[1][Error opening log][Ooh!]");return 0;}
logop=1;
tlog("*****Session opened*****");
return 0;
}

short closelog()
{
tlog("*****Session closed*****");
Fclose(lh);
logop=0;
return 0;
}
short tlog(char *stw)
{
if(logop){
Fwrite(lh,(int16)strlen(stw),stw);
Fwrite(lh,2,"\n");
}
return 0;
}

short loadmacs(char *fn)
{
long th;
char *jp;
short lcount=0,offset=0,sln,ccnt=0;
char temps[2048];
if(fn!=NULL)th=Fopen(fn,0);
if(fn==NULL)th=Fopen("FRACIRC.MCR",0);
if(th<0 && fn!=NULL){form_alert(1,"[1][File error][Oooh!]");return 0;}
if(th<0 && fn==NULL){return 0;}
Fread(th,1500,temps);
jp=temps;
sln=(int16)strlen(temps)+1;

while(offset<sln){
if(*(jp+lcount)=='Ý'){
*(jp+lcount)=0;strcpy(macs[ccnt],jp);jp=jp+lcount+1;lcount=-1;ccnt++;
}
if(ccnt==10)offset=sln;
offset++;
lcount++;
}
Fclose(th);
return 0;
}

short loadwins(char *fn)
{
long th;
short mcto=0;
short x,no;
if(fn!=NULL)th=Fopen(fn,0);
if(fn==NULL)th=Fopen("FRACIRC.WIN",0);
if(th<0 && fn!=NULL){form_alert(1,"[1][Windows: File error][Oooh!]");return 0;}
if(th<0 && fn==NULL){return 0;}
mcto=0;
while(mcto<NOFWIN){
Fread(th,2,&no);
Fread(th,2,&wn[mcto].wwa.g_x);
Fread(th,2,&wn[mcto].wwa.g_y);
Fread(th,2,&wn[mcto].wwa.g_w);
Fread(th,2,&wn[mcto].wwa.g_h);
flag=FALSE;
if(wn[mcto].hand==-1 && no>-1){openwin(wn[mcto].wwa.g_x,wn[mcto].wwa.g_y,wn[mcto].wwa.g_w,wn[mcto].wwa.g_h,0);flag=TRUE;}
if(wn[mcto].hand>-1 && !flag && no>-1){resizewindow(mcto,wn[mcto].wwa.g_x,wn[mcto].wwa.g_y,wn[mcto].wwa.g_w,wn[mcto].wwa.g_h,0);}
mcto++;
}
Fread(th,2,&x);
topwindow(x);
Fclose(th);
return 0;
}

short savmacs(char *fn)
{
long th;
char temps[2048];
th=Fcreate(fn,0);
if(th<0){form_alert(1,"[1][File error][Oooee!]");return 0;}
strcpy(temps,"\0");
strcpy(temps,macs[0]);strcat(temps,"Ý");
strcat(temps,macs[1]);strcat(temps,"Ý");
strcat(temps,macs[2]);strcat(temps,"Ý");
strcat(temps,macs[3]);strcat(temps,"Ý");
strcat(temps,macs[4]);strcat(temps,"Ý");
strcat(temps,macs[5]);strcat(temps,"Ý");
strcat(temps,macs[6]);strcat(temps,"Ý");
strcat(temps,macs[7]);strcat(temps,"Ý");
strcat(temps,macs[8]);strcat(temps,"Ý");
strcat(temps,macs[9]);strcat(temps,"Ý");
Fwrite(th,strlen(temps),temps);
Fclose(th);
return 0;
}

short savwins(char *fn)
{
long th;
GRECT ws;
short mcto=0;
th=Fcreate(fn,0);
if(th<0){form_alert(1,"[1][File error][Oooee!]");return 0;}
while(mcto<6){
wind_get(wn[mcto].hand,WF_CURRXYWH,&ws.g_x,&ws.g_y,&ws.g_w,&ws.g_h);
Fwrite(th,2,&wn[mcto].hand);
Fwrite(th,2,&ws.g_x);
Fwrite(th,2,&ws.g_y);
Fwrite(th,2,&ws.g_w);
Fwrite(th,2,&ws.g_h);
mcto++;
}
Fwrite(th,2,&cwin);
Fclose(th);
return 0;
}

