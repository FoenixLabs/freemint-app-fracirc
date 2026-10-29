#ifndef FR_IRC_WIRE_H
#define FR_IRC_WIRE_H
#include <stddef.h>
size_t fr_wire_format(char *,size_t,const char *);
int fr_wire_parse(const char *,char [10][512],char *,size_t);
/* Feed one byte: 1=complete line, 0=partial/discarded. */
int fr_wire_feed(char *,size_t,size_t *,int *,unsigned char);
int fr_identify_command(char *,size_t,const char *);
#endif
