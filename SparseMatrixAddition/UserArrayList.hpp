//
//  UserArrayList.hpp
//  SparseMatrixAddition
//
//  Created by Ron Borneo on 8/26/17.
//  Copyright © 2017 Ron Borneo. All rights reserved.
//

#ifndef UserArrayList_hpp
#define UserArrayList_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "Node.h"

class UserArrayList {
public:
  UserArrayList() : size(0), capacity(64), maxI(0), maxJ(0) {
    arrayList = new Node[capacity];
  }
  
  ~UserArrayList() {
    delete [] arrayList;
  }
  
  UserArrayList(const UserArrayList& otherList){
    std::cout << "Copy Constructor Called\n";
  }
  
  UserArrayList& operator=(const UserArrayList& otherList);
  
  UserArrayList operator+(const UserArrayList& otherList);
  
  UserArrayList recursiveAddition(const UserArrayList& otherList);
  
  void recAdditionHelper(UserArrayList& resultMatrix, const UserArrayList&, int index1, int index2, bool*);
  void recAdditionHelper2(UserArrayList& resultMatrix, const UserArrayList&, int index1, int index2, bool*);
  
  Node& operator[](int index);
  
  const Node& operator[](int index) const;
  
  void insertRemainingEntries(UserArrayList& resultList, const UserArrayList& otherList, bool* usedValues);
  
  bool checkIfValidMatrixAddition(const UserArrayList& otherList) const {
    return maxI == otherList.maxI && maxJ == otherList.maxJ;
  }
  
  void sortList();
  
  void myMergeSort(Node* list, int size);
  
  void mergeRoutine(Node*, Node* leftSide, const int, Node* rightSide, const int);
  
  void updateMax(const Node newEntry);
  
  bool checkIfMax(Node newEntry){
    return maxI == newEntry.i && maxJ == newEntry.j;
  }
  
  void pushBack(const Node newEntry);
  
  void copyOver(Node* newList);
  
  int getSize() const { return size; }
  int getCapacity() const { return capacity; }
  
  void printList(){
    for(int i = 0; i < size; i++){
      arrayList[i].printNode();
    }
    std::cout << std::endl;
  }
  
  void printListInfo(){
    std::cout << "Size: " << size << "\nCapacity: " << capacity << std::endl;
  }
  
private:
  Node *arrayList;
  int size;
  int capacity;
  int maxI;
  int maxJ;
};

#endif /* UserArrayList_hpp */
