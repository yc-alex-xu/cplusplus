#include "concrete_observer.h"
#include "concrete_subject.h"

int main()
{
  ConcreteSubject *pSubject = new ConcreteSubject();
  IObserver *pObserver1 = new ConcreteObserver("Jack Ma");
  IObserver *pObserver2 = new ConcreteObserver("Pony");

  pSubject->Attach(pObserver1);
  pSubject->Attach(pObserver2);

  pSubject->SetPrice(12.5);
  pSubject->Notify();

  pSubject->Detach(pObserver2);
  pSubject->SetPrice(15.0);
  pSubject->Notify();

  //add another interest for subscribe
  ConcreteSubject *pSubject2 = new ConcreteSubject();
  IObserver *pBlack = new Subscriber("192.168.1.100", "Black stone");
  IObserver *pWhite = new Subscriber("192.168.100.2", "White stone");
  pSubject2->Attach(pBlack); // 2 subscriber want receiving the interests
  pSubject2->Attach(pWhite);

  pSubject2->getState();

  pSubject2->SetPrice(88);
  pSubject2->Notify(); //2 subscriber will recived the notificaton

  pSubject2->Detach(pBlack); // 1 subscriber stop receiving the interests
  pSubject2->SetPrice(99);
  pSubject2->Notify(); //only 1 subscriber will recived the notificaton
  pSubject2->getState();

  return 0;
}
