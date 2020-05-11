//
// Created by David on 01/05/2020.
//
#include "key_value_pair.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

struct Key_Value_Pair
{
    char* key;
    char* data;
};

Pair pairCreate(const char* key, const char* data)
{
    assert(key != NULL && data != NULL);
    Pair pair;
    pair = malloc(sizeof(*pair));
    if(pair == NULL)
    {
        free(pair);
        pair = NULL;
        return NULL;
    }
    pair->key = malloc(strlen(key) + 1);
    if(pair->key == NULL)
    {
        free(pair->key);
        pair->key = NULL;
        pair->data = NULL;
        free(pair);
        pair = NULL;
        return  NULL;
    }
    pair->data = malloc(strlen(data) + 1);
    if(pair->data == NULL)
    {
        free(pair->key);
        pair->key = NULL;
        free(pair);
        pair = NULL;
        return NULL;
    }
    if(strcpy(pair->key, key) == NULL || strcpy(pair->data, data) == NULL)
    {
        free(pair->key);
        pair->key = NULL;
        free(pair->data);
        pair->data = NULL;
        free(pair);
        pair = NULL;
        return NULL;
    }

    return pair;
}

PairResult  pairDestroy(Pair pair)
{
    if(pair == NULL)
    {
        return PAIR_SUCCESS;
    }
    free(pair->data);
    pair->data = NULL;
    free(pair->key);
    pair->key = NULL;
    free(pair);
    pair = NULL;
    return PAIR_SUCCESS;
}

char* pairGetKey(Pair pair)
{
    assert(pair->key != NULL);
    return  pair->key;
}

char* pairGetData(Pair pair)
{
    assert(pair->data != NULL);
    return pair->data;
}

PairResult pairSetData(Pair pair, const char* new_data)
{
    assert(pair->data != NULL);
    char* temp = malloc(strlen(pair->data) + 1);
    if(temp == NULL)
    {
        return  PAIR_OUT_OF_MEMORY;
    }
    if(strcpy(temp, pair->data) == NULL)
    {
        free(temp);
        temp = NULL;
        return PAIR_OUT_OF_MEMORY;
    }
    free(pair->data);
    pair->data = malloc(strlen(new_data) + 1);
    if(pair->data == NULL)
    {
        pair->data = temp;
        return  PAIR_OUT_OF_MEMORY;
    }
    if(strcpy(pair->data, new_data) == NULL)
    {
        free(pair->data);
        pair->data = temp;
        return PAIR_OUT_OF_MEMORY;
    }
    free(temp);
    temp = NULL;
    return PAIR_SUCCESS;
}