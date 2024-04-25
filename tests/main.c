#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>



#include "../config.h"
#include "../config.c"
#include "util.h"




int
main()
{
    long _long = 5000;
    unsigned long _ulong = 103123;
    int _int = 10;
    unsigned int _uint = 321321;
    float _float = 12.0f;
    double _double = 3312032131.0;
    char _char = 123;
    unsigned char _uchar = 255;
    char *str = "Gamer word gamer";

    CFG *cfg = CFGCreate("/tmp/wannacry");
    
    /*   
    CFGCreateVar(cfg, "LONG", LONG);
    CFGCreateVar(cfg, "ULONG", ULONG);
    CFGCreateVar(cfg, "INT", INT);
    CFGCreateVar(cfg, "UINT", UINT);
    CFGCreateVar(cfg, "FLOAT", FLOAT);
    CFGCreateVar(cfg, "DOUBLE", DOUBLE);
    CFGCreateVar(cfg, "CHAR", CHAR);
    CFGCreateVar(cfg, "UCHAR", UCHAR);
    */
    CFGCreateVar(cfg, "STRING", STRING);

    /*
    CFGSaveVar(cfg, "LONG", &_long);
    CFGSaveVar(cfg, "ULONG", &_ulong);
    CFGSaveVar(cfg, "INT", &_int);
    CFGSaveVar(cfg, "UINT", &_uint);
    CFGSaveVar(cfg, "FLOAT", &_float);
    CFGSaveVar(cfg, "DOUBLE", &_double);
    CFGSaveVar(cfg, "CHAR", &_char);
    CFGSaveVar(cfg, "UCHAR", &_uchar);
    */
    CFGSaveVar(cfg, "STRING", str);

    //DEBUG("%d", _long);
    DEBUG("%d", *(long *)&_long);
    DEBUG("%s", str);
    DEBUG("%s", cfg->items->data);
    //CFGWrite(cfg);
}

