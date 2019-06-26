/*
g++ -g -std=c++11 main.cpp
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <vector>
#include "entry.h"
#include "../toolkit.h"

using namespace std;

namespace Estd
{
using namespace std;
template <typename C>
void sort(C &c)
{
  sort(c.begin(), c.end());
}
template <typename C, typename Pred>
void sort(C &c, Pred p)
{
  sort(c.begin(), c.end(), p);
}
// ...
} // namespace Estd

void vector_list_test()
{
  FUNC_HEAD();
  vector<Entry> vec{{"David Hume", 123456},
                    {"Karl Popper", 0},
                    {"Bertrand Russell", 345678},
                    {"Bertrand Russell", 345678}};

  vector<Entry> lst(vec.size());
  sort(vec.begin(), vec.end());
  unique_copy(vec.begin(), vec.end(), lst.begin()); // don’t copy adjacent equal elements

  cout << "\nunique_copy to vec(4): " << endl;
  for (auto e : lst)
    cout << e << endl;

  cout << "\nvector access via iterator: " << endl;
  vector<Entry>::iterator iter1;
  for (auto iter = vec.begin(); iter != vec.end(); iter++)
  {
    cout << iter->name << endl;
  }

  list<Entry> res;
  Estd::sort(vec);
  //If we wanted to place the unique elements in a new container
  //back_inser ter(res) constructs an iterator for res that adds elements at the end of a container
  //extending the container to make room for them. This saves us from first having to allocate a
  //fixed amount of space and then filling it.
  unique_copy(vec.begin(), vec.end(), back_inserter(res)); // append to res

  cout << "\nlist access via iterator after Estd::sort: " << endl;
  list<Entry>::iterator iter2;
  for (auto iter = res.begin(); iter != res.end(); iter++)
  {
    cout << iter->name << endl;
  }
}

bool has_c(const string &s, char c) // does s contain the character c?
{
  return find(s.begin(), s.end(), c) != s.end();
}

template <typename T>
using Iterator = typename T::iterator; // T’s iterator

template <typename C, typename V>
vector<Iterator<C>> find_all(C &c, V v)
{
  vector<Iterator<C>> res;
  for (auto p = c.begin(); p != c.end(); ++p)
    if (*p == v)
      res.push_back(p);
  return res;
}

void find_test()
{
  FUNC_HEAD();

  string s = "the test of the earth";
  vector<string::iterator> vec = find_all(s, 't');
  for (auto p : vec)
    cout << *p << endl;

  list<double> ld{1.1, 2.2, 3.3, 1.1};
  for (auto p : find_all(ld, 1.1))
    if (*p != 1.1)
      cout << "list bug!\n";

  vector<string> vs{"red", "blue", "green", "green", "orange", "red green"};
  for (auto p : find_all(vs, "red"))
    if (*p != "red")
      cout << "vector bug!\n";

  for (auto p : find_all(vs, "green"))
    *p = "vert";

  for (auto p : vs)
    cout << p << endl;
}

bool stream_iterator_test()
{
  FUNC_HEAD();
  ifstream is{"chp10.txt"};        // input stream for file "from"
  istream_iterator<string> ii{is}; // input iterator for stream
  istream_iterator<string> eos{};  // input sentinel

  ofstream os{"/tmp/temp.txt"};          // output stream for file "to"
  ostream_iterator<string> oo{os, "\n"}; // output iterator for stream
  vector<string> b{ii, eos};             // b is a vector initialized from input
  sort(b.begin(), b.end());              // sort the buffer
  unique_copy(b.begin(), b.end(), oo);   // copy buffer to output, discard replicated values
  return !is.eof() || !os;               // retur n error state (§1.3, §8.4)
}

bool stream_iterator_test2()
{
  FUNC_HEAD();

  ifstream is{"chp10.txt"};      // input stream for file "from"
  ofstream os{"/tmp/temp2.txt"}; // output stream for file "to"

  set<string> b{istream_iterator<string>{is},
                istream_iterator<string>{}}; // read input
  copy(b.begin(), b.end(),
       ostream_iterator<string>{os, "\n"}); // copy to output
  return !is.eof() || !os;                  // retur n error state (§1.3, §8.4)
}

void map_test()
{
  FUNC_HEAD();
  map<string, int> m{{"smith", 99}, {"john", 55}, {"jack", 33}};

  auto p = find_if(m.begin(), m.end(),
                   [](const pair<string, int> &r) { return r.second > 42; });
  cout << p->first << ':' << p->second << endl;
}

int main()
{
  vector_list_test();

  find_test();

  stream_iterator_test();

  stream_iterator_test2();

  map_test();

  return 0;
}