/*  $ g++  condition_var.cpp  -lpthread

 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

#include "../toolkit.h"
using namespace std;

queue<int> products;
mutex m;
condition_variable cv_prod, cv_consumer;
bool done = false;

void producer()
{
    for (int i = 0; i < 10; ++i)
    {
        cout << " producing " << i << '\n';
        products.push(i);
        cv_prod.notify_one();
        unique_lock<mutex> lk(m);
        cv_consumer.wait_for(lk, 100ms, [] { return false; });
    }
    done = true;
}

void consumer()
{
    while (!done)
    {
        unique_lock<mutex> lk(m);
        cv_prod.wait_for(lk, 100ms, [] { return false; });
        while (!products.empty())
        {
            cout << " consuming " << products.front() << '\n';
            products.pop();
        }
        cv_consumer.notify_one();
    }
}

void producer_consumer_test()
{
    FUNC_HEAD();
    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();
}

int main()
{
    producer_consumer_test();
    return 0;
}