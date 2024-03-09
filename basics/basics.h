#ifndef  __BASICS_H__
#define  __BASICS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* CHALLENGES */

char* hex2base64(const char *);
char* fixed_xor(const char *, const char *);
char* xor_cypher(const char *);

/* COMMON UTILITIES */

uint8_t hex2nibble(char);
char nibble2hex(uint8_t);
uint8_t hex2byte(const char*);

#endif /* __BASICS_H__ */