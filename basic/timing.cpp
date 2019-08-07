#include <chrono>
#include <iostream>
#include "../toolkit.h"
using namespace std;
using namespace std::chrono;

void time_points_test()
{
    FUNC_HEAD();

    time_point<system_clock, seconds> tp;
    cout << "to epoch : " << tp.time_since_epoch().count() << "s" << endl;
}

int duration_test()
{
    FUNC_HEAD();

    milliseconds mscond(1000); // 1 second
    cout << "it equal to:" << endl;
    cout << mscond.count() << " milliseconds.\n";

    cout << mscond.count() * milliseconds::period::num / milliseconds::period::den;
    cout << " seconds.\n";

    ratio<60, 1> mins;
    cout << "min=" << mins.num << "/" << mins.den << endl;

    milliseconds ms(54802);
    seconds s = duration_cast<seconds>(ms);
    cout << s.count() << "seconds\n";
}



int main()
{
    auto t0 = high_resolution_clock::now();

    system_clock::period p;
    cout << "1 tick of system clock:" << p.num << "/" << p.den << "seconds" << endl;

    time_points_test();
    duration_test();

    FUNC_HEAD();
    auto t1 = high_resolution_clock::now();
    cout << "exectuion time:" << duration_cast<milliseconds>(t1 - t0).count() << "msec\n";
    return 0;
}
