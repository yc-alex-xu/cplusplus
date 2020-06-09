
#include <iostream>

using namespace std;

typedef struct node
{
    int val;
    node *pNext;
} node;

void display(node *pHead)
{
    for (node *p = pHead; p; p = p->pNext)
    {
        cout << p->val << '\t';
    }
    cout << endl;
}

//return new head
node *reverse(node *p)
{
    node *next = p->pNext;
    if (next)
    {
        node *nh = reverse(next);
        next->pNext = p;
        return nh;
    }
    else{
        return p;
    }
}

node *reverse_it(node *pHead)
{
    node *prev = NULL;
    for (node *p = pHead; p != NULL;)
    {
        node *next = p->pNext;
        p->pNext = prev;
        prev = p;
        p = next;
    }

    return prev;
}

int main()
{
    node *pHead = NULL;

    for (int i = 10; i > 0; i--)
    {
        node *p = new node;
        p->val = i;
        p->pNext = pHead;
        pHead = p;
    }

    display(pHead);
    /*
    node *nh =reverse(pHead);
    pHead->pNext = NULL;
    */
    node *nh =reverse_it(pHead);
    display(nh);
}
