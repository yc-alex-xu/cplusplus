#include <complex>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <exception>
#include "../toolkit.h"

using namespace std;

class Account
{
private:
    static double m_rate;

public:
    double get_rate() { return m_rate; }
    static void set_rate(const double &x)
    {
        m_rate = x;
        cout << "new rate = " << x << endl;
    }
};
double Account::m_rate = 8.0;

void static_method_field()
{
    FUNC_HEAD();
    Account a;
    Account::set_rate(5.0);
    a.set_rate(7.0);
    cout << "at last,rate was set as " << a.get_rate() << endl;
}

class a
{
public:
    a() { cout << "a" << endl; }
    virtual void disp() { cout << "a disp" << endl; }
    virtual ~a() { cout << "~a" << endl; }
};

class b : public a
{
public:
    b() { cout << "b" << endl; }
    ~b() { cout << "~b" << endl; }
};

class c : public b
{
public:
    c() { cout << "c" << endl; }
    void disp() { cout << "c:disp" << endl; }
    ~c() { cout << "~c" << endl; }
};

/* check the order of construction/deconstruction
*/
int virtual_test()
{
    FUNC_HEAD();
    a *p = new c();
    p->disp();
    delete p;
    return 0;
}

int main()
{
    static_method_field();
    virtual_test();
    return 0;
}
