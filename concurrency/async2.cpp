/*
$ g++ -std=c++14 async2.cpp -lpthread
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include "../toolkit.h"
using namespace std;

template <typename Iterator, typename T>
T async_sum(Iterator first, Iterator last, T init)
{
  FUNC_HEAD();
  /*
The template function async runs the function f asynchronously
 (potentially in a separate thread which may be part of a thread pool) 
 and returns a std::future that will eventually hold the result of that function call.

 limitation: no rsource lock needed
*/
  unsigned long const length = std::distance(first, last);
  if (!length) // 1
    return init;

  unsigned long const min_per_thread = 1000;
  unsigned long const max_threads =
      (length + min_per_thread - 1) / min_per_thread; // 2

  unsigned long const hardware_threads =
      std::thread::hardware_concurrency();

  cout << " hardware_threads: " << hardware_threads << endl;
  unsigned long const num_threads = // 3
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  cout << " num_threads: " << num_threads << endl;
  unsigned long const block_size = length / num_threads; // 4

  std::vector<std::future<int>> threads(num_threads); // 5

  auto iter = first;
  for (auto i = 0; i < num_threads; ++i)
  {
    auto iter_end = iter + block_size;
    if (i == num_threads - 1)
    {
      iter_end = last;
    }
    threads[i] = async(accumulate<vector<int>::iterator, int>, iter, iter_end, 0);
    iter = iter_end;
  }
  T sum = 0;
  for (auto &t : threads)
  {
    sum += t.get();
  }
  return sum;
}

int main()
{
  vector<int> v(1000000, 1);
  unsigned long init = 0;
  auto sum = async_sum(v.begin(), v.end(), init);
  cout << "\n\nThe sum =" << sum << endl;
}