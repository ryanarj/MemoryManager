#ifndef __DLNODE__
#define __DLNODE__

#include <iostream>
#include <cassert>

template <class T>
class dlNode {
 public:
  T info;
  dlNode<T> *prev;
  dlNode<T> *next;
  dlNode<T>(T val, dlNode<T> *p = nullptr, dlNode<T> *n = nullptr) : info(val),
    prev(p), next(n) {}
};


#endif
