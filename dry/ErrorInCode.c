//
// Created by David on 15/04/2020.
//
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//code convention error: function names should be verbs + the bracket should be in a new line
char *stringDuplicator(char *s, int times) { //code convention error: s should be replaced with a more meaningful name.
    assert(!s);
    assert(times > 0);
    int LEN = strlen(s); //variable name should be in lower case letters. (code convention error)
    char *out = malloc(LEN * times); //coding error
    assert(out); //coding error
    // coding error: out should be initialized to an empty string(now it contains "garbage").
    for (int i = 0; i < times; i++) {
        out = out + LEN;//coding error
        strcpy(out, s);
    }
    return out;//error: returns pointer to the end of the string. a temp var should be introduced.
}

// Corrected version:
char *duplicateString(char *str, int times)
{
    assert(!str);
    assert(times > 0);
    int len= strlen(str);
    char *out = malloc(sizeof(*out)*len*times + 1);
    if(out == NULL){
        return NULL;
    }
    *out = "";
    char *tmp = out;
    for (int i = 0; i < times; i++) {
        strcpy(tmp, str);
        tmp = tmp + len;
    }
    return out;
}