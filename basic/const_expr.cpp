/*
compiler shall be above -std=c++11
 */

#include <iostream>
using namespace std;
constexpr int fibonacci(const int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

template <typename T>
auto print_type_info(const T &t)
{
    if constexpr (std ::is_integral<T>::value)  //when gdb, this statement don't existed at all
    {
        return t + 1;
    }
    else
    {
        return t + 0.001;
    }
}

int main()
{
    cout << fibonacci(5) << endl;
    cout << print_type_info(5) << endl;
    cout << print_type_info(3.14) << endl;
    return 0;
}