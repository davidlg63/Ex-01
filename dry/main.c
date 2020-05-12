#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node_t {
    int x;
    struct node_t *next;
} *Node;

typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    EMPTY_LIST,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;

int getListLength(Node list);
bool isListSorted(Node list);
ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out);
ErrorCode createNodeByLength(int length, Node *created_node);
int maxLength(int length1, int length2);
void destroyList(Node head);
int main()
{

}

ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out)
{
    if(merged_out == NULL)
    {
        return  NULL_ARGUMENT;
    }

    if(list1 == NULL || list2 == NULL)
    {
        return  EMPTY_LIST;
    }

    if(!isListSorted(list1) || !isListSorted(list2))
    {
        return  UNSORTED_LIST;
    }
    int list1_len = getListLength(list1), list2_len = getListLength(list2);
    int max_length = maxLength(list1_len, list2_len);
    Node head = NULL;
    ErrorCode create_result = createNodeByLength(max_length, &head);
    if(create_result == MEMORY_ERROR)
    {
        return  MEMORY_ERROR;
    }
    Node output = head;
    merged_out = &head;
    int i;
    for(i = 0; i < list1_len && i < list2_len; i++)
    {
        if(list1 <= list2)
        {
            output->x = list1->x;
            list1 = list1->next;
        }
        else
        {
            output->x = list2->x;
            list2 = list2->next;
        }
        output = output->next;
    }

    for(; i < list1_len; i++)
    {
        output->x = list1->x;
        list1 = list1->next;
        output = output->next;
    }

    for(; i < list2_len; i++)
    {
        output->x = list2->x;
        list2 = list2->next;
        output = output->next;
    }

    return  SUCCESS;
}

ErrorCode createNodeByLength(int length, Node *created_node)
{
    Node head = malloc(sizeof(head));
    if(head == NULL)
    {
        return  NULL_ARGUMENT;
    }
    Node temp = head;
    for(int i = 1; i < length; i++)
    {
        Node current = malloc(sizeof(current));
        current->next = NULL;
        if(current == NULL)
        {
            destroyList(head);
            return  MEMORY_ERROR;
        }
        temp->next = current;
        temp = current;
    }
    created_node = &head;
}

int maxLength(int length1, int length2)
{
    return (length1 >= length2) ? length1 : length2;
}

void destroyList(Node head)
{
    if(head == NULL)
    {
        free(head);
        return;
    }
    Node temp = head;
    while(temp != NULL)
    {
        head = head->next;
        free(temp);
        temp = head;
    }
    return;
}