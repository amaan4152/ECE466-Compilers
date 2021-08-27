#ifndef __LEX_DEF
#define __LEX_DEF

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include "tokens-manual.h"
#define U   1
#define L   2
#define UL  3
#define LL  4
#define ULL 5
#define D   6
#define DL  7
#define F   8
#define BUFSIZE 4096

struct _NUMBER
{
    unsigned long long _INT_; 
    long double _FLT_; 
    int _TYPE_;
};
struct _STRING
{
    char* _STR_; 
    char  _CHR_;
    char buf[BUFSIZE];
    char* pbuf; 
    size_t len; 
};    
typedef union{
    struct _NUMBER VAL;
    struct _STRING STR;
}YYSTYPE;

char filename[BUFSIZE];
int line_tick;
enum tokens TOKENS; 

#endif