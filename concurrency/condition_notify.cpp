/* 
* $g++ -std=c++14 condition_notify.cpp -lpthread
*
* waring : "data" is ambiguous
*/
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include "../toolkit.h"

using namespace std;

/*
The condition_variable class is a synchronization primitive that can be used to block a thread,
 or multiple threads at the same time, until another thread both modifies a shared variable (the condition),
  and notifies the condition_variable.
*/

mutex m;
condition_variable cv;
string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    FUNC_HEAD();
    unique_lock<mutex> lk(m);

    /*
    void wait( std::unique_lock<std::mutex>& lock, Predicate pred );
    Equivalent to
    while (!pred()) {
        wait(lock);
    }

    		
    The concept Predicate<F, Args...> specifies that F is a predicate that 
    accepts arguments whose types and value categories are encoded by Args..., i.e., 
    it can be invoked with these arguments to produce a Boolean result.

    */

    cv.wait(lk, [] { return ready; });

    // after the wait, we own the lock.
    cout << "Worker thread is processing data\n";
    data += " after processing";

    // Send data back to main()
    processed = true;
    cout << "Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}

int main()
{
    thread worker(worker_thread);

    data = "Example data";
    // send data to the worker thread
    {
        /*
        The class lock_guard is a mutex wrapper 
        that provides a convenient RAII-style mechanism for owning a mutex for the duration of a scoped block.

        When a lock_guard object is created, it attempts to take ownership of the mutex it is given.
        When control leaves the scope in which the lock_guard object was created, the lock_guard is destructed and the mutex is released.
        */
        lock_guard<mutex> lk(m);
        ready = true;
        cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();

    // wait for the worker
    {
        unique_lock<mutex> lk(m);
        cv.wait(lk, [] { return processed; });
    }
    cout << "Back in main(), data = " << data << '\n';

    worker.join();
}