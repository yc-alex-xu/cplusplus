#include <iostream>
#include <list>
#include <vector>
#include <array>
#include <algorithm>
#include "../toolkit.h"
using namespace std;

template <typename T, typename U>
void print_array(T *p, U len)
{
  FUNC_HEAD();
  for (int i = 0; i < len; i++)
    cout << *p++ << endl;
}
void test_array()
{
  FUNC_HEAD();
  constexpr int len = 4;
  array<int, len> arr = {9, 8, 7, 6};

  sort(arr.begin(), arr.end(), [](int a, int b) { return a < b; });
  for (auto v : arr)
    cout << v << endl;
  print_array(arr.data(), arr.size());
}

void test_vec_list()
{
  FUNC_HEAD();
  vector<int> v;
  list<int> l;
  for (int i = 0; i < 8; i++) ////往v和l中分别添加元素
  {
    v.push_back(i);
    l.push_back(i);
  }

  //vector iterator
  v[2];
  cout << "vector:";
  for (auto i : v)
    cout << i << " ";
  cout << endl;
  //end() need  substract 1
  cout << "first itertor point to:" << *(v.begin()) << "\t last iterator point to:" << *(v.end() - 1) << endl;
  cout << "2nd itertor point to:" << *(v.begin() + 1) << endl;
  vector<int>::iterator itv = v.begin();
  itv = itv + 2;

  //list iterator
  list<int>::iterator itl = l.begin();
  // list::iterator中重载了++，只能使用++进行迭代访问。
  cout << "list:";
  for (; itl != l.end(); itl++)
    cout << *itl << " ";
  cout << endl;
}

int main()
{
  test_array();
  test_vec_list();

  return 0;
}