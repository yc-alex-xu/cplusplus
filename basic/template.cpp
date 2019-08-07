#include <iostream>
#include "../toolkit.h"
using namespace std;

/****
 * swap_test()
 * 
 *
 */

template <typename T>
void myswap(T &a, T &b)
{
  a += b;
  b = a - b;
  a -= b;
}
void swap_test()
{
  FUNC_HEAD();
  double a = -2.0;
  double b = 3.0;
  cout << "before swap:" << a << "\t" << b << endl;
  myswap(a, b);
  cout << "after  swap:" << a << "\t" << b << endl;
}

/***
 * 
 * params_test()
 */
template <typename T, typename U>
U sum(const T a, const U b)
{
  return a + b;
}
template <typename... T>
auto sum(T... t)
{
  return (t + ...);
}

template <typename T0, typename... T>
void printf(T0 t0, T... t)
{
  cout << t0 << endl;
  if constexpr (sizeof...(t) > 0)
    printf(t...);
}

template <typename... Args>
void magic(Args... args)
{
  cout << sizeof...(args) << endl;
}

void params_test()
{
  FUNC_HEAD();
  cout << "sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)=" << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << endl;
  cout << "ouput of func printf():" << endl;
  printf(1);
  printf(2.0, 3.0);
  printf('4', '5', '6');
  cout << "ouput of func magic():" << endl;
  magic();      // 输出0
  magic(1);     // 输出1
  magic(1, ""); // 输出2
}

/****
 * 
 */

template <typename T = int, int n = 5>
class container
{
private:
  T arr[n];

public:
  void set(int i, T val) { arr[i] = val; }
  T get(int i) { return arr[i]; }
};

void class_template_test()
{
  FUNC_HEAD();
  container<float, 10> cc;
  cc.set(0, 1.1);
  cc.set(1, 2.2);
  cc.set(2, 3.3);
  cout << cc.get(0) << "\t" << cc.get(1) << "\t" << cc.get(2) << endl;
}

int main()
{
  swap_test();
  params_test();
  class_template_test();
  return 0;
}