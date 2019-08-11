#include <stdio.h>
#include <stdlib.h>
struct List;
typedef struct List
{
    struct List *p_prev, *p_next;
    int value;
} List;

//add the new node before it
List *add_to_list(List *linkedList, int value)
{
    List *p = (List *)malloc(sizeof(List));
    p->value = value;
    if (linkedList == NULL)
    {
        p->p_prev = NULL;
        p->p_next = NULL;
    }
    else
    {
        List *prev = linkedList->p_prev;
        p->p_prev = linkedList->p_prev;
        p->p_next = linkedList;
        linkedList->p_prev = p;
        if (prev)
            prev->p_next = p;
    }

    return p;
}
static void del_node(List *p)
{
    if (p->p_prev)
        p->p_prev->p_next = p->p_next;
    if (p->p_next)
        p->p_next->p_prev = p->p_prev;
    free(p);
}
////return 0 if found
int delete_from_list(List *linkedList, int value)
{
    //try forward firstly
    List *prev = linkedList->p_prev;
    while (linkedList != NULL)
    {
        if (linkedList->value == value)
        {
            del_node(linkedList);
            return 0;
        }
        else
        {
            linkedList = linkedList->p_next;
        }
    }
    //try backword
    while (prev != NULL)
    {
        if (prev->value == value)
        {
            del_node(prev);
            return 0;
        }
        else
        {
            prev = prev->p_prev;
        }
    }
    return -1;
}

static void swap(List *prev, List *next)
{
    List *t = next;
    next = prev;
    prev = t;
}

List *reverse_list(List *linkedList)
{
    //try forward firstly
    List *p = linkedList;
    while (p)
    {
        swap(p->p_prev, p->p_next);
        p = p->p_prev; //because swapped already
    }
    //try backwoard
    p = linkedList->p_next; 
    while (p)
    {
        swap(p->p_prev, p->p_next);
        p = p->p_next; 
    }
    return linkedList;
}