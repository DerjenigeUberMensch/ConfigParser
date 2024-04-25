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






CFG *
CFGCreate(
        char *FILE_NAME
        );

CFGItem *
CFGCreateItem(
        void
        );

int
CFGCreateVar(
        CFG *cfg, 
        char *VarName, 
        int CFGType
        );

void *
CFGGetVarValue(
        CFG *cfg, 
        char *VarName
        );

/* Saves data specified by the variable name If it exists. 
 * One must pass in the address of the data wanting to be used, this includes strings interpreted as char *.
 *
 * EX: int x = 10; 
 *     CFGSaveVar(MyCfg, "MyVar", &x);
 * EX: char *str = "my cool string";
 *     char str2[] = "my cool string";
 *     CFGSaveVar(MyCfg, "MyVarString", str);
 *     CFGSaveVar(MyCfg, "MyVarStringArray", str2);
 * 
 *
 * RETURN: 0 On Success.
 * RETURN: 1 On Failure.
 */
int
CFGSaveVar(
        CFG *cfg, 
        char *VarName, 
        void *data
        );

int
CFGWrite(
        CFG *cfg
        );

int
CFGLoad(
        CFG *OldCfg
        );











#endif







