#include <iostream>
#include <list>
#include <vector>
#include "toolkit.h"
using namespace std;

template <typename T>
T sum(const vector<T> &v) //will not modify its argument
{
  T sum = 0;
  for (auto i : v)
    sum += i;
  return sum;
}

void vec_list_test()
{
  FUNC_HEAD();
  vector<int> v;
  list<int> l;

  for (int i = 0; i < 8; i++)
  {
    v.push_back(i);
    l.push_back(i);
  }

  cout << "vector:";
  for (auto i : v)
    cout << i << " ";
  cout << "\nitertor 1st:" << *(v.begin()) << " 3rd:" << *(v.begin() + 2) << " last :" << *(v.end() - 1) << endl;
  const int s1 = sum(v); // OK: evaluated at run time
  cout << "sum: " << s1 << endl;
  // constexpr int s3 = sum(v); // error : sum(v) not constant expression

  list<int>::iterator itl = l.begin();
  // list::iterator中重载了++，只能使用++进行迭代访问。
  cout << "list:";
  for (; itl != l.end(); itl++)
    cout << *itl << " ";
  cout << endl;
}

int main()
{
  vec_list_test();
  return 0;
}