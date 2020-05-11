//
// Created by David on 02/05/2020.
//

#ifndef ELECTION_VOTE_NODE_H
#define ELECTION_VOTE_NODE_H

#define GET_ID_ERROR -1

typedef struct vote_node_t* VoteNode;

VoteNode voteNodeCreate(VoteNode current, int area_id, int tribe_id, int num_of_votes);

void voteNodeRemove(VoteNode node);

VoteNode voteNodeGetNext(VoteNode node);

int voteNodeGetAreaId(VoteNode node);

int voteNodeGetTribeId(VoteNode node);

void  voteNodeAddVote(VoteNode node, int num_of_votes);

int voteNodeGetVotes(VoteNode node);
#endif //ELECTION_VOTE_NODE_H
