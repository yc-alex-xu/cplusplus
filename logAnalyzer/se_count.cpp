/*
g++ -Wall -static -std=c++11 -o se_count.exe
*/
#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;

using MAP = map<int, int>;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const map<T1, T2> &m)
{
    for (const auto &v : m)
        os << "\t" << v.first << "\t" << v.second << endl;
    return os;
}

//return xvalue(expiring value), not a copy
string scan_item(string &line, string pat)
{
    string::size_type n1;
    n1 = line.find(pat);
    if (n1 == string::npos)
    {
        return "";
    }
    return line.substr(n1 + pat.length()); //till end of line
}

void checklog(ifstream &fs_in)
{
    unsigned long lineno = 0;
    bool b_UpcDlMacCeFiUlValidationInfoInd = false;
    MAP count_UpcDlMacCeFiUlValidationInfoInd;
    MAP count_validation_passed;
    MAP count_validation_failed;
    bool b_UpcDlMacCeFiUlSchedInfoInd = false;
    MAP count_UpcDlMacCeFiUlSchedInfoInd;
    MAP count_newTxSeData;
    MAP count_nonAdaptReTxSeData;
    MAP count_adaptReTxSeData;

    int cellId;

    for (string line; getline(fs_in, line);)
    {
        ++lineno;

        if (line.find("UpcDlMacCeFiUlValidationInfoInd") < string::npos)
        {
            b_UpcDlMacCeFiUlValidationInfoInd = true;
        }
        else if (line.find("UpcDlMacCeFiUlSchedInfoInd") < string::npos)
        {
            b_UpcDlMacCeFiUlSchedInfoInd = true;
        }
        else if (line.find("cellId:") < string::npos)
        {
            cellId = stoi(scan_item(line, "cellId:"));
            if (b_UpcDlMacCeFiUlValidationInfoInd)
            {
                count_UpcDlMacCeFiUlValidationInfoInd[cellId]++;
                b_UpcDlMacCeFiUlValidationInfoInd = false;
            }
            else if (b_UpcDlMacCeFiUlSchedInfoInd)
            {
                count_UpcDlMacCeFiUlSchedInfoInd[cellId]++;
                b_UpcDlMacCeFiUlSchedInfoInd = false;
            }
            else
            {
                cerr << "lineno\t" << lineno << endl
                     << "cellId:"
                     << "  appeared in unexpected place" << endl;
                exit(-3);
            }
        }
        else if (line.find("newTxSeData") < string::npos)
        {
            count_newTxSeData[cellId]++;
        }
        else if (line.find("nonAdaptReTxSeData {") < string::npos)
        {
            count_nonAdaptReTxSeData[cellId]++;
        }
        else if (line.find("adaptReTxSeData") < string::npos)
        {
            count_adaptReTxSeData[cellId]++;
        }
        else if (line.find("validResultBitmap:") < string::npos)
        {
            if (stoi(scan_item(line, "validResultBitmap:")) >= 256)
                count_validation_passed[cellId]++;
            else
                count_validation_failed[cellId]++;
        }
        else
        {
            /* do nothing*/
        }
    } //for

    cout << endl
         << "UpcDlMacCeFiUlSchedInfoInd \t" << endl
         << count_UpcDlMacCeFiUlSchedInfoInd << endl
         << "se scheduled\t" << endl
         << "\tnewTxSeData\n"
         << count_newTxSeData << endl
         << "\tnonAdaptReTxSeData\n"
         << count_nonAdaptReTxSeData << endl
         << "\tadaptReTxSeData\n"
         << count_adaptReTxSeData << endl
         << "UpcDlMacCeFiUlValidationInfoInd\t" << endl
         << count_UpcDlMacCeFiUlValidationInfoInd << endl
         << "se validated\t" << endl
         << "\tvalidation_passed validResultBitmap>=256\n"
         << count_validation_passed << endl
         << "\tvalidation_failed\n"
         << count_validation_failed << endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage:" << argv[0] << " [dec file]" << endl
             << "used for statistics for UpcDlMacCeFiUlValidationInfoInd & UpcDlMacCeFiUlSchedInfoInd only" << endl
             << "developed  by Alex" << endl;
        exit(-1);
    }
    ifstream fs_in(argv[1]);
    if (!fs_in)
    {
        cerr << argv[1] << " open error!" << endl;
        exit(-2);
    }
    checklog(fs_in);
    fs_in.close();
    return 0;
}
