#include <array>
#include <algorithm>
#include <iostream>
#include "toolkit.h"
using namespace std;

template <typename T, size_t N>
void print_array(array<T, N> &arr)
{
    for (auto x : arr)
        cout << x << endl;
}

void range_test()
{
    FUNC_HEAD();
    array<int, 3> arr = {4, 5}; //run result: 4/5/0
    cout << "the array is:" << endl;
    print_array(arr);
    cout << endl;
}

template <typename T, typename U>
void print_array2(T *p, U len)
{
    for (int i = 0; i < len; i++)
        cout << *p++ << endl;
}

void sort_test()
{
    FUNC_HEAD();
    constexpr int len = 4;
    array<int, len> arr = {9, 8, 7, 6};

    sort(arr.begin(), arr.end(), [](int a, int b) { return a < b; });
    cout << "the array after sort is:" << endl;
    print_array2(arr.data(), arr.size());
}

int main()
{
    range_test();
    sort_test();
    return 0;
}
