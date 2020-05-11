//
// Created by David on 18/04/2020.
//

#ifndef NODE_H
#define NODE_H

#include "map.h"

typedef  struct  node_t* Node;

typedef enum node_result_t
{
    NODE_SUCCESS,
    NODE_OUT_OF_MEMORY,
}NodeResult;

Node nodeGetNext(Node current_node);

Node nodeGetPrevious(Node current_node);

char* nodeGetKey(Node node);

char* nodeGetData(Node node);

void nodeRemove(Node node);

Node nodeCreate(Node last_node, const char* key, const char* data);

NodeResult nodeSetData(Node node, const char* new_data);

#endif //NODE_H
