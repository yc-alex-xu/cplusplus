#ifndef SUBJECT_H
#define SUBJECT_H

class IObserver;

class ISubject
{
public:
    virtual void Attach(IObserver *) = 0;
    virtual void Detach(IObserver *) = 0;
    virtual void Notify() = 0;
    virtual void getState(){};
};

#endif // SUBJECT_H
