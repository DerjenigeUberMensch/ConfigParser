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

    CFG *cfg = CFGCreate("/tmp/wannacry");
    
    CFGCreateVar(cfg, "LONG", LONG);
    CFGCreateVar(cfg, "ULONG", ULONG);
    CFGCreateVar(cfg, "INT", INT);
    CFGCreateVar(cfg, "UINT", UINT);
    CFGCreateVar(cfg, "FLOAT", FLOAT);
    CFGCreateVar(cfg, "DOUBLE", DOUBLE);
    CFGCreateVar(cfg, "CHAR", CHAR);
    CFGCreateVar(cfg, "UCHAR", UCHAR);
    
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

    printf("Should be: ");
    printf("%ld", _long);
    printf(" %lu", _ulong);
    printf(" %d", _int);
    printf(" %u", _uint);
    printf(" %f", _float);
    printf(" %f", _double);
    printf(" %d", _char);
    printf(" %d", _uchar);
    printf("\n");

    CFGLoad(cfg);

    long int *LONG = CFGGetVarValue(cfg, "LONG");
    unsigned long int *ULONG = CFGGetVarValue(cfg, "ULONG");
    int *INT = CFGGetVarValue(cfg, "INT");
    unsigned int *UINT = CFGGetVarValue(cfg, "UINT");
    float *FLOAT = CFGGetVarValue(cfg, "FLOAT");
    double *DOUBLE = CFGGetVarValue(cfg, "DOUBLE");
    char *CHAR = CFGGetVarValue(cfg, "CHAR");
    unsigned char *UCHAR = CFGGetVarValue(cfg, "UCHAR");


    printf("%ld", *LONG);
    printf("\n");
    printf("%lu", *ULONG);
    printf("\n");
    printf("%d", *INT);
    printf("\n");
    printf("%u", *UINT);
    printf("\n");
    printf("%f", *FLOAT);
    printf("\n");
    printf("%f", *DOUBLE);
    printf("\n");
    printf("%d", *CHAR);
    printf("\n");
    printf("%d", *UCHAR);
    printf("\n");


    CFGDestroy(cfg);
}

