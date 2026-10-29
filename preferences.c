/* GCC port preferences: bounded text format; no legacy malformed binary parser. */
#include "compat.h"
#include "header.h"
struct text_setting {const char *key;char *value;size_t size;};
#define FIELD(k,v) {k,v,sizeof(v)}
static struct text_setting texts[]={
 FIELD("nick",conf.snick),FIELD("nickserv_password",conf.nickserv_password),FIELD("alternate_nick",conf.snick2),
 FIELD("server0",irc_server[0]),FIELD("port0",irc_port[0]),
 FIELD("server1",irc_server[1]),FIELD("port1",irc_port[1]),
 FIELD("server2",irc_server[2]),FIELD("port2",irc_port[2]),
 FIELD("server3",irc_server[3]),FIELD("port3",irc_port[3]),
 FIELD("username",username),FIELD("realname",realname),
 FIELD("hostname",hostname),FIELD("dcc_path",path.dcc),
 FIELD("sound_path",path.sound),FIELD("url_path",path.url),FIELD("log_path",path.log),
 FIELD("autojoin1",conf.amaj1),FIELD("autojoin2",conf.amaj2)
};
void loadprefs(char *name)
{
 char line[1024],*value;unsigned i;FILE *f=fopen(name?name:"FRACIRC.INF","r");
 if(!f){if(name)form_alert(1,"[1][Cannot open preferences.][OK]");return;}
 while(fgets(line,sizeof(line),f)){
  value=strchr(line,'=');if(!value)continue;*value++=0;value[strcspn(value,"\r\n")]=0;
  for(i=0;i<sizeof(texts)/sizeof(texts[0]);i++)if(!strcmp(line,texts[i].key))stccpy(texts[i].value,value,texts[i].size);
 }
 fclose(f);
}
short savprefs(char *name)
{
 char tmp[1024];FILE *f;unsigned i;const char *target=name?name:"FRACIRC.INF";
 if(strlen(target)+5>=sizeof(tmp))return -1;
 snprintf(tmp,sizeof(tmp),"%s.new",target);f=fopen(tmp,"w");if(!f)return -1;
 fputs("# FracIRC GCC port preferences v1\n",f);
 for(i=0;i<sizeof(texts)/sizeof(texts[0]);i++)fprintf(f,"%s=%s\n",texts[i].key,texts[i].value);
 if(fclose(f)||rename(tmp,target)){remove(tmp);form_alert(1,"[1][Cannot save preferences.][OK]");return -1;}
 return 0;
}
