#include "link.h"
#include <stdio.h>


void test_doubly_linked()
{
    List *q = add_to_list(NULL, 999);
    q = add_to_list(q, 888);
    List *p = add_to_list(q, 777);
    p = add_to_list(p, 555);
    delete_from_list(q, 555);
    p = reverse_list(q);

}

int main()
{
    test_doubly_linked();
    return 0;
}