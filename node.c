//
// Created by David on 18/04/2020.
//
//Include:
#include "node.h"
#include "key_value_pair.h"
#include "map.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
/*..............................*/

struct node_t {
    //char* key;
    //char* data;
    Pair pair;
    Node next;
    Node previous;
};

Node nodeCreate(Node last_node, const char* key,  const char* data)
{
    assert(key != NULL && data != NULL);
    Node node = malloc(sizeof(*node));
    if(node == NULL)
    {
        free(node);
        return  NULL;
    }
    node->pair = pairCreate(key, data);
    if(node->pair == NULL)
    {
        free(node);
        node = NULL;
        return NULL;
    }
    node->previous = last_node;
    node->next = NULL;
    if(last_node != NULL)
    {
        last_node->next = node;
    }
    return  node;
}

Node nodeGetNext(Node current_node) {
    if(current_node == NULL)
    {
        return NULL;
    }
    return current_node->next;
}

Node nodeGetPrevious(Node current_node){
    if(current_node == NULL)
    {
        return NULL;
    }
    return current_node->previous;
}

char* nodeGetKey(Node node) {

    if(node == NULL)
    {
        return NULL;
    }

    return pairGetKey(node->pair);
}

char* nodeGetData(Node node) {
    if(node == NULL)
    {
        return  NULL;
    }
    return pairGetData(node->pair);
}

void nodeRemove(Node current_node) {
    assert(current_node != NULL);
    Node next = current_node->next;
    Node previous = current_node->previous;
    if(previous == NULL && next == NULL)
    {
        pairDestroy(current_node->pair);
        free(current_node);
        current_node = NULL;
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
        previous->next = current_node->next;
        next->previous = current_node->previous;
    }
    pairDestroy(current_node->pair);
    current_node->next = NULL;
    current_node->previous = NULL;
    free(current_node);
    current_node = NULL;
}

NodeResult nodeSetData(Node node, const char* data) {
    assert(node != NULL && data != NULL);
    if(pairSetData(node->pair, data) == PAIR_OUT_OF_MEMORY)
    {
        return NODE_OUT_OF_MEMORY;
    }

    return  NODE_SUCCESS;
}