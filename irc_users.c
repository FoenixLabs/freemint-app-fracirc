#include "irc_users.h"
#include <string.h>
#include <ctype.h>
static const char *plain(const char *s)
{
 while(*s&&strchr("~&@%+",*s))s++;
 return s;
}
static int same(const char *a,const char *b)
{
 a=plain(a);b=plain(b);
 while(*a&&*b){if(tolower((unsigned char)*a++)!=tolower((unsigned char)*b++))return 0;}
 return *a==*b;
}
void fr_users_add(char users[FR_USER_LIMIT][FR_USER_SIZE],short *count,const char *name)
{
 int i,slot=-1;char token[FR_USER_SIZE];size_t n=strcspn(name," !\r\n");
 if(!n||n>=FR_USER_SIZE)return;
 memcpy(token,name,n);token[n]=0;name=token;
 for(i=0;i<FR_USER_LIMIT;i++){
  if(!users[i][0]){if(slot<0)slot=i;}
  else if(same(users[i],name)){slot=i;break;}
 }
 if(slot<0)return;
 if(!users[slot][0])(*count)++;
 memcpy(users[slot],name,n);users[slot][n]=0;
}
void fr_users_change(char users[FR_USER_LIMIT][FR_USER_SIZE],short *count,const char *old,const char *name)
{
 int i;size_t prefix,n;
 for(i=0;i<FR_USER_LIMIT;i++)if(users[i][0]&&same(users[i],old)){
  if(!*name){users[i][0]=0;if(*count>0)(*count)--;}
  else{
   prefix=plain(users[i])-users[i];n=strlen(name);
   if(prefix+n>=FR_USER_SIZE)continue;
   memmove(users[i]+prefix,name,n+1);
  }
 }
}
