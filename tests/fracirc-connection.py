#!/usr/bin/env python3
from pathlib import Path
import tempfile,subprocess
root=Path(__file__).resolve().parents[1];src=root
code='\n'.join(s for s in (src/'connection.c').read_text().splitlines() if not s.startswith('#include'))
stub=r'''
#include <assert.h>
#include <stdio.h>
#include <string.h>
#define NOFWIN 6
#define scpassword 8
#define OF_LASTOB 32
#define OF_EDITABLE 8
#define G_STRING 28
#define MU_KEYBD 1
struct dialog {int unused;};typedef struct dialog DIALOG;
typedef struct {char *te_ptext,*te_ptmplt,*te_pvalid;short te_txtlen,te_tmplen,te_just;} TEDINFO;
typedef struct {short ob_next,ob_head,ob_tail,ob_type,ob_flags,ob_state;union {TEDINFO *tedinfo;char *free_string;} ob_spec;short ob_x,ob_y,ob_width,ob_height;} OBJECT;
typedef struct {short mwhich,key;} EVNT;
struct {char nickserv_password[65];} conf;
struct {char identify_password[65];} cn[6];
DIALOG dialog,*hsortconnect=&dialog;
short cursor=0;
short wdlg_get_edit(DIALOG *d,short *pos){*pos=cursor;return scpassword;}
size_t stccpy(char *d,const char *s,size_t n){size_t l=strlen(s);if(l>=n)l=n-1;memcpy(d,s,l);d[l]=0;return l;}
void fr_password_cancel(void);
'''
test=r'''
int main(void){
 OBJECT tree[8]={0};TEDINFO base={0};EVNT ev;char input[]="dummy-test-secret";unsigned i;
 tree[0].ob_width=384;tree[0].ob_height=112;tree[5].ob_spec.tedinfo=&base;
 fr_connect_tree(tree);assert(fr_connection_tree[0].ob_tail==10);assert(password_ted.te_just==0);
 assert(fr_connection_tree[9].ob_x+fr_connection_tree[9].ob_width<=fr_connection_tree[8].ob_x);
 assert(fr_connection_tree[8].ob_spec.tedinfo->te_ptext!=password);
 assert(fr_connection_tree[8].ob_flags&OF_EDITABLE);
 assert(fr_connection_tree[10].ob_flags&OF_LASTOB);
 fr_password_open();
 for(i=0;i<strlen(input);i++){
  cursor=i;ev.mwhich=MU_KEYBD;ev.key=input[i];fr_password_event(hsortconnect,&ev);
  assert((ev.key&255)=='*');mask[i]='*';mask[i+1]=0;
 }
 assert(!strcmp(password,input));assert(!strstr(mask,input));
 fr_password_accept(0);assert(!strcmp(conf.nickserv_password,input));assert(!strcmp(cn[0].identify_password,input));assert(!*password&&!*mask);
 fr_password_open();assert(strlen(mask)==strlen(input));
 cursor=5;ev.mwhich=MU_KEYBD;ev.key=8;fr_password_event(hsortconnect,&ev);
 assert(!strcmp(password,"dumm-test-secret"));
 ev.key=0x537f;fr_password_event(hsortconnect,&ev);assert(!strcmp(password,"dumm-est-secret"));
 ev.key=22;fr_password_event(hsortconnect,&ev);assert(!(ev.mwhich&MU_KEYBD));
 ev.mwhich=MU_KEYBD;ev.key=27;fr_password_event(hsortconnect,&ev);assert(!*password);
 fr_password_cancel();assert(!*mask);return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
 p=Path(d);(p/'test.c').write_text(stub+code+test)
 subprocess.run(['cc','-Wall','-Wextra','-Werror','-Wno-unused-parameter','-Wno-misleading-indentation',str(p/'test.c'),'-o',str(p/'test')],check=True)
 subprocess.run([str(p/'test')],check=True)
print('PASS: connection password masking, saved reload, cursor editing, cancel and clipboard guard')
