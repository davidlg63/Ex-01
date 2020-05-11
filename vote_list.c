//
// Created by David on 02/05/2020.
//

#include "vote_list.h"
#include "vote_node.h"
#include <stdlib.h>
#include <assert.h>

static void voteListAddVotesToArea(VoteList list, int area_id, int tribe_id, int num_of_votes);
static VoteNode voteListAreaContainsTribe(VoteNode area, int area_id, int tribe_id);

struct vote_list_t
{
    VoteNode head;
};

VoteList voteListCreate()
{
    VoteList vote_list = malloc(sizeof(*vote_list));
    if(vote_list == NULL)
    {
        return NULL;
    }
    vote_list->head = NULL;
    return vote_list;
}

void voteListDestroy(VoteList list)
{
    if(list == NULL)
    {
        return;
    }
    VoteNode current_node = list->head;
    VoteNode temp;
    while(current_node != NULL)
    {
        temp = voteNodeGetNext(current_node);
        voteNodeRemove(current_node);
        current_node = temp;
    }
    list->head = NULL;
    free(list);
    list = NULL;
}

VoteListResult voteListAdd(VoteList list, int area_id, int tribe_id, int num_of_votes) {
    if (list == NULL)
    {
        return VOTE_LIST_NULL_ARGUMENT;
    }

    VoteNode area_node = voteListContainArea(list, area_id);
    if(area_node != NULL)
    {
        voteListAddVotesToArea(list, area_id, tribe_id, num_of_votes);
    }

    else
    {
        VoteNode current = list->head;
        VoteNode next = voteNodeGetNext(current);
        while (next != NULL)
        {
            current = next;
            next = voteNodeGetNext(current);
        }

        if(current == NULL)//This case means that the list is empty right now.
        {
            list->head = voteNodeCreate(current, area_id, tribe_id, num_of_votes);
            if(list->head == NULL)
            {
                return VOTE_LIST_OUT_OF_MEMORY;
            }
        }

        else if (voteNodeCreate(current, area_id, tribe_id, num_of_votes) == NULL)
        {
            return VOTE_LIST_OUT_OF_MEMORY;
        }
    }

    return VOTE_LIST_SUCCESS;
}

void voteListRemove(VoteList list, int id, VoteListRemoveCandidate remove_candidate)
{
    assert(list != NULL);
    VoteNode current = list->head;
    VoteNode next = voteNodeGetNext(current);
    while(next != NULL)
    {
        if(remove_candidate == REMOVE_TRIBE)
        {
            if (voteNodeGetTribeId(current) == id)
            {
                list->head = (current == list->head) ? next : list->head;
                voteNodeRemove(current);
            }
        }

        else if(remove_candidate == REMOVE_AREA)
        {
            if (voteNodeGetAreaId(current) == id)
            {
                list->head = (current == list->head) ? next : list->head;
                voteNodeRemove(current);
            }
        }
        current = next;
        next = voteNodeGetNext(current);
    }
}

VoteNode voteListContainArea(VoteList list, int area_id)
{
    VoteNode current = list->head;
    VoteNode next = voteNodeGetNext(current);
    while (next != NULL)
    {
        if(voteNodeGetAreaId(current) == area_id)
        {
            return current;
        }
        current = next;
        next = voteNodeGetNext(current);
    }

    return NULL;
}

int voteListFindMaxTribe(VoteNode node, int tribe_id_minimal)
{
    assert(node != NULL);
    int max_tribe_votes = 0, min_tribe_id = 0, current_tribe_votes = 0, current_tribe_id = 0;
    VoteNode current_node = node;
    while(voteNodeGetAreaId(current_node) == voteNodeGetAreaId(node))
    {
        current_tribe_votes = voteNodeGetVotes(current_node);
        if(current_tribe_votes >= max_tribe_votes)
        {
            current_tribe_id = voteNodeGetTribeId(current_node);
            if(current_tribe_votes == max_tribe_votes && current_tribe_id < min_tribe_id)
            {
                min_tribe_id = current_tribe_id;
            }
            else if(current_tribe_votes > max_tribe_votes)
            {
                max_tribe_votes = current_tribe_votes;
                min_tribe_id = current_tribe_id;
            }
        }
        current_node = voteNodeGetNext(current_node);
    }

    min_tribe_id = (max_tribe_votes == 0) ? tribe_id_minimal : min_tribe_id;
    return min_tribe_id;
}

static void voteListAddVotesToArea(VoteList list, int area_id, int tribe_id, int num_of_votes)
{
    assert(list != NULL);
    VoteNode current = list->head;
    VoteNode  next = voteNodeGetNext(current);
    while(voteNodeGetAreaId(current) != area_id)
    {
        current = next;
        next = voteNodeGetNext(current);
    }

    VoteNode current_tribe = voteListAreaContainsTribe(current, area_id, tribe_id);
    if(current_tribe != NULL)
    {
        voteNodeAddVote(current_tribe, num_of_votes);
    }
    else
    {
        /*while(voteNodeGetAreaId(next) == area_id)
        {
            current = next;
            next = voteNodeGetNext(current);
        }*/
        voteNodeCreate(current, area_id, tribe_id, num_of_votes);
    }

}

static VoteNode voteListAreaContainsTribe(VoteNode area, int area_id, int tribe_id)
{
    assert(area != NULL);
    VoteNode current = area;
    while(voteNodeGetAreaId(current) == area_id)
    {
        if(voteNodeGetTribeId(current) == tribe_id)
        {
            return current;
        }
        current = voteNodeGetNext(current);
    }

    return NULL;
}