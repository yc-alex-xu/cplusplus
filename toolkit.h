#ifndef TOOLKIT_H
#define TOOLKIT_H
#define FUNC_HEAD() cout << "-----------" << __FILE__ << "::" << __func__ << "-----------" << endl
#define LINE_NO() cout << __LINE__ << ":"


void update_progress_tobe(unsigned long lineno )
{
    static unsigned int count = 1;
    char spin[]="|/-\\";
    if (lineno > count * 10000000)
    {
        if (count == 1)
            cout << endl
                 << "progress: "; //cerr is not buffered
        cout << '\b' << spin[count%4];
        count++;
    }
}

#endif