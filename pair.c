//
// Created by David on 18/04/2020.
//
//Include:
#include "pair.h"
#include "map.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
/*..............................*/

struct pair_t {
    char* key;
    char* data;
    Pair next;
    Pair previous;
};

Pair pairCreate(Pair last_pair, const char* key, const char* data)
{
    assert(key != NULL && data != NULL);
    Pair pair = malloc(sizeof(*pair));
    if(pair == NULL)
    {
        free(pair);
        return  NULL;
    }
    pair->key = malloc(strlen(key) + 1);
    pair->data = malloc(strlen(data) + 1);
    if(pair->key == NULL || pair->data == NULL)
    {
        free(pair->data);
        free(pair->key);
        pair->data = NULL;
        pair->key = NULL;
        return  NULL;
    }

    if(strcpy(pair->key, key) == NULL)
    {
        free(pair->key);
        free(pair->data);
        pair->key = NULL;
        pair->data = NULL;
        free(pair);
        pair = NULL;
        return  NULL;
    }
    if(strcpy(pair->data, data) == NULL)
    {
        free(pair->key);
        free(pair->data);
        pair->key = NULL;
        pair->data = NULL;
        free(pair);
        pair = NULL;
        return  NULL;
    }
    pair->previous = last_pair;
    pair->next = NULL;
    if(last_pair != NULL)
    {
        last_pair->next = pair;
    }
    return  pair;
}

Pair pairGetNext(Pair current_pair) {
    if(current_pair == NULL)
    {
        return NULL;
    }
    return current_pair->next;
}

Pair pairGetPrevious(Pair current_pair){
    if(current_pair == NULL)
    {
        return NULL;
    }
    return current_pair->previous;
}

char* pairGetKey(Pair pair) {

    if(pair == NULL)
    {
        return NULL;
    }
    //printf("pair please print");

    //printf("pair.Key = %s ",pair->key);
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
    assert(current_pair != NULL);
    Pair next = current_pair->next;
    Pair previous = current_pair->previous;
    if(previous == NULL && next == NULL)
    {
        free(current_pair->key);
        current_pair->next = NULL;
        free(current_pair->data);
        current_pair->data = NULL;
        free(current_pair);
        current_pair = NULL;
        return;
    }
    else if(previous == NULL)
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
    current_pair->key = NULL;
    free(current_pair->data);
    current_pair->data = NULL;
    current_pair->next = NULL;
    current_pair->previous = NULL;
    free(current_pair);
    current_pair = NULL;
}

PairResult pairSetData(Pair pair, const char* data) {
    assert(pair != NULL || data != NULL);
    char* temp = malloc(strlen(pair->data) + 1);
    if(temp == NULL)
    {
        return  PAIR_OUT_OF_MEMORY;
    }
    strcpy(temp, pair->data);
    free(pair->data);
    pair->data = malloc(strlen(data) + 1);
    if(pair->data == NULL)
    {
        pair->data = temp;
        return  PAIR_OUT_OF_MEMORY;
    }
    strcpy(pair->data, data);
    free(temp);
    temp = NULL;
    return PAIR_SUCCESS;
}