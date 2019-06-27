/*  $ g++ simple.cpp -lpthread
 */

#include <iostream>
#include <thread>
#include <mutex>
#include "../toolkit.h"
using namespace std;

void foo()
{
    cout << " hello world " << endl;
}

void test_thread1()
{
    FUNC_HEAD();
    thread t(foo);
    t.join();
}

mutex mtx;
int balance = 100;
int count = 0;

void save_withdraw(int money)
{
    unique_lock<mutex> lock(mtx);
    lock.unlock();
    for (int i = 0; i < 100; i++)
    {
        lock.lock();
        count++;
        balance += money;
        balance -= money;
        lock.unlock();
    }
}

void test_unique_lock()
{
    FUNC_HEAD();
    thread thd1(save_withdraw, 10);
    thread thd2(save_withdraw, -20);
    thd1.join();
    thd2.join();
    cout << "balacne=" << balance << " count=" << count << endl;
}

int main()
{
    test_thread1();

    test_unique_lock();

    return 0;
}