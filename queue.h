
#ifndef COP4530_QUEUE_H
#define COP4530_QUEUE_H
/********************************
 * COP 4530
 * FSU Department of Computer Sience
 ********************************/

#include <iostream>
#include <list>
using namespace std;
namespace cop4530 {

template <typename T>
class Queue {
 public:
     Queue();
     ~Queue();
     Queue(const Queue & rhs);
     Queue(const Queue && rhs);
     Queue& operator=(const Queue & rhs);
     Queue& operator=(const Queue && rhs);
     T& back();
     const T& back()const;
     bool empty() const;
     T& front();
     const T& front() const;
     void pop();
     void push(const T& val);
     void push(T&&val);
     int size();
     void print();
 protected:
     list<T> container;

 };
#include "Queue.hpp"
}

 #endif
