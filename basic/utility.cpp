//g++  -g -std=c++14

#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <forward_list>
#include <iostream>
#include <memory>
#include <vector>
#include "../toolkit.h"

using namespace std;

void binary(int i)
{
  bitset<8 * sizeof(int)> b = i; // assume 8-bit byte (see also §12.7)
  cout << b.to_string() << '\n'; // wr ite out the bits of i
}

void bitset_test()
{
  FUNC_HEAD();

  bitset<9> bs1{"110001111"}; // 399
  bitset<9> bs2{399};

  bitset<9> bs3 = ~bs1;      // complement: bs3=="001110000"   512-bs1-1
  bitset<9> bs4 = bs1 & bs3; // all zeros
  bitset<9> bs5 = bs1 << 2;  // shift left: bs5 = "111000000"
  cout << bs5.to_string() << endl;

  binary(3721);
}

/*************************
 * for equal_range_test()
 * 
 */
struct Record
{
  string name;
  int score;
  inline bool operator==(const Record &r) const
  {
    return (this->name == r.name);
  }
};

ostream &operator<<(ostream &os, const Record &r)
{
  os << r.name << ":" << r.score << endl;
  return os;
}

auto rec_eq = [](const Record &r1, const Record &r2) {
  return r1.name < r2.name;
};
// compare names
void find_item(const vector<Record> &v) // assume that v is sorted on its "name" field
{
  auto er = equal_range(v.begin(), v.end(), Record{"John"}, rec_eq);
  for (auto p = er.first; p != er.second; ++p)
    cout << *p;

  cout << *(er.first) << *(er.second);
}

void equal_range_test()
{
  FUNC_HEAD();
  vector<Record> vec = {
      {"John", 33}, {"Emma", 44}, {"sara", 77}, {"Smith", 33}, {"John", 77}};

  sort(vec.begin(), vec.end(),
       [](Record r1, Record r2) { return r1.name < r2.name; });
  for (auto x : vec)
    cout << x;
  auto pp =
      make_pair(vec.begin(), 2); // pp is a pair<vector<str ing>::iterator,int>

  tuple<string, int, double> t2{"Sild", 123,
                                3.14}; // the type is explicitly specified
  auto t = make_tuple(string{"Herring"}, 10,
                      1.23); // the type is deduced to tuple<string,int,double>
  string s = get<0>(t);      // get first element of tuple: "Herring"
  int x = get<1>(t);         // 10
  double d = get<2>(t);      // 1.23
  cout << s << ':' << x << ':' << d << endl;

  find_item(vec);
}

/*************************
 * for limit_test()
 * 
 */

void limit_test()
{
  FUNC_HEAD();
  constexpr float min = numeric_limits<float>::min();
  constexpr int szi = sizeof(int);
  cout << min << endl;
  cout << szi << endl;
}

/*
sort_test()

 */
template <typename C>
using Iterator_type = typename C::iterator; // C’s iterator type
template <typename Iter>
using Iterator_category =
    typename std::iterator_traits<Iter>::iterator_category; // Iter’s categor y

template <typename Ran> // for random-access iterators
void sort_helper(Ran beg, Ran end,
                 random_access_iterator_tag) // we can subscript into [beg:end)
{
  sort(beg, end); // just sort it
}

template <typename C>
using Value_type = typename C::value_type; // C’s value type

template <typename For> // for forward iterators
void sort_helper(For beg, For end,
                 forward_iterator_tag) // we can traverse [beg:end)
{
  vector<Value_type<For>> v{beg, end}; // initialize a vector from [beg:end)
  sort(v.begin(), v.end());
  copy(v.begin(), v.end(), beg); // copy the elements back
}

template <typename C>
void sort(C &c)
{
  using Iter = Iterator_type<C>;
  sort_helper(c.begin(), c.end(), Iterator_category<Iter>{});
}

template <typename T>
constexpr bool Is_arithmetic()
{
  return std::is_arithmetic<T>::value;
}

void new_sort(vector<string> &v, forward_list<int> &lst)
{
  sort(v);   // sor t the vector
  sort(lst); // sor t the singly-linked list
}

void sort_test()
{
  FUNC_HEAD();

  vector<string> v{"abc", "kkk", "jjj"};
  forward_list<int> lst{7, 8, 1};
  new_sort(v, lst);
}

/*
 predict_test()
 */
void predict_test()
{
  FUNC_HEAD();

  bool b1 = Is_arithmetic<int>();
  bool b2 = Is_arithmetic<string>();
  cout << b1 << endl
       << b2 << endl;
}

int main()
{
  bitset_test();
  equal_range_test();
  limit_test();
  sort_test();
  predict_test();
  return 0;
}