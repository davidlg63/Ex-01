//
// Created by David on 18/04/2020.
//

//Include:
#include "map.h"
#include "pair.h"
#include <stdlib.h>
#include <assert.h>
///////////////////////////////////////////

//Defines:
#define GET_SIZE_ERROR -1
/*............................*/

//Function declaration:
static Pair findPair(Map map, const char* key);
static void mapReset(Map map);
/*................................................*/


struct Map_t
{
    Pair current_pair;
    Pair first_pair;
    char* iterator;
    int num_of_elements;
};

Map mapCreate() {
    Map map = malloc(sizeof(*map));
    if(map == NULL)
    {
        return  NULL;
    }
    mapReset(map);
    map->num_of_elements = 0;
    return  map;
}

void mapDestroy(Map map) {
    if(mapClear(map) == MAP_NULL_ARGUMENT)
    {
        return;
    }

    free(map);
}

Map mapCopy(Map map) {
    Map copy_map = mapCreate();
    if(copy_map == NULL)
    {
        return  NULL;
    }
    Pair pair_counter = map->first_pair;
    while(pair_counter != NULL)
    {
        MapResult pair_copy_result = mapPut(copy_map, pairGetKey(pair_counter), pairGetData(pair_counter));
        if(pair_copy_result == MAP_NULL_ARGUMENT || pair_copy_result == MAP_OUT_OF_MEMORY)
        {
            mapDestroy(copy_map);
            return  NULL;
        }
        else
        {
            pair_counter = pairGetNext(pair_counter);
        }
    }
    return  copy_map;
}

int mapGetSize(Map map) {
    if(map == NULL)
    {
        return  GET_SIZE_ERROR;
    }
    return map->num_of_elements;
}

MapResult mapRemove(Map map, const char* key) {
    if(map == NULL || key == NULL)
    {
        return  MAP_NULL_ARGUMENT;
    }
    Pair pair_to_remove = findPair(map, key);
    if(pair_to_remove == NULL)
    {
        return MAP_ITEM_DOES_NOT_EXIST;
    }
    pairRemove(pair_to_remove);
    return MAP_SUCCESS;
}

bool mapContains(Map map, const char* key) {
    if(findPair(map, key) == NULL)
    {
        return false;
    }

    return true;
}

char* mapGet(Map map, const char* key) {
    if(key == NULL|| map == NULL)
    {
        return  NULL;
    }

    Pair temp = findPair(map, key);
    if(temp == NULL)
    {
        return  NULL;
    }
    else
    {
        return pairGetData(temp);
    }
}

MapResult mapPut(Map map, const char* key, const char* data) {

    if(map == NULL || key == NULL || data == NULL)
    {
        return  MAP_NULL_ARGUMENT;
    }

    Pair temp = findPair(map, key);
    if(temp != NULL)
    {
        pairSetData(temp, data);
        return MAP_SUCCESS;
    }

    else
    {
        temp = pairCreate(map, key, data);

        if(temp == NULL)
        {
            return  MAP_OUT_OF_MEMORY;
        }

        if(map->first_pair == NULL)// if temp is the first key-data pair added, then we assign first_pair to temp.
        {
            map->first_pair = temp;
            map->iterator = pairGetKey(temp);
        }
        map->current_pair = temp;
        map->num_of_elements++;
        return MAP_SUCCESS;
    }

}

char* mapGetFirst(Map map) {
    if(map == NULL || map->first_pair == NULL)
    {
        return  NULL;
    }
    map->iterator = pairGetKey(map->first_pair);
    return pairGetKey(map->first_pair);
}

char* mapGetNext(Map map) {
    assert(map->iterator == NULL);
    Pair current = findPair(map, map->iterator);
    Pair next = pairGetNext(current);
    if(next == NULL)
    {
        return  NULL;
    }

    return  pairGetKey(next);
}

MapResult mapClear(Map map) {

    if(map == NULL)
    {
        return  MAP_NULL_ARGUMENT;
    }

    Pair current = map->first_pair;
    while(map->num_of_elements > 0)
    {
        Pair temp = pairGetNext(current);
        pairRemove(current);
        current = temp;
        map->num_of_elements--;
    }
    mapReset(map);
    return MAP_SUCCESS;
}


static Pair findPair(Map map, const char* key) {
    Pair temp = map->first_pair;
    for (int i = 0; i < map->num_of_elements; ++i) {
        if (strcmp(key, pairGetKey(temp)) == 0) {
            return temp;
        }

        temp = pairGetNext(temp);
    }
    return NULL;
}

static void mapReset(Map map)
{
    map->first_pair = NULL;
    map->current_pair = NULL;
    map->iterator = NULL;
}