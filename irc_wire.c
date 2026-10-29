#include "irc_wire.h"
#include <string.h>
size_t fr_wire_format(char *out,size_t cap,const char *in)
{
 size_t n;while(*in==' '||*in=='\r'||*in=='\n')in++;
 if(*in==':'){in=strchr(in,' ');if(!in)return 0;while(*in==' ')in++;}
 n=strcspn(in,"\r\n");if(!n||n+3>cap)return 0;
 memcpy(out,in,n);out[n++]='\r';out[n++]='\n';out[n]=0;return n;
}
int fr_wire_parse(const char *in,char fields[10][512],char *tail,size_t cap)
{
 const char *end;size_t n;int i=1;memset(fields,0,10*512);if(!cap)return 0;tail[0]=0;
 while(*in=='\r'||*in=='\n'||*in==' ')in++;
 if(*in==':'){
  in++;end=strchr(in,' ');if(!end)return 0;n=end-in;if(n>=512)return 0;
  memcpy(fields[0],in,n);in=end;
 }
 while(*in&&i<10){
  while(*in==' ')in++;if(!*in||*in=='\r'||*in=='\n')break;
  if(*in==':'&&i>1){in++;n=strcspn(in,"\r\n");if(n>=cap)return 0;memcpy(tail,in,n);tail[n]=0;break;}
  n=strcspn(in," \r\n");if(n>=512)return 0;memcpy(fields[i++],in,n);in+=n;
 }
 return fields[1][0]!=0;
}
int fr_wire_feed(char *buf,size_t cap,size_t *len,int *discard,unsigned char byte)
{
 if(byte=='\r')return 0;
 if(byte=='\n'){
  if(*discard){*discard=0;*len=0;buf[0]=0;return 0;}
  buf[*len]=0;*len=0;return buf[0]!=0;
 }
 if(*discard)return 0;
 if(*len+1>=cap){*discard=1;*len=0;buf[0]=0;return 0;}
 buf[(*len)++]=byte;buf[*len]=0;return 0;
}

/* NickServ receives the original secret; reject protocol delimiters. */
int fr_identify_command(char *out,size_t cap,const char *password)
{
 const char prefix[]="PRIVMSG NickServ :identify ";size_t n=strlen(password),p=sizeof(prefix)-1;
 if(!n||n>64||strpbrk(password," \r\n")||p+n+1>cap)return 0;
 memcpy(out,prefix,p);memcpy(out+p,password,n+1);return 1;
}
