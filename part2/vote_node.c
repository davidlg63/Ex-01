//
// Created by David on 02/05/2020.
//

#include "vote_node.h"
#include "vote_data.h"
#include <stdlib.h>
#include <assert.h>


struct vote_node_t
{
    VoteData data;
    VoteNode next;
    VoteNode previous;
};


VoteNode voteNodeCreate(VoteNode current, int area_id, int tribe_id, int num_of_votes)
{
    VoteNode new_node = malloc(sizeof(*new_node));
    if(new_node == NULL)
    {
        return NULL;
    }
    if(current == NULL)
    {
        new_node->next = NULL;
        new_node->previous = NULL;
        new_node->data = voteDataCreate(area_id, tribe_id, num_of_votes);
        if(new_node->data == NULL)
        {
            free(new_node);
            new_node = NULL;
            return NULL;
        }
        return new_node;
    }
    new_node->data = voteDataCreate(area_id, tribe_id, num_of_votes);
    if(new_node->data == NULL)
    {
        new_node->next = NULL;
        new_node->previous = NULL;
        free(new_node);
        new_node = NULL;
        return NULL;
    }
    new_node->next = current->next;
    new_node->previous = current;
    current->next = new_node;
    return new_node;
}

void voteNodeRemove(VoteNode node)
{
    assert(node != NULL);
    VoteNode next = node->next;
    VoteNode previous = node->previous;
    if(previous != NULL)
    {
        node->previous->next = next;
    }
    if(next != NULL)
    {
        node->next->previous = previous;
    }

    voteDataRemove(node->data);
    node->data = NULL;
    node->previous = NULL;
    node->next = NULL;
    free(node);
    node = NULL;
}

VoteNode voteNodeGetNext(VoteNode node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->next;
}

int voteNodeGetAreaId(VoteNode node)
{
    if(node == NULL)
    {
        return GET_ID_ERROR;
    }
    return voteDataGetSource(node->data);
}

int voteNodeGetTribeId(VoteNode node)
{
    if(node == NULL)
    {
        return GET_ID_ERROR;
    }
    return voteDataGetDestination(node->data);
}

void  voteNodeAddVote(VoteNode node, int num_of_votes)
{
    assert(node != NULL);
    voteDataAddOrSubtract(node->data, num_of_votes);
}

int voteNodeGetVotes(VoteNode node)
{
    assert(node != NULL);
    return  voteDataGetNumOfVotes(node->data);
}