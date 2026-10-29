#include "history_scroll.h"
short fr_scroll_limit(short used,short rows){if(rows<1)rows=1;return used>rows?used-rows:0;}
short fr_scroll_thumb(short used,short rows){if(rows<1)rows=1;return used<=rows?1000:(short)((long)rows*1000/used);}
short fr_scroll_position(short offset,short used,short rows)
{
 short max=fr_scroll_limit(used,rows);if(!max)return 1000;
 if(offset<0)offset=0;if(offset>max)offset=max;return 1000-(short)((long)offset*1000/max);
}
short fr_scroll_offset(short position,short used,short rows)
{
 if(position<0)position=0;if(position>1000)position=1000;
 return (short)(((long)(1000-position)*fr_scroll_limit(used,rows)+500)/1000);
}
