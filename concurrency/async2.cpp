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

/*
The template function async runs the function f asynchronously
 (potentially in a separate thread which may be part of a thread pool) 
 and returns a std::future that will eventually hold the result of that function call.

 limitation: no rsource lock needed
*/
/*
template< class InputIt, class T >
T accumulate( InputIt first, InputIt last, T init );
*/
int async_sum()
{
  FUNC_HEAD();
  vector<int> v(10000, 1);
  int i = 0;
  auto iter = v.begin();
  auto sum_1_half = async(accumulate<vector<int>::iterator, int>, iter, iter + v.size() / 2, i);
  auto sum_2_half = async(accumulate<vector<int>::iterator, int>, iter + v.size() / 2, v.end(), i);

  return (sum_1_half.get() + sum_2_half.get());
}

int main()
{
  auto sum = async_sum();
  cout << "\n\nThe sum =" << sum << endl;
}