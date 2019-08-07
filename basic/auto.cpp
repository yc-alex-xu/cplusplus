#include <iostream>
#include <string>
#include "../toolkit.h"

using namespace std;

// after c++14
template <typename T, typename U>
auto add3(T x, U y)
{
    FUNC_HEAD();
    return x + y;
}

decltype(auto) look_up_a_string_1()
{
    FUNC_HEAD();
    string s = "abc";
    return s;
}

auto look_up_a_string_2()
{
    FUNC_HEAD();
    string s = "efg";
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
}

int main()
{
    auto q = add3(1.0, 2);
    cout << "q: " << q << endl;
    cout << look_up_a_string_1() << endl;
    cout << look_up_a_string_2() << endl;

    decltype_test();
}
