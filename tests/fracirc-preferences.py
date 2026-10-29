#!/usr/bin/env python3
"""Exercise the actual FracIRC preference parser/writer with host libc."""
from pathlib import Path
import tempfile,subprocess
root=Path(__file__).resolve().parents[1]
src=root/'preferences.c'
code='\n'.join(l for l in src.read_text().splitlines() if not l.startswith('#include'))
stub=r'''
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
struct {char snick[20],snick2[20],nickserv_password[65],amaj1[15],amaj2[15];} conf;
char irc_server[4][100],irc_port[4][20],username[128],realname[128],hostname[128];
struct {char dcc[512],sound[512],url[512],log[512];} path;
int form_alert(int a,const char *b){(void)a;(void)b;return 1;}
size_t stccpy(char *d,const char *s,size_t n){size_t x=strlen(s);if(x>=n)x=n-1;memcpy(d,s,x);d[x]=0;return x;}
'''
test=r'''
int main(void){
 FILE *f;strcpy(conf.snick,"FnxFrac");strcpy(irc_server[0],"irc.libera.chat");strcpy(irc_port[0],"6667");
 strcpy(conf.nickserv_password,"example-secret");
 assert(!savprefs("prefs.inf"));conf.nickserv_password[0]=0;strcpy(conf.snick,"changed");irc_server[0][0]=0;
 loadprefs("prefs.inf");assert(!strcmp(conf.nickserv_password,"example-secret"));assert(!strcmp(conf.snick,"FnxFrac"));assert(!strcmp(irc_server[0],"irc.libera.chat"));
 f=fopen("long.inf","w");fputs("unknown=ignored\nnick=abcdefghijklmnopqrstuvwxyz1234567890\nserver0=irc.example.test\r\n",f);fclose(f);
 loadprefs("long.inf");assert(strlen(conf.snick)==19);assert(!strcmp(irc_server[0],"irc.example.test"));
 loadprefs(NULL);assert(strlen(conf.snick)==19);return 0;
}
'''
with tempfile.TemporaryDirectory() as t:
 p=Path(t);(p/'test.c').write_text(stub+code+test)
 subprocess.run(['cc','-Wall','-Wextra','-Werror',str(p/'test.c'),'-o',str(p/'test')],check=True)
 subprocess.run([str(p/'test')],cwd=p,check=True)
print('PASS: FracIRC preference roundtrip, unknown keys, bounds, CRLF and missing defaults')
