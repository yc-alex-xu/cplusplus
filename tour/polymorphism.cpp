#include <iostream>
#include "toolkit.h"
using namespace std;

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
  polymorphism_test();
  return 0;
}