#include <iostream>
#include "toolkit.h"

using namespace std;

struct human
{
    string name;

private:
    int age;
};

class man : public human
{
public:
    bool married;
};
void struct_class_test()
{
    FUNC_HEAD();
    human *h = new man();
    h->name = "John";
    man *m = (man *)h;
    m->married = false;
    cout << "name: " << m->name << " married: " << m->married << endl;
}

class Account
{
private:
    //static 成员变量属于类，不属于某个具体的对象，即使创建多个对象，也只为它分配一份内存
    static double m_rate;

public:
    //编译器在编译一个普通成员函数时，会隐式地增加一个形参 this，并把当前对象的地址赋值给 this
    //而静态成员函数可以通过类来直接调用，编译器不会为它增加形参 this，只能访问静态成员
    //它不需要当前对象的地址，所以不管有没有创建对象，都可以调用静态成员函数。
    static void set_rate(const double &x)
    {
        cout << "old rate = " << m_rate << " new rate = " << x << endl;
        m_rate = x;
    }
};
double Account::m_rate = 8.0;

void static_test()
{
    FUNC_HEAD();
    //static方法，不需要实例化即可调用
    Account::set_rate(5.0);
    Account a;
    a.set_rate(7.0);
}

/*
 class a --> class b --> class c

*/

class a
{
public:
    //在C++中，有一种特殊的成员函数，它的名字和类名相同，没有返回值，不需要用户显式调用（用户也不能调用），
    //而是在创建对象时自动执行。这种特殊的成员函数就是构造函数（Constructor）。
    a() { cout << "Constructor a" << endl; }
    virtual void disp() { cout << "a::disp()" << endl; }
    //析构函数 Destructor 也是一种特殊的成员函数，没有返回值，不需要程序员显式调用（
    virtual ~a() { cout << "Destructor ~a" << endl; }
};

class b : public a
{
public:
    b() { cout << "Constructor b" << endl; }
    ~b() { cout << "Destructor ~b" << endl; }
};

class c : public b
{
public:
    c() { cout << "Constructor c" << endl; }
    void disp() { cout << "c::disp()" << endl; }
    ~c() { cout << "Destructor ~c" << endl; }
};

/* 
check the sequence of construction/deconstruction
and virtual function
*/
void virtual_test()
{
    FUNC_HEAD();
    a *p = new c();
    cout << "call virtual function via object pointer" << endl;
    p->disp();
    delete p; //must free explicitly
}

class Empty
{
};

void f()
{
    Empty a, b;
    if (&a == &b)
        cout << "impossible: report error to compiler supplier";

    Empty *p1 = new Empty;
    Empty *p2 = new Empty;
    if (p1 == p2)
        cout << "impossible: report error to compiler supplier";
}

struct X : Empty
{
    int a;
    // ...
};

void f(X *p)
{
    void *p1 = p;
    void *p2 = &p->a;
    if (p1 == p2)
        cout << "nice: good optimizer\n";
}



/******
 * 
http://www.stroustrup.com/bstechfaq.htm
*/

void empty_class_test()
{
    FUNC_HEAD();
    f();
    struct X b;
    f(&b);
}

class Stack_r
{
private:
    int *mpstack;
    int mtop;
    int msize;

public:
    Stack_r(int size = 1000) : msize(size), mtop(0)
    {
        cout << "construction " << endl;
        mpstack = new int[size];
    }
    ~Stack_r()
    {
        cout << "deconstruction" << endl;
        delete[] mpstack;
        mpstack = nullptr;
    }

    Stack_r(const Stack_r &src) : msize(src.msize), mtop(src.mtop)
    {
        cout << "copy construction " << endl;
        mpstack = new int[src.msize];
        for (int i = 0; i < mtop; ++i)
        {
            mpstack[i] = src.mpstack[i];
        }
    }
    Stack_r(Stack_r &&src) : msize(src.msize), mtop(src.mtop)
    {
        cout << "copy construction with rvalue" << endl;

        /*此处没有重新开辟内存拷贝数据，把src的资源直接给当前对象，再把src置空*/
        mpstack = src.mpstack;
        src.mpstack = nullptr;
    }

    // 带右值引用参数的赋值运算符重载函数
    Stack_r &operator=(Stack_r &&src)
    {
        cout << "operator=(Stack_r &&)" << endl;

        if (this == &src)
            return *this;

        delete[] mpstack;

        msize = src.msize;
        mtop = src.mtop;

        /*此处没有重新开辟内存拷贝数据，把src的资源直接给当前对象，再把src置空*/
        mpstack = src.mpstack;
        src.mpstack = nullptr;

        return *this;
    }

    // 赋值重载
    Stack_r &operator=(const Stack_r &src)
    {
        cout << "operator=" << endl;
        if (this == &src)
            return *this;

        delete[] mpstack;

        msize = src.msize;
        mtop = src.mtop;
        mpstack = new int[src.msize];
        for (int i = 0; i < mtop; ++i)
        {
            mpstack[i] = src.mpstack[i];
        }
        return *this;
    }

    void print() &
    {
        cout << "called by lvalue reference" << endl;
    }
    void print() &&
    {
        cout << "called by rvalue reference" << endl;
    }

    int getSize()
    {
        return msize;
    }
};

Stack_r GetStack(Stack_r &s)
{
    Stack_r tmp(s.getSize());
    return tmp;
}

/*
about rvalue ,please refer rvalue.cpp
here mainly test polymorphism
*/
void polymorphism_test()
{
    FUNC_HEAD();
    Stack_r s1;
    s1.print();
    GetStack(s1).print();
    //程序自动调用了带右值引用的拷贝构造函数和赋值运算符重载函数，
    //使得程序的效率得到了很大的提升，因为并没有重新开辟内存拷贝数据。
    s1 = GetStack(s1);
}

int main()
{
    struct_class_test();
    static_test();
    virtual_test();
    empty_class_test();
    return 0;
}
