#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// in an ADT
typedef struct page {

    char* key;
    char* data;
    struct page* next;

}*Page;

struct Map
{
     struct Page* first_value;
     struct Page* last;
     char* iterator;
     int num_of_elemants;
};



Map mapCreate()
{
   Map map= malloc(sizeof(*map));
   if (map==NULL)
    {
        return NULL;
    }
   map .first_value=NULL;
   map .last=NULL;
   map .iterator=NULL;
   map .num_of_elemants=0;
   return map;
}

void mapDestroy(Map map)
{
    if (mapClear(map)==MAP_NULL_ARGUMENT)
        {
            return;
        }
    free(map);
    return;
}

MapResult mapPut(Map map, const char* key, const char* data);
{
    Page page=malloc(sizeof(*page));
    if (page==NULL)
      {
        return MAP_OUT_OF_MEMORY
      }
    if (map .first_value==NULL)
      {
        map .first_value=page;
        map. last=page;
      }
    else
      {
        *last .next=page;
      }
    page.key=key;
    page.data=data;
    page.next=NULL
    map.num_of_elemants++;
    return MAP_SUCCRDD;

}

bool mapContains(Map map, const char* key);
{
    if (finding_value(map, key)==NULL)
    return false
    return true;
}

static Map finding_value(Map map, const char* key)
{
    Page tmp=map.first_valu;
    for (int i=0;i<map .num_of_elemants;i++)
    {
        if (strcmp(*tmp.key,key)==0)
        {
            return tmp;
        }
        tmp=*tmp.next;
    }
    return NULL;
}

char* mapGet(Map map, const char* key)
{
    if (mapContains(map,key)==false)
      {
        return NULL;
      }
    Page tmp= finding_value(map,key);
    char* the_data=tmp.data;
    return the_data;
}
