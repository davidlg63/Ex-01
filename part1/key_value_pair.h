//
// Created by David on 01/05/2020.
//

#ifndef KEY_VALUE_PAIR_H
#define KEY_VALUE_PAIR_H

typedef struct Key_Value_Pair* Pair;

typedef enum key_value_pair_result_t
{
    PAIR_SUCCESS,
    PAIR_OUT_OF_MEMORY,
}PairResult;

Pair pairCreate(const char* key, const char* data);

PairResult  pairDestroy(Pair pair);

char* pairGetKey(Pair pair);

char* pairGetData(Pair pair);

PairResult pairSetData(Pair pair, const char* new_data);

#endif /*KEY_VALUE_PAIR_H */
