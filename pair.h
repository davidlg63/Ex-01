//
// Created by David on 18/04/2020.
//

#ifndef PAIR_H
#define PAIR_H

#include "map.h"

typedef  struct  pair_t* Pair;

typedef enum pair_result_t
{
    PAIR_SUCCESS,
    PAIR_OUT_OF_MEMORY,
}PairResult;

Pair pairGetNext(Pair current_pair);

Pair pairGetPrevious(Pair current_pair);

char* pairGetKey(Pair pair);

char* pairGetData(Pair pair);

void pairRemove(Pair pair);

Pair pairCreate(Pair last_pair, const char* key, const char* data);

PairResult pairSetData(Pair pair, const char* new_data);

#endif //PAIR_H
