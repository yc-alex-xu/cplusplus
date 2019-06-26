#include <initializer_list>
#include <iostream>
#include <vector>
class MagicFoo
{
public:
    std ::vector<int> vec;
    MagicFoo(std ::initializer_list<int> list)
    {
        for (auto it = list.begin();
             it != list.end(); ++it)
            vec.push_back(*it);
    }
    void append(std ::initializer_list<int> list)
    {
        for (auto it = list.begin();
             it != list.end(); ++it)
            vec.push_back(*it);
    }
};
int main()
{
    // after C ++11
    MagicFoo magicFoo = {1, 2, 3, 4, 5};

    magicFoo.append({6, 7, 8, 9});

    std ::cout << " magicFoo : " << std::endl;
    for (auto it = magicFoo.vec.begin(); it != magicFoo.vec.end(); ++it)
        std ::cout << *it << std ::endl;
}