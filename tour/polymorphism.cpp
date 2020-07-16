#include <iostream>
#include "toolkit.h"
using namespace std;

class Stack
{
private:
  int *mpstack;
  int mtop;
  int msize;

public:
  Stack(int size = 1000) : msize(size), mtop(0)
  {
    cout << "Constructor " << endl;
    mpstack = new int[size];
  }
  ~Stack()
  {
    cout << "Destructor" << endl;
    delete[] mpstack;
    mpstack = nullptr;
  }

  Stack(const Stack &src) : msize(src.msize), mtop(src.mtop)
  {
    cout << "copy Constructor " << endl;
    mpstack = new int[src.msize];
    for (int i = 0; i < mtop; ++i)
    {
      mpstack[i] = src.mpstack[i];
    }
  }
  Stack(Stack &&src) : msize(src.msize), mtop(src.mtop)
  {
    cout << "move Constructor" << endl;
    mpstack = src.mpstack;
    src.mpstack = nullptr;
  }

  // move assignment
  Stack &operator=(Stack &&src)
  {
    cout << "operator=(Stack &&)" << endl;

    if (this == &src)
      return *this;

    delete[] mpstack;

    msize = src.msize;
    mtop = src.mtop;
    mpstack = src.mpstack;
    src.mpstack = nullptr;

    return *this;
  }

  // copy assignment
  Stack &operator=(const Stack &src)
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

Stack GetStack(Stack &s)
{
  Stack tmp(s.getSize());
  return tmp;
}

/*
about rvalue ,please refer rvalue.cpp
here mainly test polymorphism
*/
void polymorphism_test()
{
  FUNC_HEAD();
  Stack s1;
  s1.print();
  GetStack(s1).print();
  //程序自动调用了带右值引用的拷贝构造函数和赋值运算符重载函数，
  //使得程序的效率得到了很大的提升，因为并没有重新开辟内存拷贝数据。
  s1 = GetStack(s1);
}

int main()
{
  polymorphism_test();
  return 0;
}