/*
http://www.stroustrup.com/bstechfaq.htm
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Empty
{
};

void f()
{
  Empty a, b;
  if (&a == &b)
    cout << "impossible: report error to compiler supplier";

  Empty *p1 = new Empty;
  Empty *p2 = new Empty;
  if (p1 == p2)
    cout << "impossible: report error to compiler supplier";
}

struct X : Empty
{
  int a;
  // ...
};

void f(X *p)
{
  void *p1 = p;
  void *p2 = &p->a;
  if (p1 == p2)
    cout << "nice: good optimizer\n";
}

class B
{
public:
  int f(int i)
  {
    cout << "f(int): ";
    return i + 1;
  }
  // ...
};

class D : public B
{
public:
  using B::f; // make every f from B available
  double f(double d)
  {
    cout << "f(double): ";
    return d + 1.3;
  }
  // ...
};

#include <string>
#include <sstream>

string itos(int i) // convert int to string
{
  stringstream s;
  s << i;
  return s.str();
}

int main()
{
  vector<double> v;

  double d;
  cout << "plese input some unubmer ,end with ctrl-d" << endl;

  while (cin >> d)
    v.push_back(d); // read elements
  if (!cin.eof())
  { // check if input
    // failed如果你在UNIX上运行这个程序，可以用Ctrl-D输入EOF
    cerr << "format error\n";
    return 1; // error return
  }

  cout << "read " << v.size() << " elements\n";

  reverse(v.begin(), v.end());
  cout << "elements in reverse order:\n";
  for (auto x : v)
    cout << x << '\n';

  f();

  struct X b;
  f(&b);

  D *pd = new D;

  cout << pd->f(2) << '\n';
  cout << pd->f(2.3) << '\n';

  string s = itos(234);
  cout << s << endl;

  return 0; // success return
}