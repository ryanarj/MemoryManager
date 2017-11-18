#ifndef __DLLIST__
#define __DLLIST__

#include <iostream>
#include <cassert>
#include "dlNode.h"

template <class T>
class dlList {
 public:
  dlList(T headerData = T(), T trailerData = T() );
  bool empty();
  void insertAfter(dlNode<T> *current, T newval);
  void insertBefore(dlNode<T> *current, T newval);
  void deleteNext(dlNode<T> *q);
  ~dlList();
  void deletePrevious(dlNode<T> *q);
  void deleteNode(dlNode<T> *q);
  void print(const char *sep);
  dlNode<T> *header;
  dlNode<T> *trailer;
};

template <class T>
bool dlList<T>::empty()
{
  return header->next == trailer;
}
    
template <class T>
dlList<T>::~dlList()
{
  while(header->next != trailer) {
    dlNode<T> *hold = header->next;
    header->next = hold->next;    
    delete hold;
  }
  delete header;
  delete trailer;

}

template <class T>
dlList<T>:: dlList(T headerData, T trailerData)
{
  header = new (std::nothrow) dlNode<T>(headerData);
  trailer = new(std::nothrow) dlNode<T>(trailerData);
  trailer->prev = header;
  header->next = trailer;
}

template <class T>
void dlList<T>::print(const char *sep)
{
  assert(header != nullptr && header->next != nullptr);
  if(header->next == trailer) {
    std::cout << "Empty list" << std::endl;
    return;
  } 
  dlNode<T> *cursor = header->next;
  
  while(cursor->next != trailer) {
    std::cout << cursor->info << sep;
    cursor = cursor->next;
  }
  std::cout << cursor->info << std::endl;
}

template <class T>
void dlList<T>::insertAfter(dlNode<T> *current, T newval)
{
  assert(current != trailer);
  current->next = new dlNode<T>(newval, current, current->next);
  current = current->next;
  current->next->prev = current;
}

template <class T>
void dlList<T>::insertBefore(dlNode<T> *current, T newval)
{
    assert(current != header);
    insertAfter(current->prev,newval);
}

template <class T>
void dlList<T>::deleteNext(dlNode<T> *current)
{
  assert(current != trailer && current->next != trailer);
  dlNode<T> *hold = current->next;
  current->next = hold->next;
  if (current->next != nullptr)
    current->next->prev = current;
  delete hold;
}

template <class T>
void dlList<T>::deletePrevious(dlNode<T> *current)
{
  assert(current != header && current->prev != header);
  dlNode<T> *hold = current->prev;
  current->prev = hold->prev;
  current->prev->next = current;
  delete hold;
}

template <class T>
void dlList<T>::deleteNode(dlNode<T>* current)
{
  assert(current != header && current != trailer);
  
  dlNode<T> *hold = current;
  current->prev->next = current->next;
  current->next->prev = current->prev;
  delete hold;
}


#endif
