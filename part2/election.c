//
// Created by David on 02/05/2020.
//

#include "election.h"
#include "map.h" //"mtm_map/map.h
#include "vote_list.h"
#include <stdlib.h>
#include <stdbool.h>

//static functions:
//*****************************

enum ManageStatus {VOTE_MANAGE_ADD, VOTE_MANAGE_REMOVE};

static bool isValidId(int id);
static bool isValidName(const char* name);
static ElectionResult CheckStandardInputParameters(Election election, int id, const char* name);
static ElectionResult electionVoteManage(Election election, int area_id, int tribe_id, int num_of_votes,
         enum ManageStatus status);
static int intLength(int);

//*****************************

#define LOWER_CASE_A ('a')
#define LOWER_CASE_Z ('z')
#define SPACE_ASCII (' ')
#define DECIMAL_BASE 10

struct election_t
{
    Map tribes;
    Map areas;
    VoteList vote_list;
};



Election electionCreate()
{
    Election election = malloc(sizeof(*election));
    if(election == NULL)
    {
        free(election);
        election = NULL;
        return NULL;
    }
    election->tribes = mapCreate();
    election->areas = mapCreate();
    election->vote_list = voteListCreate();
    if(election->tribes == NULL || election->areas == NULL || election->vote_list == NULL)
    {
        free(election->tribes);
        election->tribes = NULL;
        free(election->areas);
        election->areas = NULL;
        free(election->vote_list);
        election->vote_list = NULL;
        return NULL;
    }
    return election;
}


void electionDestroy(Election election)
{
    mapDestroy(election->tribes);
    mapDestroy(election->areas);
    voteListDestroy(election->vote_list);
    free(election);
    election = NULL;
}

ElectionResult electionAddTribe (Election election, int tribe_id, const char* tribe_name)
{
    char* string_holder = NULL;
    ElectionResult is_input_parameters_valid = CheckStandardInputParameters(election, tribe_id, tribe_name);
    if(is_input_parameters_valid != ELECTION_SUCCESS)
    {
        return is_input_parameters_valid;
    }

    string_holder = malloc(intLength(tribe_id) + 1);
    if(string_holder == NULL)
    {
        return ELECTION_OUT_OF_MEMORY;
    }
    string_holder = itoa(tribe_id, string_holder, DECIMAL_BASE);
    if(mapContains(election->tribes, string_holder) == true)
    {
        free(string_holder);
        string_holder = NULL;
        return ELECTION_TRIBE_ALREADY_EXIST;
    }

    if(mapPut(election->tribes, string_holder, tribe_name) == MAP_OUT_OF_MEMORY)
    {
        free(string_holder);
        string_holder = NULL;
        return ELECTION_OUT_OF_MEMORY;
    }

    free(string_holder);
    string_holder = NULL;
    return ELECTION_SUCCESS;
}

ElectionResult electionAddArea(Election election, int area_id, const char* area_name)
{
    ElectionResult is_input_parameters_valid = CheckStandardInputParameters(election, area_id, area_name);
    if(is_input_parameters_valid != ELECTION_SUCCESS)
    {
        return is_input_parameters_valid;
    }

    char* string_holder = malloc(intLength(area_id) + 1);
    if(string_holder == NULL)
    {
        return ELECTION_OUT_OF_MEMORY;
    }
    string_holder = itoa(area_id, string_holder, DECIMAL_BASE);

    if(mapContains(election->areas, string_holder) == true)
    {
        free(string_holder);
        string_holder = NULL;
        return ELECTION_AREA_ALREADY_EXIST;
    }

    if(mapPut(election->areas, string_holder, area_name) == MAP_OUT_OF_MEMORY)
    {
        free(string_holder);
        string_holder = NULL;
        return ELECTION_OUT_OF_MEMORY;
    }

    free(string_holder);
    string_holder = NULL;
    return ELECTION_SUCCESS;
}

char* electionGetTribeName (Election election, int tribe_id)
{
    char* string_holder = NULL;
    string_holder = malloc(intLength(tribe_id) + 1);
    if(string_holder == NULL)
    {
        return ELECTION_OUT_OF_MEMORY;
    }
    string_holder = itoa(tribe_id, string_holder, DECIMAL_BASE);
    if(election == NULL || mapContains(election->tribes, string_holder) == false)
    {
        free(string_holder);
        string_holder = NULL;
        return NULL;
    }

    char* tribe_name = mapGet(election->tribes, string_holder);
    char* tribe_name_copy = malloc(strlen(tribe_name) + 1);
    if(tribe_name_copy == NULL)
    {
        free(string_holder);
        string_holder = NULL;
        return NULL;
    }
    strcpy(tribe_name_copy, tribe_name);
    free(string_holder);
    string_holder = NULL;
    return tribe_name;
}

ElectionResult electionSetTribeName (Election election, int tribe_id, const char* tribe_name)
{
    //char* string_holder = NULL;
    char* string_holder = malloc(intLength(tribe_id) + 1);
    if(string_holder == NULL)
    {
        return ELECTION_OUT_OF_MEMORY;
    }
    ElectionResult is_input_parameters_valid = CheckStandardInputParameters(election, tribe_id, tribe_name);
    if(is_input_parameters_valid != ELECTION_SUCCESS)
    {
        free(string_holder);
        string_holder = NULL;
        return  is_input_parameters_valid;
    }
    string_holder = itoa(tribe_id, string_holder, DECIMAL_BASE);
    if(mapContains(election->tribes, string_holder) == false)
    {
        free(string_holder);
        string_holder = NULL;
        return ELECTION_TRIBE_NOT_EXIST;
    }

    if(mapPut(election->tribes, string_holder, tribe_name) == MAP_OUT_OF_MEMORY)
    {
        free(string_holder);
        string_holder = NULL;
        return ELECTION_OUT_OF_MEMORY;
    }

    return ELECTION_SUCCESS;
}

ElectionResult electionAddVote (Election election, int area_id, int tribe_id, int num_of_votes)
{
    return electionVoteManage(election, area_id, tribe_id, num_of_votes, VOTE_MANAGE_ADD);
}

ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    return electionVoteManage(election, area_id, tribe_id, num_of_votes, VOTE_MANAGE_REMOVE);
}

ElectionResult electionRemoveTribe (Election election, int tribe_id)
{
    char* string_holder = NULL;

    if(election == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }

    if(isValidId(tribe_id) == false)
    {
        return ELECTION_INVALID_ID;
    }

    string_holder = malloc(intLength(tribe_id) + 1);
    if(string_holder == NULL)
    {
        return ELECTION_OUT_OF_MEMORY;
    }
    string_holder = itoa(tribe_id, string_holder, DECIMAL_BASE);

    if(mapRemove(election->tribes, string_holder) == MAP_ITEM_DOES_NOT_EXIST)
    {
        free(string_holder);
        string_holder = NULL;
        return ELECTION_TRIBE_NOT_EXIST;
    }

    voteListRemove(election->vote_list, tribe_id, TRIBE);
    free(string_holder);
    string_holder = NULL;
    return ELECTION_SUCCESS;
}

ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area)
{
    if(election == NULL || should_delete_area == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }

    char* key = mapGetFirst(election->areas);
    while(key != NULL)
    {
        if(should_delete_area(atoi(key)))
        {
            voteListRemove(election->vote_list, atoi(mapGet(election->areas, key)), AREA);
            mapRemove(election->areas, key);
        }
        key = mapGetNext(election->areas);
    }

    return ELECTION_SUCCESS;
}

Map electionComputeAreasToTribesMapping (Election election)
{
    if(election == NULL)
    {
        return NULL;
    }
    int max_tribe_id, area_id;
    char* key = mapGetFirst(election->areas);
    char* string_holder_area = NULL;
    char* string_holder_tribe = NULL;
    VoteNode area = NULL;
    Map areas_to_tribes = mapCreate();
    if(areas_to_tribes == NULL)
    {
        return NULL;
    }
    while(key != NULL)
    {
        area = voteListContainArea(election->vote_list, atoi(key));
        if (area != NULL)
        {
            max_tribe_id = voteListFindMaxTribe(area);
            area_id = voteNodeGetAreaId(area);
            string_holder_tribe = malloc(intLength(max_tribe_id) + 1);
            string_holder_area = malloc(intLength(area_id) + 1);
            string_holder_tribe = itoa(max_tribe_id, string_holder_tribe, DECIMAL_BASE);
            string_holder_area = itoa(area_id, string_holder_area, DECIMAL_BASE);
            if(string_holder_area == NULL || string_holder_tribe == NULL)
            {
                free(string_holder_area);
                free(string_holder_tribe);
                string_holder_area = NULL;
                string_holder_tribe = NULL;
                return NULL;
            }
            if (mapPut(areas_to_tribes, string_holder_area, string_holder_tribe) == MAP_OUT_OF_MEMORY)
            {
                mapDestroy(areas_to_tribes);
                areas_to_tribes = NULL;
                free(string_holder_area);
                string_holder_area = NULL;
                free(string_holder_tribe);
                string_holder_tribe = NULL;
                return ELECTION_OUT_OF_MEMORY;
            }
        }
        key = mapGetNext(election->areas);
    }

    free(string_holder_area);
    string_holder_area = NULL;
    free(string_holder_tribe);
    string_holder_tribe = NULL;
    return areas_to_tribes;
}

static bool isValidId(int id)
{
    if(id < 0)
    {
        return false;
    }

    return true;
}

static bool isValidName(const char* name)
{
    while(*name)
    {
        if((*name < LOWER_CASE_A || *name > LOWER_CASE_Z) && *name != SPACE_ASCII)
        {
            return false;
        }
        name++;
    }

    return true;
}

static ElectionResult CheckStandardInputParameters(Election election, int id, const char* name)
{
    if(election == NULL || name == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }

    if(isValidId(id) == false)
    {
        return ELECTION_INVALID_ID;
    }

    if(isValidName(name) == false)
    {
        return ELECTION_INVALID_NAME;
    }

    return ELECTION_SUCCESS;
}

static ElectionResult electionVoteManage(Election election, int area_id, int tribe_id, int num_of_votes,
        enum ManageStatus status)
{
    char* string_holder = NULL;
    if(election == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }

    if(isValidId(area_id) == false || isValidId(tribe_id) == false)
    {
        return ELECTION_INVALID_ID;
    }

    if(num_of_votes < 0)
    {
        return ELECTION_INVALID_VOTES;
    }

    string_holder = malloc(intLength(tribe_id) + 1);
    if(string_holder == NULL)
    {
        return ELECTION_OUT_OF_MEMORY;
    }
    string_holder = itoa(tribe_id, string_holder, DECIMAL_BASE);
    if(mapContains(election->tribes, string_holder) == false)
    {
        free(string_holder);
        string_holder = NULL;
        return ELECTION_TRIBE_NOT_EXIST;
    }
    free(string_holder);
    string_holder = malloc(intLength(area_id) + 1);
    if(string_holder == NULL)
    {
        return ELECTION_OUT_OF_MEMORY;
    }
    string_holder = itoa(area_id, string_holder, DECIMAL_BASE);
    if(mapContains(election->areas, string_holder) == false)
    {
        free(string_holder);
        string_holder = NULL;
        return ELECTION_AREA_NOT_EXIST;
    }

    free(string_holder);
    string_holder = NULL;
    
    if(status == VOTE_MANAGE_REMOVE)
    {
        num_of_votes = -num_of_votes;
    }

    VoteListResult result = voteListAdd(election->vote_list, area_id, tribe_id, num_of_votes);

    if(result == VOTE_LIST_OUT_OF_MEMORY)
    {
        return ELECTION_OUT_OF_MEMORY;
    }

    if(result == VOTE_LIST_NULL_ARGUMENT)
    {
        return ELECTION_NULL_ARGUMENT;
    }

    return ELECTION_SUCCESS;
}

static int intLength(int num)
{
    int counter = 1; //every number has at least one digit.
    while((num /= 10) > 0)
    {
        counter++;
    }

    return counter;
}
