/* 
to demo usage of string 
g++ -g 
*/
#include <iostream>
#include <string>
#include "../toolkit.h"

/*
For basic use, consider the concept Regular. A type is regular when it behaves much like an int
or a vector. An object of a regular type
• can be default constructed.
• can be copied (with the usual semantics of copy yielding two objects that are independent
and compare equal) using a constructor or an assignment.
• can be compared using == and !=.
• doesn’t suffer technical problems from overly clever programming tricks.

A string is another example of a regular type. Like int, string is also Ordered. That is, two strings
can be compared using <, <=, >, and >= with the appropriate semantics. Concepts is not just a syntactic
notion, it is fundamentally about semantics. For example, don’t define + to divide; that would
not match the requirements for any reasonable number.

*/

/*
  plan to add some string related tests
*/

void test_to_string()
{
  FUNC_HEAD();
  double f = 23.43;
  double f2 = 1e-9;
  double f3 = 1e40;
  double f4 = 1e-40;
  double f5 = 123456789;
  std::string f_str = std::to_string(f);
  std::string f_str2 = std::to_string(f2); // Note: returns "0.000000"
  std::string f_str3 = std::to_string(f3); // Note: Does not return "1e+40".
  std::string f_str4 = std::to_string(f4); // Note: returns "0.000000"
  std::string f_str5 = std::to_string(f5);
  std::cout << "std::cout: " << f << '\n'
            << "to_string: " << f_str << "\n\n"
            << "std::cout: " << f2 << '\n'
            << "to_string: " << f_str2 << "\n\n"
            << "std::cout: " << f3 << '\n'
            << "to_string: " << f_str3 << "\n\n"
            << "std::cout: " << f4 << '\n'
            << "to_string: " << f_str4 << "\n\n"
            << "std::cout: " << f5 << '\n'
            << "to_string: " << f_str5 << '\n';
}

main()
{

  test_to_string();
}
