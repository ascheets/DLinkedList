#pragma once
#include <iostream>
#include <stdlib.h>
#include "../logging/Log.h"

using namespace std;

template <class T>
class DLL
{
 public:
  DLL();
  DLL(Log* someLog);
  ~DLL();

  void insertAtFront(const T& elem);
  void insertAtRear(const T& elem);
  
  bool removeFromFront(T& elem);
  bool removeFromRear(T& elem);
 
  bool first(T& elem);
  bool next(T& elem);
  bool last(T& elem);
  bool previous(T& elem);
  
  int size();
  bool isEmpty();
  void setLog(Log* someLog);
  void printAllFromTail();
  void printAllFromHead();

 private:

  //create node structure
  struct Node
  {
    T data;
    //pointer to previous node, closer to head
    Node* p_prev;
    //pointer to next node, closer to tail
    Node* p_next;
  };

  Node* p_head;
  Node* p_tail;
  Node* p_current;
  int numElements;

  Log* p_log;
  
};

//DLL constructor
template <class T>
DLL <T> :: DLL()
{  
  //what should happen when DLL is initialized?
   //set head to zero
  p_head = 0;
  //set current node to zero
  p_current = 0;
  //since there are no elements in this list yet
  numElements = 0;
      
}

//DLL constructor with log
template <class T>
DLL <T> :: DLL(Log* someLog)
{
  //initialize Log
  p_log = someLog;
  
  p_log->info("Inside DLL constructor");

  //what should happen when DLL is initialized?
 
  //set head to zero
  p_head = 0;
  //set current node to zero
  p_current = 0;
  //since there are no elements in this list yet
  numElements = 0;
 
  //let log know
  p_log->info("DLL initialized");
}

//DLL destructor
template <class T>
DLL <T> :: ~DLL()
{
  //temp node helper pointer
  Node* p_temp;

  //while the list is not empty
  while(!isEmpty()){

    //set pointer to head node
    p_temp = p_head;

    //move the head one towards tail
    p_head = p_head->p_next;

    //delete the current p_head
    delete p_temp;

    //increment numElements
    numElements--;
  }

  //log the object's destruction
  p_log->info("Object has been destroyed, allocated space freed");

}

//insertAtFront
template <class T>
void DLL <T> :: insertAtFront(const T& elem)
{
  //create new node on the heap
  Node* newNode = new Node;

  //set date for new node
  newNode->data = elem;

  //if the list is empty
  if(isEmpty()){

    //set newNode values
    newNode->p_next = 0;
    newNode->p_prev = 0;

    //update dll values
    p_head = newNode;
    p_tail = newNode;
    p_current = newNode;

    //anything else?

  }
  //if the list is not empty
  else{
    
    //set node(s) values
    p_head->p_prev = newNode;
    newNode->p_prev = 0;
    newNode->p_next = p_head;

    //update dll values
    p_head = newNode;

    //anything else?
  }

  //increase numElements
  numElements++;
} 

//insertAtRear
template <class T>
void DLL <T> :: insertAtRear(const T& elem)
{
  //create a new node
  Node* newNode = new Node;
  
  //set data for new node
  newNode->data = elem;

  //if the list is empty
  if(isEmpty()){
    
    //set node members
    newNode->p_prev = 0;
    newNode->p_next = 0;

    //update list members
    p_head = newNode;
    p_tail = newNode;

  }
  //if the list is not empty
  else{
    
    //consider what it means to insert at end
    
    //set node members
    newNode->p_prev = p_tail;
    newNode->p_next = 0;
    p_tail->p_next = newNode;

    //update list members
    p_tail = newNode;

  }

  //update numElements
  numElements++;

}

//removeFromFront
template <class T>
bool DLL <T> :: removeFromFront(T& elem)
{
  //if the list is not empty
  if(!isEmpty()){

    //create a temporary node pointer
    Node* p_nodeTemp = p_head;

    //set ref element to data at p_head
    elem = p_head->data;

    //delete p_head object from heap
    delete p_head;

    //update p_head
    p_head = p_nodeTemp->p_next;

    //update numElements
    numElements--;
  }
  //if the list is empty
  else{
    p_log->warning("Trying to remove from empty list");
  }
}

//removeFromRear
template <class T>
bool DLL <T> :: removeFromRear(T& elem)
{
  //if the list is not empty
  if(!isEmpty()){
    
    //create a temporary node pointer
    Node* p_nodeTemp = p_tail;

    //set ref element to p_tail data
    elem = p_tail->data;
  
    //delete p_tail object from heap
    delete p_tail;

    //update p_tail
    p_tail = p_nodeTemp->p_prev;

    //update numElements
    numElements--;
  }
  //if the list is empty
  else{
    p_log->warning("Trying to remove from empty list");
  }
}

//first()
template <class T>
bool DLL <T> :: first(T& elem)
{
  //if list is not empty this function places
  //current pointer at head of list

  //assume there is not a first item
  bool retVal = false;

  //if the list is not empty
  if(!isEmpty()){
    
    //indicate there is a first item
    retVal = true;

    //copy data into reference parameter
    elem = p_head->data;

    //store current node that is being processed
    p_current = p_head;

  }

  return retVal;

}

//next()
template <class T>
bool DLL <T> :: next(T& elem)
{
  //assume at tail of list
  bool retVal = false;

  //if we have not processed all the elements
  //moving tailwards
  if(p_current->p_next != 0){
    
    //move the current pointer towards tail
    p_current = p_current->p_next;

    //indicate there is another p_next
    retVal = true;

    //copy the data into ref parameter
    elem = p_current->data;
  }

  return retVal;

}

//last()
template <class T>
bool DLL <T> :: last(T& elem)
{
  //if list is not empty this function places
  //current pointer to tail of list
  
  bool retVal = false;

  //if list is not empty
  if(!isEmpty()){

    //indicate there is a last item
    retVal = true;

    //copy data into ref parameter
    elem = p_tail->data;

    //set current node to last/tail
    p_current = p_tail;

  }

  return retVal;

}

//previous
template <class T>
bool DLL <T> :: previous(T& elem)
{
  //if list is not empty this function moves
  //current pointer towards head

  //assume we are at head
  bool retVal = false;

  //if we have not processed all the elements
  if(p_current->p_prev != 0){

    //move current pointer towards head one
    p_current = p_current->p_prev;

    //indicate there is another item
    retVal = true;

    //copy data of item into ref param
    elem = p_current->data;
     
  }

  return retVal;

}

//size()
template <class T>
int DLL <T> :: size()
{
  return numElements;
}

//setLog()
template <class T>
void DLL <T> :: setLog(Log* someLog)
{
  p_log = someLog;
}

//isEmpty()
template <class T>
bool DLL <T> :: isEmpty()
{
  return (size() == 0);
}

//printAllFromTail()
template <class T>
void DLL <T> :: printAllFromTail()
{
  //helper T object
  T val;

  if(isEmpty()){
    
    //do not print and tell log
    p_log->info("Not printing because list is empty");
  
  }
  else{
    
    //if there is a last item (list is not empty)
    //store the element in val
    if(last(val)){

      p_log->info(val);

      //while we are not at the end, store each element in val
      while(previous(val)){

	p_log->info(val);

      }

    }
  }    
}

//printAllFromHead()
template <class T>
void DLL <T> :: printAllFromHead()
{
  //helper T object
  T val;

  if(isEmpty()){
    
    //do not print and tell log
    p_log->info("Not printing because list is empty");
  
  }
  else{
    
    //if there is a last item (list is not empty)
    //store the element in val
    if(first(val)){

      p_log->info(val);

      //while we are not at the end, store each element in val
      while(next(val)){

	p_log->info(val);

      }
    }
  }
}

