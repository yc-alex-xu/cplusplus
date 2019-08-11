#include "link2.h"
#include <stdio.h>

void test_singly_linked()
{
    List *q = add_to_list(NULL, 999);
    q = add_to_list(q, 888);
    List *p = add_to_list(q, 777);
    p = add_to_list(p, 555); //p the head node
    delete_from_list(p, 777);
    p = reverse_list(p);
}

int main()
{
    test_singly_linked();
    return 0;
}