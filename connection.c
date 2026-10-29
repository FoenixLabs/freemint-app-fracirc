#include "header.h"
#include "fracirc2.h"
OBJECT fr_connection_tree[11];
static TEDINFO password_ted;
static char password[65],mask[65],template[65],valid[]="X";
void fr_connect_tree(OBJECT *original)
{
 short i,cw=original[0].ob_width/48,ch=original[0].ob_height/7;
 memcpy(fr_connection_tree,original,8*sizeof(OBJECT));
 if(cw<1)cw=8;if(ch<1)ch=16;
 fr_connection_tree[0].ob_tail=10;fr_connection_tree[0].ob_height=11*ch;
 for(i=1;i<=7;i++)if(i==1||i==2||i==6||i==7)fr_connection_tree[i].ob_y=9*ch;
 fr_connection_tree[7].ob_flags&=~OF_LASTOB;fr_connection_tree[7].ob_next=8;
 fr_connection_tree[8]=original[5];fr_connection_tree[8].ob_next=9;
 fr_connection_tree[8].ob_flags=OF_EDITABLE;fr_connection_tree[8].ob_state=0;
 fr_connection_tree[8].ob_x=19*cw;fr_connection_tree[8].ob_y=5*ch;
 fr_connection_tree[8].ob_width=27*cw;
 password_ted=*original[5].ob_spec.tedinfo;
 memset(template,'_',64);template[64]=0;
 password_ted.te_just=0;
 password_ted.te_ptext=mask;password_ted.te_ptmplt=template;password_ted.te_pvalid=valid;
 password_ted.te_txtlen=sizeof(mask);password_ted.te_tmplen=sizeof(template);
 fr_connection_tree[8].ob_spec.tedinfo=&password_ted;
 for(i=9;i<=10;i++){
  fr_connection_tree[i]=original[6];fr_connection_tree[i].ob_type=G_STRING;
  fr_connection_tree[i].ob_flags=i==10?OF_LASTOB:0;fr_connection_tree[i].ob_state=0;
  fr_connection_tree[i].ob_next=i==10?0:10;fr_connection_tree[i].ob_head=fr_connection_tree[i].ob_tail=-1;
  fr_connection_tree[i].ob_x=cw;fr_connection_tree[i].ob_y=(i==9?5:7)*ch;
  fr_connection_tree[i].ob_width=46*cw;fr_connection_tree[i].ob_height=ch;
 }
 fr_connection_tree[9].ob_width=18*cw;
 fr_connection_tree[9].ob_spec.free_string="NickServ password:";
 fr_connection_tree[10].ob_spec.free_string="Save setup stores password as plain text.";
}
void fr_password_open(void)
{
 size_t n;
 stccpy(password,conf.nickserv_password,sizeof(password));n=strlen(password);
 memset(mask,'*',n);mask[n]=0;
}
void fr_password_accept(short c)
{
 stccpy(conf.nickserv_password,password,sizeof(conf.nickserv_password));
 stccpy(cn[c].identify_password,password,sizeof(cn[c].identify_password));
 fr_password_cancel();
}
void fr_password_cancel(void)
{
 memset(password,0,sizeof(password));memset(mask,0,sizeof(mask));
}
/* Only stars reach AES; the actual secret never lives in an editable object. */
void fr_password_event(DIALOG *dialog,EVNT *ev)
{
 short pos,obj;unsigned key,ch,scan;size_t n;
 if(dialog!=hsortconnect||!(ev->mwhich&MU_KEYBD))return;
 obj=wdlg_get_edit(dialog,&pos);if(obj!=scpassword)return;
 key=(unsigned short)ev->key;ch=key&255;scan=(key>>8)&255;n=strlen(password);
 if(pos<0)pos=0;if((size_t)pos>n)pos=n;
 if(ch==27){memset(password,0,sizeof(password));return;}
 if(ch==8){if(pos>0)memmove(password+pos-1,password+pos,n-pos+1);return;}
 if(ch==127||scan==0x53){if((size_t)pos<n)memmove(password+pos,password+pos+1,n-pos);return;}
 if(ch==9||ch==13||(!ch&&(scan==0x47||scan==0x4b||scan==0x4d||scan==0x4f)))return;
 if(ch>=33&&ch<=126&&n<sizeof(password)-1){
  memmove(password+pos+1,password+pos,n-pos+1);password[pos]=ch;
  ev->key=(ev->key&0xff00)|'*';return;
 }
 ev->mwhich&=~MU_KEYBD;
}
