# Makefile 
it applied to  3 sub folders(Questions)  
make -f ../Makefile 
#  Q1  
focused on protocol/message desgin
## main program  
server.c  
client.c  
based on https://www.geeksforgeeks.org/socket-programming-cc/
## lib
message.h also serve as lib for simplicity  
## note
"The code must ensure that both server and client sides receive the entire message size from users"  
assuming it mean: the tcp packe is stream, not datagram, so may need read several. Coding such way in server side.

#  Q2

It use the design pattern:  observer  
sequence diagram are availble:  https://en.wikipedia.org/wiki/Observer_pattern  
due to network issue, I can't download the JDK need for PlantUML sw, so can't generate the pic

base on my old code: https://github.com/justwawre/DesignPatterns
* add  method  getState() in class ISubject  
* add  new class class Subscriber : public ConcreteObserver  

# Q3
## data structure & its function, 
link.h: doubly linked list
link2.h: doubly linked list
for the doubly linked list, param linkedList can any valid postion,  not restricted to list head  
for the singly linked list, param linkedList is  restricted to list head  
##  test code 
test_doubly.c  
test_singly.c  




