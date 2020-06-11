#include <iostream>
#include <unordered_map>
#include <map>
#include "toolkit.h"
using namespace std;

void map_test()
{
    FUNC_HEAD();
    // 两组结构按同样的顺序初始化
    unordered_map<int, string> um = {
        {1, "1"},
        {3, "3"},
        {2, "2"}};
    map<int, string> m = {{1, "1"}, {3, "3"}, {2, "2"}};

    // 分别对两组结构进行遍历
    cout << "  unordered_map " << endl;
    for (const auto &v : um)
        cout << "Key :[" << v.first << "] Value :[" << v.second << "]\n";
    cout << endl;

    /*
    由于Map是采用的是红黑树实现的二叉查找树，成员插入自然是有序的
    */
    cout << "  map " << endl;
    for (const auto &v : m)
        cout << "Key :[" << v.first << "] Value :[" << v.second << "]\n";
}

int main()
{
    map_test();
    return 0;
}