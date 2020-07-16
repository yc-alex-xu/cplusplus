/*
demo of the operator override
*/
#include <iostream>
#include "toolkit.h"
using namespace std;
struct USCurrency
{
  int dollars;
  int cents;
  USCurrency operator+(const USCurrency c)
  {
    this->cents += c.cents;
    this->dollars += c.dollars;
    if (this->cents >= 100)
    {
      this->cents -= 100;
      this->dollars++;
    }
    return *this;
  }
};

ostream &operator<<(ostream &out, const USCurrency &c)
{
  out << "$" << c.dollars << "." << c.cents;
  return out;
}

/*
override the operator  +， <<
 */
int operator_test()
{
  FUNC_HEAD();
  USCurrency a = {2, 50};
  USCurrency b = {1, 75};
  USCurrency c = a + b;
  cout << c << endl;
  return 0;
}

int main()
{
  operator_test();
  return 0;
}