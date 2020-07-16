#include <complex>
#include <iostream>
#include <exception>
#include "toolkit.h"

using namespace std;

void type_arithmetic_test() // function that doesn’t return a value
{
  FUNC_HEAD();

  double d1 = 2.3;
  double d2{2.3};
  complex<double> z = 1;
  complex<double> z2{d1, d2};
  complex<double> z3 = {1, 2};
  cout << "the complex z,z2,z3:" << z << " " << z2 << " " << z3 << endl;

  auto b = true;           // a bool
  auto ch = 'x';           // a char
  auto i = 123;            // an int
  auto d = 1.2;            // a double
  auto sqr_root = sqrt(d); // z has the type of whatever sqr t(y) retur ns
  cout << "auto variable:" << b << " " << ch << " " << i << " " << d << " " << sqr_root << " " << z << endl;

  auto x = 3;
  auto y = 5;
  x += y; // x = x+y
  ++x;    // increment: x = x+1
  x -= y; // x = x-y
  --x;    // decrement: x = x-1
  x *= y; // scaling: x = x*y
  x /= y; // scaling: x = x/y
  x %= y; // x = x%y
}

void data_size_test()
{
  FUNC_HEAD();
  cout << "size of datatype" << endl;
  cout << "short " << sizeof(short) << endl;
  cout << "int " << sizeof(int) << endl; //still 4 bytes as 32bit machine
  cout << "long " << sizeof(long) << endl;
  cout << "long long " << sizeof(long long) << endl;
  cout << "float " << sizeof(float) << endl;
  cout << "double " << sizeof(double) << endl;

  string b;
  cout << "address of string " << sizeof(&b) << endl
       << "string " << sizeof(b) << endl;
}

void ds_bias_test()
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
  cout << "bias " << bias << endl;

  bias = (size_t) & (((struc_t *)0)->b);
  cout << "bias " << bias << endl;
}

void exception_test()
{
  FUNC_HEAD();
  int x = 1;
  int y = 0;

  try
  {
    x /= y;
  }
  catch (exception &err)
  {
    cerr << err.what() << endl;
  }
}

//默认参数只能放在形参列表的最后
void defaultParam_test(string hi = "Hi", string name = "Alex")
{
  FUNC_HEAD();
  cout << hi << "\t" << name << endl;
}

/*
引用可以看做是数据的一个别名，通过这个别名和原来的名字都能够找到这份数据。
变量 b 就是变量 a 的引用，它们用来指代同一份数据；
也可以说变量 b 是变量 a 的另一个名字。从输出结果可以看出，a 和 b 的地址一样
*/
void reference_test()
{
  FUNC_HEAD();
  int a = 99;
  //引用必须在定义的同时初始化，并且以后也要从一而终，不能再引用其它数据
  int &b = a;
  b = 11;
  cout << "a:" << a << "\tb:" << b << endl;
  cout << "address of a:" << &a << endl
       << "address of b:" << &b << endl;
}

/*
Function Overloading。借助重载，一个函数名可以有多种用途。
*/
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
void swap(float *a, float *b)
{
  float temp = *a;
  *a = *b;
  *b = temp;
}

class B
{
public:
  int f(int i)
  {
    cout << "B::f(int): ";
    return i;
  }
  // ...
};

class D : public B
{
public:
  using B::f; // make every f from B available
  double f(double d)
  {
    cout << "D::f(double): ";
    return d;
  }
  // ...
};

void overload_test()
{
  int i1 = 1, i2 = 2;
  float f1 = 1.2, f2 = 2.1;
  cout << "before swap" << endl;
  cout << i1 << "\t" << i2 << endl;
  cout << f1 << "\t" << f2 << endl;
  swap(&i1, &i2);
  swap(&f1, &f2);
  cout << "after swap" << endl;
  cout << i1 << "\t" << i2 << endl;
  cout << f1 << "\t" << f2 << endl;

  //虽然这不能算overload,但从效果来看，也起了类似效果
  D *pd = new D;
  cout << pd->f(2) << '\n';
  cout << pd->f(2.3) << '\n';
}

int main()
{
  type_arithmetic_test();
  data_size_test();
  ds_bias_test();
  reference_test();
  defaultParam_test("Hello");
  overload_test();
  exception_test();
  return 0;
}
