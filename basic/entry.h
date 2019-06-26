#ifndef ENTRY_H
#define ENTRY_H

using namespace std;

struct Entry
{
    string name;
    int number;
    inline bool operator==(const Entry &e) const
    {
        return (this->name == e.name);
    }
};

// 不能定义为method
ostream &operator<<(ostream &os, const Entry &e)
{
    return os << "{\"" << e.name << "\", " << e.number << "}";
}

inline bool operator<(const Entry &x, const Entry &y)
{
    return x.name < y.name; // order Entrys by their names
}

#endif