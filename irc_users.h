#ifndef FR_IRC_USERS_H
#define FR_IRC_USERS_H
#define FR_USER_LIMIT 128
#define FR_USER_SIZE 64
void fr_users_add(char [FR_USER_LIMIT][FR_USER_SIZE],short *,const char *);
void fr_users_change(char [FR_USER_LIMIT][FR_USER_SIZE],short *,const char *,const char *);
#endif
