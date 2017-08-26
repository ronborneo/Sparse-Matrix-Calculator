//
//  UserLinkedList.hpp
//  SparseMatrixAddition
//
//  Created by Ron Borneo on 8/25/17.
//  Copyright © 2017 Ron Borneo. All rights reserved.
//

#ifndef UserLinkedList_hpp
#define UserLinkedList_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "Entry.h"

class UserLinkedList {
public:
  UserLinkedList() : head(nullptr), tail(nullptr), m_maxI(0), m_maxJ(0) {
    //std::cout << "Constructor Called\n";
  }
  
  UserLinkedList(const UserLinkedList& otherMatrix){
    //std::cout << "Copy Constructor Called\n";
  }
  
  UserLinkedList& operator=(const UserLinkedList& other);
  UserLinkedList operator+(const UserLinkedList& otherMatrix);
  UserLinkedList recursiveAddition(const UserLinkedList& otherMatrix);
  
  void recAdditionHelper(UserLinkedList& resultMatrix, Entry* current, Entry*);
  void recAdditionHelper2(UserLinkedList& resultMatrix, Entry* current, Entry*);

  void addEntry(Entry* newEntry);
  void setTail();
  void addEntrySorted(Entry *newEntry);
  void checkMaxValues(int i, int j);
  void addRemainingEntries(UserLinkedList& resultMatrix, const UserLinkedList& otherMatrix);
  
  bool isValidAddition(const UserLinkedList& otherMatrix){
    return m_maxI == otherMatrix.m_maxI && m_maxJ == otherMatrix.m_maxJ;
  }
  bool checkIfMax(Entry* entry){
    return m_maxI == entry->i && m_maxJ == entry->j;
  }
  
  Entry* getHead() const { return head; }
  
  void printList();
  void printMaxes() { std::cout << "m_maxI: " << m_maxI << std::endl << "m_maxJ: " << m_maxJ << std::endl; }
  void deleteList();
  
  ~UserLinkedList(){
    deleteList();
  }
  
private:
  Entry* head;
  Entry* tail;
  int m_maxI;
  int m_maxJ;
};


#endif /* UserLinkedList_hpp */
