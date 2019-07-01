//$ $ g++ -Wall -std=c++1z thread_safe.cpp -lpthread

#include <thread>
#include <mutex>
#include <iostream>
#include "../toolkit.h"

using namespace std;

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
    //C++17中添加了一个新特性，称为模板类参数推导，这样类似std::locak_guard这样简单的模板类型的模板参数列表可以省略。
    //lock_guard<mutex> guard(m_gi);
    lock_guard guard(m_gi);

    /*
    C++中通过实例化std::mutex创建互斥量实例，通过成员函数lock()对互斥量上锁，unlock()进行解锁。不过，实践中不推荐直接去调用成员函数，调用成员函数就意味着，必须在每个函数出口都要去调用unlock()，也包括异常的情况。C++标准库为互斥量提供了一个RAII语法的模板类std::lock_guard，在构造时就能提供已锁的互斥量，并在析构的时候进行解锁，从而保证了一个已锁互斥量能被正确解锁。
   */

    //m_gi.lock();
    gi += 100;
    //m_gi.unlock();
}

void thread_safe_2()
{
    int j = 0;
    j++;
    lock_guard guard(m_gi);
    gi -= 100;
}

void thread_safe_test()
{
    FUNC_HEAD();

    cout << "start with gi=:\t" << gi << endl;
    thread t1(thread_safe_2);
    thread t2(thread_safe_1);
    thread t3(thread_safe_1);
    thread t4(thread_safe_2);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << "end with gi=:\t" << gi << endl;
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
    cout << "start with gi=" << gi << endl;
    thread t1(thread_reentrant_2);
    thread t2(thread_reentrant_1);
    thread t3(thread_reentrant_1);
    thread t4(thread_reentrant_2);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cout << "end with gi=" << gi << endl;
}

int main()
{
    thread_local_test();
    thread_safe_test();
    thread_reentrant_test();
    return 0;
}