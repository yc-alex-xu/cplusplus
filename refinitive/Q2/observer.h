#ifndef OBSERVER_H
#define OBSERVER_H

class IObserver
{
public:
    virtual void Update(float price) = 0;
    virtual void getState(){};
};

#endif // OBSERVER_H
