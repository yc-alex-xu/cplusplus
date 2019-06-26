#include <complex>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <exception>
#include "../toolkit.h"

using namespace std;

template <typename T>
T sum(const vector<T> &v) //will not modify its argument
{
  T sum = 0;
  for (auto i : v)
    sum += i;
  return sum;
}

void some_function() // function that doesn’t return a value
{
  FUNC_HEAD();
  double d = 2.2; // initialize floating-point number
  int i = 7;      // initialize integer
  d = d + i;      // assign sum to d
  i = d * i;      // assign product to i (truncating the double d*i to an int)

  double d1 = 2.3;
  double d2{2.3};
  complex<double> z = 1; // a complex number with double-precision floating-point scalars
  complex<double> z2{d1, d2};
  complex<double> z3 = {1, 2}; // the = is optional with { ... }

  auto bb = true;    // a bool
  auto chch = 'x';   // a char
  auto ii = 123;     // an int
  auto dd = 1.2;     // a double
  auto zz = sqrt(d); // z has the type of whatever sqr t(y) retur ns

  auto x = 3;
  auto y = 5;
  x += y; // x = x+y
  ++x;    // increment: x = x+1
  x -= y; // x = x-y
  --x;    // decrement: x = x-1
  x *= y; // scaling: x = x*y
  x /= y; // scaling: x = x/y
  x %= y; // x = x%y

  const int dmv = 17;
  int var = 17;
  constexpr double max1 = 1.4 * dmv;
  // constexpr double max2 = 1.4 * var; // error : var is not a constant expression
  const double max3 = 1.4 * var; // OK, may be evaluated at run time

  vector<double> v{1.2, 3.4, 4.5}; // v is not a constant
  const double s1 = sum(v);        // OK: evaluated at run time
  // constexpr double s2 = sum(v); // error : sum(v) not constant expression
}

void iter_a_array()
{
  int arr[4];
  FUNC_HEAD();

  for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
  {
    arr[i] = i * i;
  }

  for (auto &v : arr)
  {
    v--;
    cout << v << '\t';
  }
  cout << endl;
}

void find_bias()
{
  typedef struct
  {
    int a;
    int b;
  } struc_t;
  FUNC_HEAD();
  struc_t a;
  cout << static_cast<void *>(&(a.b)) << ":" << static_cast<void *>(&a) << endl;
  size_t bias = (char *)&(a.b) - (char *)(&a);
  cout << bias << endl;

  bias = (size_t) & (((struc_t *)0)->b);
  cout << bias << endl;
}

void sizes()
{
  FUNC_HEAD();
  cout << sizeof(short) << endl;
  cout << sizeof(int) << endl;
  cout << sizeof(long) << endl;
  cout << sizeof(long long) << endl;

  cout << sizeof(float) << endl;
  cout << sizeof(double) << endl;

  int a = 2;
  string b;
  LINE_NO();
  cout << &a << "\t" << sizeof(&a) << endl;
  LINE_NO();
  cout << &b << "\t" << sizeof(&b) << ":" << sizeof(b) << endl;
}

void catch_exception()
{
  int x = 1;
  int y = 0;
  FUNC_HEAD();
  try
  {
    x /= y;
  }
  catch (exception &err)
  {
    cerr << err.what() << endl;
  }
}

class Account
{
private:
  static double m_rate; //静态数据成员，类中声明
public:
  double get_rate() { return m_rate; }
  static void set_rate(const double &x) { m_rate = x; }
};
double Account::m_rate = 8.0; //private静态数据成员在类外初始化

void static_method_field()
{
  FUNC_HEAD();
  Account a;              //before class construction, m_rate = 8.0 already
  Account::set_rate(5.0); //通过class name调用static函数
  a.set_rate(7.0);
  cout << "at last,rate was set as " << a.get_rate() << endl;
}

int stl_set_test()
{
  FUNC_HEAD();
  set<int> iset;
  iset.insert(11);
  iset.insert(55);
  iset.insert(33);
  iset.insert(44);
  iset.insert(22);

  set<int>::iterator it;
  for (it = iset.begin(); it != iset.end(); it++)
  {
    cout << *it << "\t";
  }
  cout << endl;

  int i = 33;
  if (binary_search(iset.begin(), iset.end(), i))
    cout << "found " << i << endl;
  else
    cout << "can't find " << i << endl;
}

void alg_test()
{
  FUNC_HEAD();
  int a[] = {5, 7, 2, 1};
  sort(a, a + 4);
  ;
  rotate(a, a + 2, a + 4);
  reverse(a, a + 4);
  for (auto v : a)
    cout << v << "\t";
  cout << endl;
}

class a
{
public:
  a() { cout << "a" << endl; }
  virtual void disp() { cout << "a disp" << endl; }
  virtual ~a() { cout << "~a" << endl; }
};

class b : public a
{
public:
  b() { cout << "b" << endl; }
  ~b() { cout << "~b" << endl; }
};

class c : public b
{
public:
  c() { cout << "c" << endl; }
  void disp() { cout << "c:disp" << endl; }
  ~c() { cout << "~c" << endl; }
};

/* check the order of construction/deconstruction
*/
int virtual_test()
{
  FUNC_HEAD();
  a *p = new c();
  p->disp();
  delete p;
  return 0;
}

int main()
{
  some_function();
  iter_a_array();
  sizes();
  find_bias();
  static_method_field();
  stl_set_test();
  alg_test();
  virtual_test();

  catch_exception(); //must be last one, because it will abort() the execution
  return 0;
}
