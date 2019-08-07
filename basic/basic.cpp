#include <complex>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <exception>
#include "../toolkit.h"

using namespace std;

void foo() // function that doesn’t return a value
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
  foo();
  sizes();
  find_bias();
  static_method_field();
  virtual_test();
  catch_exception(); //must be last one, because it will abort() the execution
  return 0;
}
