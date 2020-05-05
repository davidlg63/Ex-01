// Include:
#include "vote_data.h"
#include <stdlib.h>
#include <assert.h>
/*..............................*/


struct votedata_t {
    int source_id;
    int destination_id;
    int num_of_votes;
};

VoteData voteDataCreate (int source, int destination, int num_of_votes) {
    VoteData votedata = malloc(sizeof(*votedata));
    if(votedata==NULL) {
        votedata=NULL;
        return NULL ;
    }
    votedata->source_id=source;
    votedata->destination_id=destination;
    votedata->num_of_votes = num_of_votes;
    return votedata;
}

void voteDataRemove(VoteData current_votedata){
    free(current_votedata);
    current_votedata=NULL;
}

int voteDataGetSource (VoteData current_votedata) {
    assert(current_votedata != NULL);
    return current_votedata->source_id;
}

int voteDataGetDestination (VoteData current_votedata) {
    assert(current_votedata != NULL);
    return current_votedata->destination_id;
}

int voteDataGetNumOfVotes (VoteData current_votedata) {
    assert(current_votedata != NULL);
    return current_votedata->num_of_votes;
}

VoteDataResult voteDataAddOrSubtract (VoteData current_votesdata, int change_num) {
    if (current_votesdata==NULL ){
        return VOTEDATA_NULL_ARRGUMENT;
    }
    current_votesdata->num_of_votes += change_num;
    if (current_votesdata->num_of_votes < 0) //change_num can be a negative number
    {
        current_votesdata->num_of_votes=0;
        return VOTEDATA_SUCCESS;
    }

    return VOTEDATA_SUCCESS;
}
