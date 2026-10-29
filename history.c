#include "header.h"
/* The VDI renderer keeps a working ring in WIND; these are the owning rings. */
typedef struct {char line[150][200],colour[150];short next,scroll,used;unsigned long revision;} HISTORY;
static HISTORY histories[30+NOFWIN];
static short loaded[NOFWIN],initialized;
static unsigned long revision[NOFWIN];
short fr_output_channel=-2;
short fr_output_visible=1;
static void init(void){short w;if(!initialized){for(w=0;w<NOFWIN;w++)loaded[w]=-1;initialized=1;}}
static short key(short w){return wn[w].chan>=0&&wn[w].chan<30?wn[w].chan:30+w;}
static void load(short w,short k)
{
 memcpy(wn[w].cl,histories[k].line,sizeof(wn[w].cl));memcpy(wn[w].clc,histories[k].colour,sizeof(wn[w].clc));
 wn[w].clused=histories[k].used;wn[w].clcnt=histories[k].next;wn[w].scb=histories[k].scroll;loaded[w]=k;revision[w]=histories[k].revision;
}
void fr_history_sync(short w)
{
 short k;init();if(w<0||w>=NOFWIN)return;k=key(w);
 if(loaded[w]>=0)histories[loaded[w]].scroll=wn[w].scb;
 if(loaded[w]!=k||revision[w]!=histories[k].revision){
  load(w,k);
  if(wn[w].hand>=0)initiateredraw(w,wn[w].wwa.g_x,wn[w].wwa.g_y,wn[w].wwa.g_w-SIDEW,wn[w].wwa.g_h-ith*2-VT+4);
 }
 fr_scroll_update(w);
}
void fr_history_reset(short c)
{
 short w;init();if(c<0||c>=30)return;memset(&histories[c],0,sizeof(HISTORY));
 for(w=0;w<NOFWIN;w++)if(loaded[w]==c)loaded[w]=-1;
}
void fr_history_clear(short w)
{
 short k;init();if(w<0||w>=NOFWIN)return;k=key(w);
 memset(&histories[k],0,sizeof(HISTORY));loaded[w]=-1;fr_history_sync(w);
}
void sendout(char *text,short w,short colour)
{
 short selected,target,visible,added,offset,max;HISTORY *h;
 if(w<0||w>=NOFWIN)return;fr_history_sync(w);selected=key(w);
 target=fr_output_channel>=0&&fr_output_channel<30?fr_output_channel:selected;
 if(target!=selected)load(w,target);
 visible=fr_output_visible;fr_output_visible=target==selected;
 offset=wn[w].scb;added=fr_sendout_lines(text,w,colour);
 wn[w].clused+=added;if(wn[w].clused>150)wn[w].clused=150;
 max=fr_scroll_limit(wn[w].clused,fr_scroll_rows(w));
 if(offset>0){wn[w].scb=offset+added;if(wn[w].scb>max)wn[w].scb=max;}
 else wn[w].scb=0;
 h=&histories[target];memcpy(h->line,wn[w].cl,sizeof(h->line));memcpy(h->colour,wn[w].clc,sizeof(h->colour));
 h->used=wn[w].clused;h->next=wn[w].clcnt;h->scroll=wn[w].scb;h->revision++;revision[w]=h->revision;
 fr_output_visible=visible;
 if(target!=selected)load(w,selected);
 else if(added>0){
  if(!offset)scrollup(w,added);
  else initiateredraw(w,wn[w].wwa.g_x,wn[w].wwa.g_y,wn[w].wwa.g_w-SIDEW,wn[w].wwa.g_h-ith*2-VT+4);
 }
 fr_scroll_update(w);
}
