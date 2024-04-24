#ifndef CONFIG_H
#define CONFIG_H



#include <stdint.h>
#include <stdlib.h>



typedef struct CFG CFG;
typedef struct CFGItem CFGItem;


struct CFG
{
    char *file;
    CFGItem *items;
    CFGItem *last;
};

struct CFGItem
{
    uint8_t _type;
    size_t size;
    uint32_t _veclen;
    void *data;
    char *name;

    CFGItem *next;
    CFGItem *prev;
};

enum ParseCode
{
    ParseSuccess,
    ParseError,
    ParsePartialError,
    ParseOverflow,
    ParseEOF,
};

enum CFGType
{
    NOTYPE,
    CHAR,
    UCHAR,
    INT,
    UINT,
    LONG,
    ULONG,
    FLOAT,
    DOUBLE,
    STRING,
    VECTOR,
    LASTTYPE,
};
















#endif







