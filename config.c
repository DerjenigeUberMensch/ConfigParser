
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"



static int /* FILE READ,   Buffer FILL data, Buffer Length */
__FILE_GET_NEW_LINE(FILE *fr, char *buff, unsigned int bufflength)
{
    char *nl;
    if(fgets(buff, bufflength, fr))
    {
        nl = strchr(buff, '\n');
        if(!nl)
        {
            if(!feof(fr))
            {   return ParseOverflow;
            }
        } /* remove new line char */
        else
        {   *nl = '\0';
        }
        return ParseSuccess;
    }
    else
    {
        if(ferror(fr))
        {
            return ParseError;
        }
        return ParseEOF;
    }
}


static void
__attach(CFG *cfg, CFGItem *item)
{
    item->next = cfg->items;
    cfg->items = item;
    if(item->next)
    {
        item->next->prev = item;
    }
    else
    {
        cfg->last = item;
    }
    item->prev = NULL;
}

static void
__detach(CFG *cfg, CFGItem *item)
{
    CFGItem **tc;
    for(tc = &cfg->items; *tc && *tc != item; tc = &(*tc)->next);
    *tc = item->next;
    if(!(*tc))
    {
        cfg->last = item->prev;
    }
    else if(item->next)
    {
        item->next->prev = item->prev;
    }
    else if(item->prev)
    {
        item->prev->next = NULL;
    }

    item->prev = NULL;
    item->next = NULL;
}



static char *
__REMOVE_WHITE_SPACE(char *str, int str_len)
{
    char *ret = NULL;
    int reti;
    int i;
    const int len = str_len;
    int size = len + sizeof(char);
    ret = malloc(size);
    if(!ret)
    {   return NULL;
    }
    reti = 0;
    for(i = 0; i < len; ++i)
    {   
        if(str[i] != ' ')
        {   
            ret[reti] = str[i];
            ++reti;
        }
    }
    if(reti < size)
    {   
        size = reti + sizeof(char);
        void *tmp = realloc(ret, size);
        if(!tmp)
        {   
            free(ret);
            return NULL;
        }
        ret = tmp;
    }
    ret[size - 1] = '\0';
    return ret;
}

/* Allocated mememory must be freed by caller.
 * Can return NULL
 */
static char *
__CFG_PARSE_NAME(char *buff)
{
    const char *delimeter = "=";
    char *token = NULL;
    char *ret = NULL;
    const int maxlen = 1024;
    int i;
    int reti;
    
    token = strtok(buff, delimeter);
    if(token)
    {   ret = __REMOVE_WHITE_SPACE(token, strnlen(token, maxlen));
    }
    return ret;
}

static char *
__CFG_PARSE_VALUE(char *buff)
{
    const char *delimeter = "=";
    char *token = NULL;
    char *ret = NULL;
    const int maxlen = 1024;
    
    token = strtok(buff, delimeter);
    token = strtok(NULL, delimeter);
    if(token)
    {   ret = __REMOVE_WHITE_SPACE(token, strnlen(token, maxlen));
    }
    return ret;
}


static CFGItem *
__CFG_GET_VAR_FROM_STRING(CFG *cfg, const char *VarName)
{
    CFGItem *item;
    for(item = cfg->items; item && strcmp(item->name, VarName); item = item->next);
    return item;
}

static size_t
__CFG_GET_TYPE_SIZE(int CFGType)
{
    switch(CFGType)
    {
        case INT:
            return sizeof(int);
        case UINT:
            return sizeof(unsigned int);
        case LONG:
            return sizeof(long int);
        case ULONG:
            return sizeof(unsigned long int);
        case FLOAT:
            return sizeof(float);
        case DOUBLE:
            return sizeof(double);
        case CHAR:
            return sizeof(char);
        case UCHAR:
            return sizeof(unsigned char);
    }
    return 0;
}



CFG *
CFGCreate(
        char *FILE_NAME
        )
{
    CFG *ret = malloc(sizeof(CFG));

    if(ret)
    {   
        ret->file = FILE_NAME;
        ret->items = NULL;
    }

    return ret;
}


CFGItem *
CFGCreateItem(
        void
        )
{
    CFGItem *item = malloc(sizeof(CFGItem));

    if(item)
    {
        item->data = NULL;
        item->_type = 0;
        item->name = NULL;
        item->next = NULL;
        item->prev = NULL;
        item->_veclen = 0;
    }

    return item;
}

int
CFGCreateVar(
        CFG *cfg, 
        char *VarName, 
        int CFGType)
{
    CFGItem *item = CFGCreateItem();

    if(item)
    {
        item->name = VarName;
        item->_type = CFGType;
        item->size = __CFG_GET_TYPE_SIZE(CFGType);
        if(cfg)
        {   __attach(cfg, item);
        }
        else
        {
            free(item);
            item = NULL;
        }
    }
    return !!item;
}

void *
CFGGetVarValue(
        CFG *cfg, 
        char *VarName
        )
{
    CFGItem *item;
    if((item = __CFG_GET_VAR_FROM_STRING(cfg, VarName)))
    {   return item->data;
    }
    return NULL;
}

int
CFGSaveVar(
        CFG *cfg, 
        char *VarName, 
        void *data
        )
{
    CFGItem *item;
    if((item = __CFG_GET_VAR_FROM_STRING(cfg, VarName)))
    {   memcpy(item->data, data, item->size);
    }
    return !!item;
}

int
CFGWrite(
        CFG *cfg
        )
{
    CFGItem *item;
    char *format;
    FILE *fw = fopen(cfg->file, "w");

    if(!fw)
    {   return ParseError;
    }
    uint8_t error = ParseSuccess;
    for(item = cfg->last; item; item = item->prev)
    {
        switch(item->_type)
        {
            case INT:
                format = "%d";
                fprintf(fw, format, *(int *)item->data);
                break;
            case UINT:
                format = "%u";
                fprintf(fw, format, *(unsigned int *)item->data);
                break;
            case LONG:
                format = "%ld";
                fprintf(fw, format, *(long int *)item->data);
                break;
            case ULONG:
                format = "%lu";
                fprintf(fw, format, *(unsigned long *)item->data);
                break;
            case FLOAT:
                format = "%f";
                fprintf(fw, format, *(float *)item->data);
                break;
            case DOUBLE:
                format = "%f";
                fprintf(fw, format, *(double *)item->data);
                break;
            case CHAR:
                format = "%c";
                fprintf(fw, format, ((char *)item->data)[0]);
                break;
            case UCHAR:
                format = "%d";
                fprintf(fw, format, *(unsigned char *)item->data);
            case STRING:
                format = "%s";
                fprintf(fw, format, (char *)item->data);
                break;
            default:
                error = ParsePartialError;
                break;
        }
        fprintf(fw, "\n");
    }
    return error;
}

int
CFGLoad(CFG *OldCfg)
{
    const int standardbufflimit = 1024 << 2;
    int running = 1;
    char buff[standardbufflimit];
    FILE *fr = fopen(OldCfg->file, "r");

    char *name = NULL;
    char *typename = NULL;
    int type = NOTYPE;
    void *data = NULL;
    if(!fr)
    {   return ParseError;
    }

    uint8_t error = ParseSuccess;
    
    while(running)
    {
        switch(__FILE_GET_NEW_LINE(fr, buff, standardbufflimit))
        {
            case ParseSuccess: 
                break;
            case ParseEOF:
                running = 0;
                /* FALLTHROUGH */
            case ParseOverflow: case ParseError: default:
                continue;
        }
        name = __CFG_PARSE_NAME(buff);
        typename = __CFG_PARSE_VALUE(buff);
        if(!name || !typename)
        {   
            free(name);
            free(typename);
            continue;
        }

        free(name);
        free(typename);
    }




    return error;
}
