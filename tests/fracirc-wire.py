#!/usr/bin/env python3
from pathlib import Path
import subprocess,tempfile
root=Path(__file__).resolve().parents[1];src=root
test=r'''
#include "irc_wire.h"
#include <assert.h>
#include <string.h>
int main(void){
 char out[4096],f[10][512],tail[4096],buf[16];size_t n=0;int discard=0,lines=0;const char *p;
 assert(fr_wire_format(out,sizeof(out),":oldnick JOIN #test\r")==12);assert(!strcmp(out,"JOIN #test\r\n"));
 fr_wire_format(out,sizeof(out),"LIST");assert(!strcmp(out,"LIST\r\n"));
 fr_wire_format(out,sizeof(out),":oldnick NICK NewNick\r");assert(!strcmp(out,"NICK NewNick\r\n"));
 assert(fr_wire_parse("\n:Nick!u@host JOIN #test\r\n",f,tail,sizeof(tail)));assert(!strcmp(f[0],"Nick!u@host"));assert(!strcmp(f[1],"JOIN"));assert(!strcmp(f[2],"#test"));
 assert(fr_wire_parse("PING :abc xyz",f,tail,sizeof(tail)));assert(!strcmp(f[1],"PING"));assert(!strcmp(tail,"abc xyz"));
 assert(fr_wire_parse(":server 322 Nick #channel 2 :topic",f,tail,sizeof(tail)));assert(!strcmp(f[3],"#channel"));assert(!strcmp(tail,"topic"));
 for(p="PING :token\r\nNEXT\n";*p;p++)if(fr_wire_feed(buf,sizeof(buf),&n,&discard,*p)){if(!lines)assert(!strcmp(buf,"PING :token"));else assert(!strcmp(buf,"NEXT"));lines++;}
 assert(lines==2);for(p="12345678901234567890\nOK\n";*p;p++)if(fr_wire_feed(buf,sizeof(buf),&n,&discard,*p))assert(!strcmp(buf,"OK"));
 assert(fr_identify_command(out,sizeof(out),"dummy-test-secret"));
 assert(!strcmp(out,"PRIVMSG NickServ :identify dummy-test-secret"));
 assert(!fr_identify_command(out,sizeof(out),""));
 assert(!fr_identify_command(out,sizeof(out),"bad\r\nJOIN #x"));
 assert(!fr_identify_command(out,sizeof(out),"bad secret"));
 assert(!fr_identify_command(out,5,"secret"));
 assert(!fr_wire_format(out,5,"JOIN #x"));return 0;
}
'''
with tempfile.TemporaryDirectory() as tmp:
 p=Path(tmp);(p/'test.c').write_text(test)
 subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror','-Wno-misleading-indentation','-I'+str(src),str(p/'test.c'),str(src/'irc_wire.c'),'-o',str(p/'test')],check=True)
 subprocess.run([str(p/'test')],check=True)
print('PASS: IRC wire framing, prefix normalization, PING/numerics, fragmented lines and overflow recovery')
