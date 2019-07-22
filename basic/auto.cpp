#include <iostream>
#include <string>
using namespace std;

// after c++14
template <typename T, typename U>
auto add3(T x, U y)
{
    return x + y;
}

decltype(auto) look_up_a_string_1()
{
    string s = "abc";
    return s;
}

auto look_up_a_string_2()
{
    string s = "efg";
    return s;
}
int main()
{
    auto q = add3(1.0, 2);
    cout << "q: " << q << endl;
    cout << look_up_a_string_1() << endl;
    cout << look_up_a_string_2() << endl;
}
