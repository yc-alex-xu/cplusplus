/*
for WSL/Ubuntu, -lpthread must be at the end of command line
$ g++ async.cpp -lpthread
*/

#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include "../toolkit.h"
using namespace std;

template <typename T>
int parallel_sum(T beg, T end)
{
  auto len = end - beg;

  if (len < 1000)
  {
    cout << "len=" + to_string(len) + "\n";  //output once to avoid interrupt
    this_thread::sleep_for(1ms);
    return accumulate(beg, end, 0); //Defined in header <numeric>
  }

  T mid = beg + len / 2;
  auto handle =
      async(launch::async, parallel_sum<T>, mid, end);
  int sum = parallel_sum(beg, mid);
  return sum + handle.get();
}

void async_parallel()
{
  FUNC_HEAD();
  vector<int> v(10000, 1);
  int sum = parallel_sum(v.begin(), v.end());

  cout << "\n\nThe sum =" << sum << '\n';
}

int main()
{
  async_parallel();
}