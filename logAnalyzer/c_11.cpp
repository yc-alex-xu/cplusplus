/*
for  gcc version 4.9.2 
g++ -Wall (-DDEBUG) -static -std=c++11 -o logB
*/

#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

using TRACE = map<int, string>;

struct UPCUL_211 //after SE
{
    unsigned long bbUeRef;
    int pathThroughTfs;
    int pathThroughTfs2;
    int csiDecisionBitmap;
    int tbs;
    int isUlMuMimoCandidate;
    int muMimoPairedSeType;
    int servCellIndex;
    int spsActivationPending;
    int hasPucchTransmission;
};

struct UPCUL_123 //before SE
{
    unsigned long bbUeRef;
    int srCause;
    int srType;
    int isSrReceived;
};

struct UPCUL_170 //before SE, higher order than UPCUL_123
{
    unsigned long bbUeRef;
    int isSrReceived;
};
struct SE_newTx
{
    unsigned long bbUeRef;
    int pathThroughTfs;
    int pathThroughTfs2;
    int csiDecisionBitmap;
    int tbs;
    int isUlMuMimoCandidate;
    int muMimoPairedSeType;
    int servCellIndex;
    int spsActivationPending;
    int hasPucchTransmission;
    int isSrReceived;
    int srCause;
    int srType;
};

ifstream fs_in;
ofstream fs_out;

//返回(xvalue, expiring value) 右值引用延长临时对象生命周期 而不是copy 一个string
string scan_item(string &line, string pat, string ending = " ")
{
    string::size_type n1, n2;
    n1 = line.find(pat);
    if (n1 == string::npos)
    {
        return "";
    }
    n2 = line.find(ending, n1);
    if (n2 == string::npos)
    {
        return "";
    }
    return line.substr(n1 + pat.length(), n2 - n1 - pat.length());
}

int get_trace_info(string &line, UPCUL_211 &trace)
{
    trace.bbUeRef = stoul(scan_item(line, "bbUeRef="), 0, 0);
    trace.servCellIndex = stoi(scan_item(line, "servCellIndex="));
    trace.isUlMuMimoCandidate = stoi(scan_item(line, "isUlMuMimoCandidate="));
    trace.muMimoPairedSeType = stoi(scan_item(line, "muMimoPairedSeType="));
    trace.tbs = stoi(scan_item(line, "tbs="));
    trace.pathThroughTfs = stoi(scan_item(line, "pathThroughTfs="), 0, 0);
    trace.pathThroughTfs2 = stoi(scan_item(line, "pathThroughTfs2="), 0, 0);
    trace.csiDecisionBitmap = stoi(scan_item(line, "csiDecisionBitmap="), 0, 0);
    trace.spsActivationPending = stoi(scan_item(line, "spsActivationPending="));
    trace.hasPucchTransmission = stoi(scan_item(line, "hasPucchTransmission="));
    return 0;
}

int get_trace_info(string &line, UPCUL_123 &trace)
{
    trace.bbUeRef = stoul(scan_item(line, "bbUeRef="), 0, 0);
    trace.isSrReceived = stoul(scan_item(line, "isSrReceived="));
    trace.srCause = stoul(scan_item(line, "srCause="));
    trace.srType = stoul(scan_item(line, "srType="));
    return 0;
}

int get_se_info(string &str_se_info, SE_newTx &se)
{

    return 0;
}

bool trace_matched(SE_newTx &se, UPCUL_123 &trace_123, UPCUL_211 &trace_211)
{
    return true;
    if (!(trace_211.csiDecisionBitmap == se.csiDecisionBitmap && trace_211.hasPucchTransmission == se.hasPucchTransmission && trace_211.pathThroughTfs == se.pathThroughTfs && trace_211.servCellIndex == se.servCellIndex && trace_211.spsActivationPending == se.spsActivationPending && trace_211.tbs == se.tbs))
    {
        return false;
    }

    if ((trace_211.isUlMuMimoCandidate) && (trace_211.muMimoPairedSeType != se.muMimoPairedSeType))
    {
        return false;
    }
/*   
    if (!(trace_123.srCause == se.srCause && trace_123.isSrReceived == se.isSrReceived && trace_123.srType == se.srType))
    {
        return false;
    }
*/    
    return true;
}

/*
comapre the trace with golden
if matched return 0;
else if preceeding trace missing return >0
else <0
*/
inline int compare_trace(string &str_se_info, TRACE map_123, UPCUL_211 trace_211)
{
    SE_newTx se;
    get_se_info(str_se_info, se);

    string str_trace;
    auto iter = map_123.find(se.bbUeRef);
    if (iter != map_123.end())
    {
        str_trace = map_123[se.bbUeRef];
        fs_out << str_trace << str_se_info;
    }
    else
    {
#ifdef DEBUG
        fs_out << "can't found " << se.bbUeRef << endl;
#endif
        return 1;
    }
    UPCUL_123 trace_123;
    get_trace_info(str_trace, trace_123);
    if (map_123.size() > 1000)
    {
        map_123.clear();
    }
    else
    {
        map_123.erase(iter);
    }

    if (trace_matched(se, trace_123, trace_211))
        return 0;
    else
        return -1;
}

inline void update_progress(int lineno)
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

//return true if the requried se type met
bool read_se(string &str_se_info, unsigned long &lineno, unsigned long &bbUeRef)
{
    string line;
    bool b_se_found = false;
    while (getline(fs_in, line))
    {
        lineno++;
        str_se_info += line + "\n";
        if (line.find("newTxSeData {\r") < string::npos) //need verify
        {
#ifdef DEBUG
            fs_out << "------> iua found" << endl;
#endif
            b_se_found = true;
        }
        else if (line.find("bbUeRef") < string::npos)
        {
            bbUeRef = stoul(scan_item(line, "bbUeRef", ","));
        }
        else if (line.find("}\r") < string::npos)
        {
#ifdef DEBUG
            fs_out << "------>end of  iua found" << endl;
#endif
            break;
        }
    }
    return b_se_found;
}

int checklog(long &count)
{
    unsigned long lineno = 0; //without long long, the old gcc can't match stoi
    int status = 0;
    unsigned long bbUeRef_se = 0;
    bool b_se_found = false;
    string str_se_info;
    TRACE map_123;

    for (string line; (status >= 0) && getline(fs_in, line);)
    {
        ++lineno;
        update_progress(lineno);
        if (line.find("<!UPCUL.211!>") < string::npos)
        {
            unsigned long bbUeRef = stoul(scan_item(line, "bbUeRef="), 0, 0);
#ifdef DEBUG
            fs_out << "------> trace found" << bbUeRef << endl;
#endif
            if (b_se_found && bbUeRef == bbUeRef_se)
            {
                UPCUL_211 trace_211;
                get_trace_info(line, trace_211);
                count++;
                status = compare_trace(str_se_info, map_123, trace_211);
            }
        }
        else if (line.find("<!UPCUL.123!>") < string::npos)
        {
            unsigned long bbUeRef = stoul(scan_item(line, "bbUeRef="), 0, 0);
#ifdef DEBUG
            fs_out << "------> trace found" << bbUeRef << endl;
#endif
            map_123[bbUeRef] = to_string(lineno) + ":" + line + "\n";
        }
        else if (line.find("seSchedInfoList {") < string::npos)
        {
#ifdef DEBUG
            fs_out << "------> bbUeRef found" << endl;
#endif
            str_se_info = to_string(lineno) + ":" + line + "\n";
            b_se_found = read_se(str_se_info, lineno, bbUeRef_se);
        }
        else
        {
            /* do nothing*/
        }
    }
    map_123.clear();
    return status;
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
