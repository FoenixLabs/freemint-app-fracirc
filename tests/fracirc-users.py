#!/usr/bin/env python3
"""Exercise the actual channel roster with modern NAMES and membership changes."""
from pathlib import Path
import subprocess,tempfile
root=Path(__file__).resolve().parents[1]
src=root
code=r'''
#include "irc_users.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main(void){
 struct {char before[8];char users[FR_USER_LIMIT][FR_USER_SIZE];char after[8];} s={"before",{{0}},"after"};
 short count=0;int i;char n[100];
 fr_users_add(s.users,&count,"@OperatorWithThirtyCharacters12");
 fr_users_add(s.users,&count,"+Guest");
 fr_users_add(s.users,&count,"+Guest");assert(count==2);
 fr_users_change(s.users,&count,"operatorwiththirtycharacters12","Renamed");
 assert(!strcmp(s.users[0],"@Renamed"));
 fr_users_change(s.users,&count,"GUEST","");assert(count==1);
 fr_users_add(s.users,&count,"+Guest!user@host");assert(count==2);
 fr_users_add(s.users,&count,"+Guest!user@host");assert(count==2);
 fr_users_change(s.users,&count,"Renamed","");assert(count==1);
 for(i=0;i<FR_USER_LIMIT+5;i++){sprintf(n,"User%d",i);fr_users_add(s.users,&count,n);}
 assert(count==FR_USER_LIMIT);
 memset(n,'x',sizeof(n));n[99]=0;fr_users_add(s.users,&count,n);
 assert(!strcmp(s.before,"before")&&!strcmp(s.after,"after"));
 fr_users_change(s.users,&count,"User0","");assert(count==FR_USER_LIMIT-1);
 fr_users_add(s.users,&count,"Replacement");assert(count==FR_USER_LIMIT);
 return 0;
}
'''
with tempfile.TemporaryDirectory() as d:
 p=Path(d);(p/'test.c').write_text(code)
 subprocess.run(['cc','-Wall','-Wextra','-Werror','-I'+str(src),str(p/'test.c'),str(src/'irc_users.c'),'-o',str(p/'test')],check=True)
 subprocess.run([str(p/'test')],check=True)
print('PASS: user roster long names, prefixes, duplicates, rename/removal and capacity bounds')
