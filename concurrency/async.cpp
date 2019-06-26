/*
g++ -std=c++14 -lpthread  

for Ubuntu, -lpthread must be at the end of command line
$ g++ -std=c++14   async.cpp -lpthread

and a very good news: it can run under WSL
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

template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
  chrono::seconds sec(1);
  auto len = end - beg;

  if (len < 1000)
  {
    cout << "this thread can't split, here len=" + to_string(len) + "\n";
    cout.flush();
    this_thread::sleep_for(sec);
    return accumulate(beg, end, 0); //Defined in header <numeric>
  }

  RandomIt mid = beg + len / 2;
  auto handle =
      async(launch::async, parallel_sum<RandomIt>, mid, end);
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