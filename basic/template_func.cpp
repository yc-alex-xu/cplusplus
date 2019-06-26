#include <iostream>
#include "../toolkit.h"
using namespace std;

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
/*  much much better than macro  */
template <typename T>
T min_alex(const T a, const T b)
{
  return (a < b ? a : b);
}

template <typename T = int, int n = 5>
class container
{
private:
  T arr[n];

public:
  void set(int i, T val) { arr[i] = val; }
  T get(int i) { return arr[i]; }
};

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

template <typename... Args>
void magic(Args... args)
{
  cout << sizeof...(args) << endl;
}

template <typename T0, typename... T>
void printf(T0 t0, T... t)
{
  cout << t0 << endl;
  if constexpr (sizeof...(t) > 0)
    printf(t...);
}

int main()
{
  swap_test();
  int a = 3, b = 4;
  int c = min_alex(a++, b++);
  cout << c << endl;

  int x = 3;
  float y = 4.0;
  cout << sum(x, y) << endl;

  container<float, 10> cc;
  cc.set(0, 2.3);
  cout << cc.get(0) << endl;

  cout << "ouput of func magic():" << endl;
  magic();      // 输出0
  magic(1);     // 输出1
  magic(1, ""); // 输出2
  cout << "ouput of func printf():" << endl;
  printf(1);
  printf(2.0, 3.0);
  printf('4', '5', '6');
  cout << "ouput of func sum():" << endl;
  cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << endl;
  return 0;
}