//
// Created by David on 02/05/2020.
//

#ifndef ELECTION_VOTE_LIST_H
#define ELECTION_VOTE_LIST_H

#include "vote_node.h"

typedef struct vote_list_t* VoteList;

typedef enum VoteListResult_t
{
    VOTE_LIST_SUCCESS,
    VOTE_LIST_OUT_OF_MEMORY,
    VOTE_LIST_NULL_ARGUMENT
}VoteListResult;

typedef enum VoteListRemoveCandidate_t
{
    TRIBE,
    AREA
}VoteListRemoveCandidate;

VoteList voteListCreate();

void voteListDestroy(VoteList list);

VoteListResult voteListAdd(VoteList list, int area_id, int tribe_id, int num_of_votes);

void voteListRemove(VoteList list, int id, VoteListRemoveCandidate remove_candidate);

VoteNode voteListContainArea(VoteList list, int area_id);

int voteListFindMaxTribe(VoteNode area, int tribe_id_minimal);
#endif //ELECTION_VOTE_LIST_H
