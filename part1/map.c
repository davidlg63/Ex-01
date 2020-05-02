//
// Created by David on 18/04/2020.
//

//Include:
#include "map.h"
#include "node.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
///////////////////////////////////////////

//Defines:
#define GET_SIZE_ERROR -1
/*............................*/

//Function declaration:
static Node findNode(Map map, const char* key);
static void mapReset(Map map);
/*................................................*/


struct Map_t
{
    Node last_node;
    Node first_node;
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
    mapReset(map);
    free(map);
    map = NULL;
}

Map mapCopy(Map map) {
    if(map == NULL)
    {
        return  NULL;
    }
    Map copy_map = mapCreate();
    if(copy_map == NULL)
    {
        return  NULL;
    }
    Node node_counter = map->first_node;
    while(node_counter != NULL)
    {
        MapResult node_copy_result = mapPut(copy_map, nodeGetKey(node_counter), nodeGetData(node_counter));
        if(node_copy_result == MAP_NULL_ARGUMENT || node_copy_result == MAP_OUT_OF_MEMORY)
        {
            mapDestroy(copy_map);
            return  NULL;
        }
        else
        {
            node_counter = nodeGetNext(node_counter);
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
    Node node_to_remove = findNode(map, key);
    if(node_to_remove == NULL)
    {
        return MAP_ITEM_DOES_NOT_EXIST;
    }
    if(node_to_remove == map->first_node)
    {
        map->first_node = nodeGetNext(node_to_remove);
    }
    if(node_to_remove == map->last_node)
    {
        map->last_node = nodeGetPrevious(node_to_remove);
    }
    nodeRemove(node_to_remove);
    map->num_of_elements--;
    return MAP_SUCCESS;
}

bool mapContains(Map map, const char* key) {
    if(findNode(map, key) == NULL)
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

    Node temp = findNode(map, key);
    if(temp == NULL)
    {
        return  NULL;
    }
    else
    {
        assert(temp != NULL);

        return nodeGetData(temp);
    }
}

MapResult mapPut(Map map, const char* key, const char* data) {

    if(map == NULL || key == NULL || data == NULL)
    {
        return  MAP_NULL_ARGUMENT;
    }

    Node temp = findNode(map, key);

    if(temp != NULL)//temp already exists in map
    {
        if(nodeSetData(temp, data) == NODE_OUT_OF_MEMORY)
        {
            return MAP_OUT_OF_MEMORY;
        }

        else
        {
            return MAP_SUCCESS;
        }
    }

    else
    {
        temp = nodeCreate(map->last_node, key, data);

        if(temp == NULL)
        {
            return  MAP_OUT_OF_MEMORY;
        }

        if(map->first_node == NULL)// if temp is the first key-data node added, then we assign first_node to temp.
        {
            map->first_node = temp;
            map->iterator = nodeGetKey(temp);
        }
        map->last_node = temp;
        map->num_of_elements++;

        return MAP_SUCCESS;
    }

}

char* mapGetFirst(Map map) {
    if(map == NULL || map->first_node == NULL)
    {
        return  NULL;
    }
    map->iterator = nodeGetKey(map->first_node);
    return nodeGetKey(map->first_node);
}

char* mapGetNext(Map map) {
    assert(map->iterator != NULL);
    Node current = findNode(map, map->iterator);
    Node next = nodeGetNext(current);
    if(next == NULL)
    {
        return NULL;
    }
    map->iterator = nodeGetKey(next);
    return  nodeGetKey(next);
}

MapResult mapClear(Map map) {

    if(map == NULL)
    {
        return  MAP_NULL_ARGUMENT;
    }

    Node current = map->first_node;
    while(map->num_of_elements > 0)
    {
        Node temp = nodeGetNext(current);
        nodeRemove(current);
        current = temp;
        map->num_of_elements--;
    }
    mapReset(map);
    return MAP_SUCCESS;
}


static Node findNode(Map map, const char* key) {
    if(map == NULL || key == NULL)
    {
        return  NULL;
    }
    Node temp = map->first_node;
    for (int i = 0; i < map->num_of_elements; ++i) {
        assert(temp != NULL);

        if (strcmp(key, nodeGetKey(temp)) == 0) {
            return temp;
        }
        else
           // printf("Elad and David: %d\n", strcmp(key, nodeGetKey(temp)));
        temp = nodeGetNext(temp);
    }
    return NULL;
}

static void mapReset(Map map)
{
    map->first_node = NULL;
    map->last_node = NULL;
    map->iterator = NULL;
}