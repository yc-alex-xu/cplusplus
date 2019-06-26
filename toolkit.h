#ifndef TOOLKIT_H
#define TOOLKIT_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

#define FUNC_HEAD() cout << "-----------" << __FILE__ << "::" << __func__ << "-----------" << endl
#define LINE_NO() cout << __LINE__ << ":"
template <typename Target = string, typename Source = string>
Target to(Source arg, int radix = 10) // convert Source to Target
{
    stringstream interpreter;
    Target result;
    bool status;
    switch (radix)
    {
    case 16:
        status = !(interpreter << hex << arg);
        break;
    case 8:
        status = !(interpreter << oct << arg);
        break;
    default:
        status = !(interpreter << arg);
        break;
    }

    if (status || !(interpreter >> result) | !(interpreter >> std::ws).eof()) // stuff left in stream?
        throw runtime_error{"to<>() failed"};
    return result;
}

#endif