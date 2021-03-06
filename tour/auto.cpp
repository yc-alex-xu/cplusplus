#include <iostream>
#include <string>
#include "toolkit.h"

using namespace std;

// after c++14
template <typename T, typename U>
auto add3(T x, U y)
{
    return x + y;
}

void auto_test()
{
    FUNC_HEAD();
    cout << "add3(1.0, 2) return " << add3(1.0, 2) << endl;
    cout << "add3(1.1, 2.2) return " << add3(1.1, 2.2) << endl;
}

decltype(auto) look_up_a_string()
{
    string s = "abc";
    return s;
}

int decltype_test()
{
    FUNC_HEAD();
    auto x = 1;
    auto y = 2;
    decltype(x + y) z;

    if (is_same<decltype(x), int>::value)
        cout << " type x == int " << endl;
    if (is_same<decltype(x), float>::value)
        cout << " type x == float " << endl;
    if (is_same<decltype(x), decltype(z)>::value)
        cout << " type z == type x" << endl;
    auto s = look_up_a_string();
    if (is_same<decltype(s), string>::value)
        cout << " type s == string " << endl;
}

int main()
{
    auto_test();
    decltype_test();
}
