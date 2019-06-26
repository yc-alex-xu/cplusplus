/*
* $ g++ -std=c++14 multi_mutex.cpp -lpthread
*/
#include <mutex>
#include <thread>
#include <iostream>
#include <string>
#include "../toolkit.h"

using namespace std;

struct Box
{
    explicit Box(int num) : num_things{num} {}
    int num_things;
    mutex m;
};

void transfer(Box &from, Box &to, int num)
{
    FUNC_HEAD();
    // don't actually take the locks yet
    unique_lock<mutex> lock1(from.m, defer_lock);
    unique_lock<mutex> lock2(to.m, defer_lock);
    // lock both unique_locks without deadlock
    lock(lock1, lock2);

    from.num_things -= num;
    to.num_things += num;
    //output once, otherwise will be interrrupted between "<<"s
    cout << "after mov " + to_string(num) +" \nFrom=" + to_string(from.num_things)
        + " \nTo=" + to_string(to.num_things) + "\n";
}

int main()
{
    Box acc1(100);
    Box acc2(50);

    thread t1(transfer, ref(acc1), ref(acc2), 10);
    thread t2(transfer, ref(acc2), ref(acc1), 5);

    t1.join();
    t2.join();

    cout << "acc1:\t" << acc1.num_things << "\tacc2 \t:" << acc2.num_things << endl;

    return 0;
}
