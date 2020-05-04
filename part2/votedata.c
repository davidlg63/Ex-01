// Include:
#include "votedata.h"
#include <stdlib.h>
#include <assert.h>
/*..............................*/


struct votedata_t {
    int source_id;
    int destanation_id;
    int num_of_votes;
};

VoteData voteDataCreate (int source, int destination) {
    VoteData votedata = malloc(sizeof(*votedata));
    if(votedata==NULL) {
        votedata=NULL;
        return NULL ;
    }
    votedata->source_id=source;
    votedata->destanation_id=destination;
    votedata->num_of_votes=0;
    return votedata;
}

void voteDataRemove(VoteData current_votedata){
    free(current_votedata);
    current_votedata=NULL;
}

int getSource (VoteData current_votedata) {
    assert(current_votedata != NULL);
    return current_votedata->source_id;
}

int getDestination (VoteData current_votedata) {
    assert(current_votedata != NULL);
    return current_votedata->destanation_id;
}

int getNumOfVotes (VoteData current_votedata) {
    assert(current_votedata != NULL);
    return current_votedata->num_of_votes;
}

VoteDataResult voteDataAddOrSubtract (VoteData current_votesdata, int change_num) {
    if (current_votesdata==NULL ){
        return VOTEDATA_NULL_ARRGUMENT;
    }
    if (current_votesdata->num_of_votes+change_num<0){//change_num can be a negative number
        current_votesdata->num_of_votes=0;
        return VOTEDATA_SUCCESS;
    }
    current_votesdata->num_of_votes += change_num;
    return VOTEDATA_SUCCESS;
}

/*VoteDataResult  voteDataSubtruct(VoteData current_votesdata, int num_to_remove) {
    if (current_votesdata==NULL ||num_to_remove<0 ){
        return VOTEDATA_NULL_ARRGUMENT;
    }
   // ( current_votesdata->num_of_votes - num_to_remove <= 0) ? current_votesdata->num_of_votes=0 : current_votesdata->num_of_votes-=num_to_remove;
   if (current_votesdata->num_of_votes<num_to_remove){
        current_votesdata->num_of_votes=0;
        return VOTEDATA_SUCCESS;
    }
    current_votesdata->num_of_votes-=num_to_remove;
    return VOTEDATA_SUCCESS;
}/*