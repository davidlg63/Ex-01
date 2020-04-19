//
// Created by David on 18/04/2020.
//
//Include:
#include "pair.h"
#include "map.h"
#include <stdlib.h>
#include <assert.h>
/*..............................*/

struct pair_t {
    char* key;
    char* data;
    Pair next;
    Pair previous;
};

Pair pairCreate(Map map, Pair last_pair, const char* key, const char* data)
{
    assert(map == NULL || key == NULL || data == NULL);
    Pair pair = malloc(sizeof(*pair));
    if(pair == NULL)
    {
        return  NULL;
    }
    pair->key = malloc(sizeof(strlen(*key) + 1));
    pair->data = malloc(sizeof(strlen(*data) + 1));
    if(pair->key == NULL || pair->data == NULL)
    {
        free(pair->key);
        free(pair->data);
        free(pair);
        return  NULL;
    }
    strcpy(pair->key, key);
    strcpy(pair->data, data);
    pair->previous = last_pair;
    last_pair->next = pair;
    pair->next = NULL;
    return  pair;
}

Pair pairGetNext(Pair current_pair) {
    return current_pair->next;
}

Pair pairGetPrevious(Pair current_pair){
    return current_pair->previous;
}

char* pairGetKey(Pair pair) {
    if(pair == NULL)
    {
        return NULL;
    }
    return pair->key;
}

char* pairGetData(Pair pair) {
    if(pair == NULL)
    {
        return  NULL;
    }
    return pair->data;
}

void pairRemove(Pair current_pair) {
    assert(current_pair == NULL);
    Pair next = current_pair->next;
    Pair previous = current_pair->previous;
    if(previous == NULL)
    {
        next->previous = previous;
    }
    else if (next == NULL)
    {
        previous->next = next;
    }
    else
    {
        previous->next = current_pair->next;
        next->previous = current_pair->previous;
    }
    free(current_pair->key);
    free(current_pair->data);
    free(current_pair);
}

PairResult pairSetData(Pair pair, const char* data) {
    assert(pair == NULL);
    char* temp = malloc(sizeof(pair->data));
    if(temp == NULL)
    {
        return  PAIR_OUT_OF_MEMORY;
    }
    strcpy(temp, pair->data);
    free(pair->data);
    pair->data = malloc(sizeof(strlen(*data) + 1));
    if(pair->data == NULL)
    {
        pair->data = temp;
        return  PAIR_OUT_OF_MEMORY;
    }
    strcpy(pair->data, data);
    return PAIR_SUCCESS;
}
