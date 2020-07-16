/*
demo of iterator, friend class
*/
#include <iostream>
#include "toolkit.h"
using namespace std;
class StackIter;

class Stack
{
private:
    int items[10];
    int sp;

public:
    friend class StackIter;
    Stack()
    {
        sp = -1;
    }
    void push(int in)
    {
        items[++sp] = in;
    }
    int pop()
    {
        return items[sp--];
    }
    bool isEmpty()
    {
        return (sp == -1);
    }
    StackIter *createIterator() const;
};

class StackIter
{
    const Stack *stk;
    int index;

public:
    StackIter(const Stack *s)
    {
        stk = s;
    }
    void first()
    {
        index = 0;
    }
    void next()
    {
        index++;
    }
    bool isDone()
    {
        return index == stk->sp + 1;
    }
    int currentItem()
    {
        return stk->items[index];
    }
};

StackIter *Stack::createIterator() const
{
    return new StackIter(this);
}

bool operator==(const Stack &l, const Stack &r)
{

    StackIter *itl = l.createIterator();
    StackIter *itr = r.createIterator();

    for (itl->first(), itr->first(); !itl->isDone(); itl->next(), itr->next())
        if (itl->currentItem() != itr->currentItem())
            break;
    bool ans = itl->isDone() && itr->isDone();
    delete itl;
    delete itr;
    return ans;
}

/* 
the example of friend class
 */
void friend_test()
{
    FUNC_HEAD();
    Stack s1;
    for (int i = 1; i < 5; i++)
        s1.push(i);
    Stack s2(s1), s3(s1); //no copy construction defined, using default one
    s3.pop();
    cout << "s1==s2?: " << (s1 == s2) << endl;
    /*
    if not equal, it mean the default copy constuction deep copy the
       int items[10];
    */
    cout << "s1==s3?: " << (s1 == s3) << endl;
}

int main()
{
    friend_test();
    return 0;
}
