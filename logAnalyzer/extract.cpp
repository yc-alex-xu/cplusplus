/*
for  gcc version 4.9.2 
only extract needed info for comparison
g++ -Wall (-DDEBUG) -static -std=c++11 -o 
*/

#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

/*
global variable
 */
ifstream fs_in;
ofstream fs_out;

/*
internal func
 */
bool startsWith(string &s, const string &sub)
{
    return s.find(sub) == 0 ? true : false;
}

bool endsWith(string &s, const string &sub)
{
    return s.rfind(sub) == (s.length() - sub.length()) ? true : false;
}



void update_progress(int lineno)
{
    static int count = 1;
    if (lineno > count * 100000)
    {
        if (count == 1)
            cerr << endl
                 << "progress:\t"; //cerr is not buffered
        cerr << "#";
        count++;
    }
}


int checklog(long &count)
{
    unsigned long lineno = 0; //without long long, the old gcc can't match stoi
    string str_se_info;
    const int MAX_SE = 50;

    for (string line; count < MAX_SE && getline(fs_in, line);)
    {
        ++lineno;
        update_progress(lineno);
        if (line.find("<!UPCUL.211!>") < string::npos)
        {
            fs_out <<lineno<<":"<<line <<endl;
        }
        else if (line.find("<!UPCUL.170!>") < string::npos)
        {
            fs_out <<lineno<<":"<<line <<endl;
        }
        else if (line.find("<!UPCUL.123!>") < string::npos)
        {
            fs_out <<lineno<<":"<<line <<endl;
        }
        else if (endsWith(line,"newTxSeData {"))
        {
            fs_out <<lineno<<":"<<line <<endl;
            count++;
            while (getline(fs_in, line))
            {
                lineno++;
                fs_out <<line <<endl;
                if (endsWith(line,"}"))
                {
                    break;
                }
            }//while
        }
        else
        {
            /* do nothing*/
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage:" << argv[0] << " [FILE] \nused for EBB log verification \ndeveloped  by Alex" << endl;
        exit(-1);
    }
    fs_in.open(argv[1]);
    if (!fs_in.good())
    {
        cerr << argv[1] << " open error!" << endl;
        exit(-2);
    }
    string fn("result.txt");
    fs_out.open(fn, ios::trunc);
    if (!fs_out.good())
    {
        cerr << fn << " open error!" << endl;
        exit(-3);
    }
    long count = 0;
    if (checklog(count) < 0)
        cout << endl
             << count << " se verified,last one not matched " << endl;
    else
        cout << endl
             << count << " se verified,all matched" << endl;
    cout << "please double check via " << fn << endl;

    fs_in.close();
    fs_out.close();
    return 0;
}
