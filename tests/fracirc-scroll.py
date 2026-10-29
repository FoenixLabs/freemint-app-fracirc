#!/usr/bin/env python3
from pathlib import Path
import tempfile,subprocess
root=Path(__file__).resolve().parents[1];src=root
test=r'''
#include "history_scroll.h"
#include <assert.h>
#include <stdlib.h>
int main(void){
 short used,rows,offset,max,p;
 assert(fr_scroll_thumb(0,50)==1000);assert(fr_scroll_thumb(3,50)==1000);
 assert(fr_scroll_thumb(150,50)==333);assert(fr_scroll_thumb(100,50)==500);
 assert(fr_scroll_limit(51,50)==1);assert(fr_scroll_limit(3,50)==0);
 for(used=0;used<=150;used++)for(rows=1;rows<=160;rows++){
  max=fr_scroll_limit(used,rows);
  assert(fr_scroll_offset(1000,used,rows)==0);
  assert(fr_scroll_offset(0,used,rows)==max);
  for(offset=0;offset<=max;offset++){
   p=fr_scroll_position(offset,used,rows);assert(p>=0&&p<=1000);
   assert(fr_scroll_offset(p,used,rows)==offset);
  }
 }
 assert(fr_scroll_offset(-100,150,50)==100);
 assert(fr_scroll_offset(1100,150,50)==0);
 assert(fr_scroll_position(500,150,50)==0);return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
 p=Path(d);(p/'test.c').write_text(test)
 subprocess.run(['cc','-Wall','-Wextra','-Werror','-Wno-misleading-indentation','-I'+str(src),str(p/'test.c'),str(src/'history_scroll.c'),'-o',str(p/'test')],check=True)
 subprocess.run([str(p/'test')],check=True)
print('PASS: proportional scrollbar size, exact position mapping, empty/short/full history and viewport bounds')
