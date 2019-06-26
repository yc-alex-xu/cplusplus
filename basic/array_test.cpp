//$ g++ array_test.cpp

#include <array>
#include <iostream>
#include "../toolkit.h"
using namespace std;

template <typename T, size_t N>
void print_array(array<T, N> &arr)
{
    for (auto x : arr)
        cout << x << endl;
}

int main()
{
    array<int, 3> arr1{1, 2, 3};
    array<int, 3> arr2 = {4, 5};
    print_array(arr1);
    cout << endl;

    print_array(arr2);
    cout << endl;

    return 0;
}
