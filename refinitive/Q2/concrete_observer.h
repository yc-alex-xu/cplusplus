#ifndef CONCRETE_OBSERVER_H
#define CONCRETE_OBSERVER_H

#include "observer.h"
#include <iostream>
#include <string>

using namespace std;

class ConcreteObserver : public IObserver
{
public:
    ConcreteObserver(string name) { m_str = name; }

    void Update(float price)
    {
        cout << m_str << " - price: " << price << endl;
    }

protected:
    string m_str;
};

class Subscriber : public ConcreteObserver
{
public:
    Subscriber(string ip, string name) : ConcreteObserver(name)
    {
        this->ip = ip;
        conncted = true;
    }
    void Update(float price)
    {
        cout << " - price: " << price << " will send to:" << m_str << " via ip " << ip << endl;
        //pseudo code, if no reponse received, change state
        conncted = false;
    }
    void getState()
    {
        cout << m_str << " connected : " << boolalpha << conncted << endl;
    }

protected:
    string ip;
    bool conncted;
};

#endif // CONCRETE_OBSERVER_H
