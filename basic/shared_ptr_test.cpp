/*  $ g++ -std=c++14 shared_ptr_test.cpp -lpthread
*/

/* std::shared_ptr is a smart pointer that retains shared ownership of an object through a pointer.
 Several shared_ptr objects may own the same object. The object is destroyed and its memory 
 deallocated when either of the following happens:

the last remaining shared_ptr owning the object is destroyed;
the last remaining shared_ptr owning the object is assigned another pointer via operator= or reset().
 */

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include "../toolkit.h"

using namespace std;

struct Base
{
    Base() { cout << "  Base::Base()\n"; }
    // Note: non-virtual destructor is OK here
    ~Base() { cout << "  Base::~Base()\n"; }
};

struct Derived : public Base
{
    Derived() { cout << "  Derived::Derived()\n"; }
    ~Derived() { cout << "  Derived::~Derived()\n"; }
};

/* this thread print different  lp.use_count() value under different gcc version
*  can check via: https://en.cppreference.com/w/cpp/memory/shared_ptr
*/
void thr(shared_ptr<Base> p)
{
    this_thread::sleep_for(chrono::seconds(3));
    shared_ptr<Base> lp = p; // thread-safe, even though the
                             // shared use_count is incremented
    {
        static mutex io_mutex;
        lock_guard<mutex> lk(io_mutex);
        FUNC_HEAD();
        cout << "local pointer in a thread:\n"
             << "  get() return " << lp.get()
             << " use_count() = " << lp.use_count() << '\n';
    }
}

int main()
{
    FUNC_HEAD();
    shared_ptr<Base> p = make_shared<Derived>();
    cout << "p.unique()" << boolalpha << p.unique() << endl;

    shared_ptr<Base> p2 = p;
    cout << "p.unique()" << boolalpha << p.unique() << endl;
    p2 = nullptr;
    cout << "p.unique()" << boolalpha << p.unique() << endl;
    cout << "endof of unique() demo" << endl;

    cout << endl
         << endl;
    FUNC_HEAD();
    cout << " get() return " << p.get()
         << " use_count() = " << p.use_count() << '\n';
    thread t1(thr, p), t2(thr, p), t3(thr, p);

    p.reset(); // release ownership while threads still sleep

    FUNC_HEAD();
    cout
        << "shared ptr after reset:\n"
        << " get() return " << p.get()
        << " use_count() = " << p.use_count() << '\n';
    t1.join();
    t2.join();
    t3.join();
    FUNC_HEAD();
    cout << "All threads completed now\n\n";
}