//$ g++ -std=c++14 no_mutex.cpp -lpthread

#include <iostream>
#include <thread>
#include "../toolkit.h"

using namespace std;

void f1(int n)
{
    for (int i = 0; i < 5; ++i)
    {
        cout << "Thread 1 executing\n";
        ++n;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void f2(int &n)
{
    for (int i = 0; i < 5; ++i)
    {
        cout << "Thread 2 executing\n";
        ++n;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void thread_param_test()
{
    FUNC_HEAD();
    int n = 0;
    thread t1; // t1 is not a thread

    thread t2(f1, n + 1);  // pass by value
    thread t3(f2, ref(n)); // pass by reference

    thread t4(move(t3)); //  t3 is no longer a thread

    // Blocks the current thread until the thread identified by *this finishes its execution.
    t2.join();
    t4.join();

    // t1.join(); terminating with uncaught exception of type std::__1::system_error: thread::join failed: Invalid argument

    cout << "\n\nFinal value of n is " << n << '\n';
}

void f3()
{
    FUNC_HEAD();
}

/* 

在传统的C线程中，会有一个void*参数用于给线程函数传递参数，但是Boost.Thread去是直接构造线程对象，
除了一个函数名之外没有其它的参数，那么如果使用传统的方式（直接将函数名称传入）
就只能执行无参数的函数了，所以这里使用了函数对象来实现参数的传递。

 */
struct F
{
    //  函数对象，就是一个重载'()'运算符的类的对象。这样就可以直接使用‘对象名()’的方式，这跟调用函数一样
    void operator()(int i)
    {
        FUNC_HEAD();
        cout << i << endl;
    };
};

void thread_func_test()
{
    FUNC_HEAD();
    F f4;
    f4(333);
    thread t1(f3);
    thread t2(f4, 777);
    t1.join();
    t2.join();
}

int main()
{
    thread_param_test();
    thread_func_test();
    return 0;
}
