

# ifndef VOTEDATA_H
#define VOTEDATA_H



/**
 *
 * Implements a VotesData container type.
 * The type of the source_id, destination_id and num_votes is int.
 *
 *  The following functions are available:
 *
 *      voteDataCreate      - create a new VotesData type and returns a pointer to the struct.
 *      voteDataRemove      - removes the VotesData that matches the given pointer and freeing it's memory.
 *      getSource            - return the ID value of the votes' source  (the ID of the area).
 *      getDestination       - returns the ID of the tribes which the votes belong to.
 *      getNumOfVotes             - returns the number of votes from this specific area to the specific tribe.
 *      voteDataAddOrSubtract      - adding a number of votes (set by the user) to a certain tribe from
 *                                  a certain area. If the number given is negative, the function will subtract it
 *                                  from the current value, and if the result will be negative, it will be changed to 0
 *
 *      */

/** Type for defining the data of the vots */
typedef struct votedata_t* VoteData;

/**
 * a set of return messages from VotesData function.
 */
typedef enum votedata_result_t {
    VOTEDATA_SUCCESS,
   VOTEDATA_NULL_ARRGUMENT,
} VoteDataResult;

/**
 * voteDataCreate      - create a new VotesData type and returns a pointer to the struct
 *                        allocates the memory required for a VotesData struct and will reset their values to
 *                        the information its given.
 *
 * @param source: The Id of the are from which the votes are connected to.
 * @param destination: The Id of the tribe that the votes belong to.
 * @return
 * Pointer to the struct created by the function, if the allocation was a success.
 * NULL if the allocation failed.
 */
VoteData  voteDataCreate (int source, int destination);

/**
 *  voteDataCreate      Frees all the memory that was allocated in the  VotesData that  was associated with
 *                       pointer the function receives from the user.
 *
 * @param current_votedata - Pointer to the start of the struct to free.
 */
void voteDataRemove (VoteData current_votedata);

/**
 *  getSource            - return the ID of the area that associated with the pointer given by the user.
 *
 * @param current_votedata- Pointer to the struct that the from which the ID will come.
 * @return
 * ID of the area from which the votes connected to the struct are coming from.
 */
int getSource(VoteData cuurent_votedata);

/**
 * gerDestination        - a function that return to the user the ID of the tribe that the votes
 *                          in the struct belong to.
 * @param current_votedata Pointer to the struct that its data is requested.
 * @return
 * The ID of the tribe that the votes in the struct belong to.
 */
int getDestination(VoteData current_votedata);

/**
 * getNumOfVotes            - a function that returns the number of votes from a certain area to a certain tribe.
 * @param current_votedata : Pointer to the struct that its data will be received.
 * @return
 * The number of votees from the area to the tribe.
 */
int getNumOfVotes(VoteData current_votedata);

/**
 * voteDataAdd         - This function will receive a number of votes that will be added or
 *                      subtracted to the number already exist  from the are to the tribe. If the result of the
 *                      subtract action will be a negative number, the value will be changed to 0.
 *
 * @param current_votedata ; Pointer to the strcut that the number of votes will be added to.
 * @param num_to_add: The number of votes to add to the current votes.
 * @return
 * VOTESDATA_SUCCESS in case of a successful action.
 * VOTESDATA_NULL_ARRGUMENT in case of a null number sent to the function.
 */
//VoteDataResult  voteDataAddOrSubtract(VoteData current_votesdata, int num_to_add);





#endif /* VOTESDATA_H */
