#include <stdio.h>
#include <stdlib.h>
struct List;
typedef struct List
{
    struct List  *p_next;
    int value;
} List;

//add the new node before it
List *add_to_list(List *linkedList, int value)
{
    List *p = (List *)malloc(sizeof(List));
    p->value = value;
    if (linkedList == NULL)
    {
        p->p_next = NULL;
    }
    else
    {
        p->p_next = linkedList;
    }

    return p;
}
static void del_node(List *prev, List *p)
{
    if (prev){
        prev->p_next = p->p_next;
    } 
    free(p);
}
//return 0 if found
int delete_from_list(List *linkedList, int value)
{
    List *prev = NULL;
    while (linkedList != NULL)
    {
        if (linkedList->value == value)
        {
            del_node(prev,linkedList);
            return 0;
        }
        else
        {
            prev = linkedList;
            linkedList = linkedList->p_next;
        }
    }
    return -1;
}

List *reverse_list(List *linkedList)
{
    
    List *p = linkedList->p_next;
    linkedList->p_next = NULL; //becasue it is head node
    List *prev =  linkedList;
    while (p)
    {
        List * tmp = p->p_next;
        p->p_next= prev;
        prev = p;
        p = tmp;
    }
    return prev;        //return the new head node
}