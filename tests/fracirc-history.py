#!/usr/bin/env python3
"""Exercise actual history ownership and background routing, independent of GEM."""
from pathlib import Path
import tempfile,subprocess
root=Path(__file__).resolve().parents[1]
code=(root/'history.c').read_text().replace('#include "header.h"','')
stub=r'''
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "history_scroll.h"
#define NOFWIN 6
#define SIDEW 400
#define VT 15
struct {short chan,hand,clcnt,scb,clused;char cl[150][200],clc[150];struct {short g_x,g_y,g_w,g_h;} wwa;} wn[6];
short ith=8;int redraws,visible_writes;
void initiateredraw(short w,short x,short y,short width,short height){redraws++;}
extern short fr_output_visible;
short fr_sendout_lines(char *s,short w,short col){strcpy(wn[w].cl[wn[w].clcnt],s);wn[w].clc[wn[w].clcnt]=col;wn[w].clcnt=(wn[w].clcnt+1)%150;visible_writes+=fr_output_visible;return 1;}
short fr_scroll_rows(short w){return 1;}
void fr_scroll_update(short w){short m=fr_scroll_limit(wn[w].clused,1);if(wn[w].scb>m)wn[w].scb=m;}
void scrollup(short w,short n){}
'''
test=r'''
int main(void){
 int i;char s[30];wn[0].chan=-1;wn[0].hand=10;
 sendout("server welcome",0,1);
 wn[0].chan=0;fr_history_sync(0);assert(!wn[0].clcnt&&!wn[0].cl[0][0]);
 sendout("channel A",0,2);sendout("older A",0,2);wn[0].scb=1;
 wn[0].chan=1;fr_history_sync(0);assert(!wn[0].clcnt);
 sendout("channel B",0,3);
 fr_output_channel=0;sendout("background A",0,4);fr_output_channel=-2;
 assert(wn[0].clcnt==1&&!strcmp(wn[0].cl[0],"channel B"));assert(visible_writes==4);
 wn[0].chan=0;fr_history_sync(0);assert(wn[0].clcnt==3&&wn[0].scb==2&&wn[0].clused==3);
 assert(!strcmp(wn[0].cl[2],"background A")&&wn[0].clc[2]==4);
 fr_history_clear(0);assert(!wn[0].clcnt&&!wn[0].scb&&!wn[0].cl[0][0]);
 wn[0].chan=1;fr_history_sync(0);assert(!strcmp(wn[0].cl[0],"channel B"));
 wn[0].chan=-1;fr_history_sync(0);assert(!strcmp(wn[0].cl[0],"server welcome"));
 wn[0].chan=0;fr_history_sync(0);
 for(i=0;i<160;i++){sprintf(s,"line %d",i);sendout(s,0,1);}
 assert(wn[0].clcnt==10&&!strcmp(wn[0].cl[9],"line 159"));
 fr_history_reset(0);fr_history_sync(0);assert(!wn[0].clcnt&&!wn[0].cl[0][0]);
 assert(redraws>3);return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
 p=Path(d);(p/'test.c').write_text(stub+code+test)
 subprocess.run(['cc','-Wall','-Wextra','-Werror','-Wno-unused-parameter','-Wno-misleading-indentation','-I'+str(root),str(p/'test.c'),str(root/'history_scroll.c'),'-o',str(p/'test')],check=True)
 subprocess.run([str(p/'test')],check=True)
print('PASS: separate server/channel histories, background routing, scroll state, selected clear and ring wrap')
