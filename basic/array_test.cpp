//$ g++ array_test.cpp

#include <array>
#include <iostream>
#include "../toolkit.h"
using namespace std;

template <typename T, size_t N>
void print_array(array<T, N> &arr)
{
    FUNC_HEAD();
    for (auto x : arr)
        cout << x << endl;
}

void print_array_2()
{
    int arr[4];
    FUNC_HEAD();

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        arr[i] = i * i;
    }

    for (auto &v : arr)
    {
        cout << v << '\t';
    }
    cout << endl;
}

int main()
{
    array<int, 3> arr1{1, 2, 3};
    array<int, 3> arr2 = {4, 5}; //run result: 4/5/0
    print_array(arr1);
    cout << endl;

    print_array(arr2);
    cout << endl;

    print_array_2();

    return 0;
}
