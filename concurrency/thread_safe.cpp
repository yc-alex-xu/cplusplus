//$ g++ -std=c++14  thread_safe.cpp -lpthread

#include <thread>
#include <mutex>
#include <iostream>
#include "../toolkit.h"

using namespace std;
mutex m;

thread_local int g_n = 1;
void f()
{
    for (auto i = 0; i < 100000; i++)
        g_n++;
    cout << __func__ << ":\t" << g_n << endl;
}

void g()
{
    thread_local int j = 0;
    for (auto i = 0; i < 100000; i++)
        j++;
    cout << __func__ << ":\t" << g_n << "\t" << j << endl;
}

void thread_local_test()
{
    FUNC_HEAD();
    thread t1(f);
    thread t2(f);
    thread t3(g);
    thread t4(g);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

// 一个函数被称为线程安全的（thread-safe），当且仅当被多个并发进程反复调用时，它会一直产生正确的结果
int gi = 1000;
mutex m_gi;

void thread_safe_1()
{
    int i = 0;
    i++;
    m_gi.lock();
    gi += 100;
    m_gi.unlock();
}

void thread_safe_2()
{
    int j = 0;
    j++;
    m_gi.lock();
    gi -= 100;
    m_gi.unlock();
}

void thread_safe_test()
{
    FUNC_HEAD();

    cout << "thread safe start gi=:\t" << gi << endl;
    thread t1(thread_safe_2);
    thread t2(thread_safe_1);
    thread t3(thread_safe_1);
    thread t4(thread_safe_2);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << "thread safe end   gi=:\t" << gi << endl;
}

//可重入函数：可重入函数是线程安全函数的一种，其特点在于它们被多个线程调用时，不会引用任何共享数据。
//可重入函数通常要比不可重入的线程安全函数效率高一些，因为它们不需要同步操作。
void add_r(int &balance, int change)
{
    balance += change;
}

void thread_reentrant_1()
{
    int i = 100;
    add_r(gi, i);
}

void thread_reentrant_2()
{
    int i = 100;
    add_r(gi, -i);
}

void thread_reentrant_test()
{
    FUNC_HEAD();
    thread t1(thread_reentrant_2);
    thread t2(thread_reentrant_1);
    thread t3(thread_reentrant_1);
    thread t4(thread_reentrant_2);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << "thread reentrant :\t" << (gi == 1000) << endl;
}

int main()
{
    thread_local_test();
    thread_safe_test();
    thread_reentrant_test();
    return 0;
}