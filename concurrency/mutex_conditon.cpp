/* 
* $g++ -std=c++14 mutex_conditon.cpp -lpthread
*/
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include "../toolkit.h"

using namespace std;
mutex m;

struct F
{ // function object
  vector<double> &v;
  double *res;
  F(vector<double> &vv, double *r) : v{vv}, res(r) {}

  // fuction object
  void operator()()
  {
    cout << __func__ << endl;
    *res = 0;
    for (auto x : v)
    {
      m.lock();
      cout << x << "\t";
      m.unlock();
      *res += x;
    }
    cout << endl;
  };
};

void f(vector<double> &v, double &sum)
{
  FUNC_HEAD();
  sum = 0;
  for (auto x : v)
  {
    m.lock();
    cout << x << "\t";
    m.unlock();
    sum += x;
  }
  cout << endl;
}

mutex m_cout;
void f_seq(vector<double> &v, double &sum)
{
  FUNC_HEAD();
  sum = 0;
  unique_lock<mutex> lck{m_cout};
  for (auto x : v)
  {
    cout << x << "\t";
    sum += x;
  }
  cout << endl;
  cout.flush();
  m_cout.unlock(); //will unlock implicitly  when func end
}

#include <utility>
void mutex_test()
{
  FUNC_HEAD();
  vector<double> some_vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<double> vec2{10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

  double res1;
  double res2;
  cout << "two thread will print 0~19 in two sequence" << endl;
  thread t1(f, ref(some_vec), ref(res1));
  thread t2{F{vec2, &res2}}; // F(vec2)() executes in a separate thread
  t1.join();
  t2.join();
  cout << "thread 1 return:" + to_string(res1) +
              "\t thread 2 return:" + to_string(res2) + "\n" +
              "two thread will print 0~19 in one sequence\n";

  thread t3(f, ref(some_vec), ref(res1));
  thread t4(f, ref(vec2), ref(res2));
  t3.join();
  t4.join();
  cout << "thread 1 return:" + to_string(res1) +
              "\t thread 2 return:" + to_string(res2) + "\n";
}

#include <condition_variable>
#include <queue>

struct Message
{
  Message(string s) : body(s){};
  string body;
};
queue<Message> mqueue;    // the queue of messages
condition_variable mcond; // the variable communicating events
mutex mmutex;             // the locking mechanism
void consumer()
{
  for (;;)
  {
    unique_lock<mutex> lck{mmutex};
    mcond.wait(lck);
    while (!mqueue.empty())
    {
      auto m = mqueue.front();
      mqueue.pop();
      cout << m.body << endl;
    }
  }
}

void producer()
{
  for (int i = 0; i < 10; i++)
  {
    Message m("messge:" + to_string(i));
    unique_lock<mutex> lck{mmutex};
    mqueue.push(m);
    mcond.notify_one(); // notify
  }
}

void cond_test()
{
  FUNC_HEAD();
  thread t1(producer);
  thread t2(consumer);
  t1.join();
  t2.join();
}

int main()
{
  mutex_test();
  cond_test();
  return 0;
}
