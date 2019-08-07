#include <iostream>
#include <set>
#include <algorithm>
#include "../toolkit.h"

using namespace std;

int stl_set_test()
{
    FUNC_HEAD();
    set<int> iset;
    iset.insert(11);
    iset.insert(55);
    iset.insert(33);
    iset.insert(44);
    iset.insert(22);

    set<int>::iterator it;
    for (it = iset.begin(); it != iset.end(); it++)
    {
        cout << *it << "\t";
    }
    cout << endl;

    int i = 33;
    if (binary_search(iset.begin(), iset.end(), i))
        cout << "found " << i << endl;
    else
        cout << "can't find " << i << endl;
}

int main()
{
    stl_set_test();

    return 0;
}
