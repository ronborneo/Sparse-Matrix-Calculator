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
  
  UserArrayList operator*(const UserArrayList& otherList);
  
  UserArrayList recursiveAddition(const UserArrayList& otherList);
  
  Node& operator[](const int index);
  
  const Node& operator[](const int index) const;
  
  void sortList(const char orderBy);
  
  void updateMax(const Node newEntry);
  
  bool checkIfMax(const Node newEntry){
    return maxI == newEntry.i && maxJ == newEntry.j;
  }
  
  int getMaxI() const { return maxI; }
  
  int getMaxJ() const { return maxJ; }
  
  void pushBack(const Node newEntry);
  
  void pushBackSorted(const Node newEntry);
  
  int getSize() const { return size; }
  
  int getCapacity() const { return capacity; }
  
  bool isSorted() const;
  
  int binarySearchForIndex(int startIndex, int endIndex, int ValueToSearchFor, const char) const;

  int binarySearchForNode(int startIndex, int endIndex, const Node& nodeToSearchFor) const;
  
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
  void mergeRoutine(Node*, Node* leftSide, const int, Node* rightSide, const int, const char);
  
  void insertRemainingEntries(UserArrayList& resultList, const UserArrayList& otherList, bool* usedValues);
  
  bool checkIfValidMatrixAddition(const UserArrayList& otherList) const {
    return maxI == otherList.maxI && maxJ == otherList.maxJ;
  }
  
  bool checkIfValidMatrixMultiplication(const UserArrayList& otherList) const {
    return maxJ == otherList.maxI;
  }
  
  void copyOver(Node* newList);
  
  void myMergeSort(Node* list, int size, const char orderBy);
  
  void recAdditionHelper(UserArrayList& resultMatrix, const UserArrayList&, int index1, int index2, bool*);
  
  void recAdditionHelper2(UserArrayList& resultMatrix, const UserArrayList&, int index1, int index2, bool*);
  
  int findFirstOccurenceOfJVal(const int jValue, int index) const;
  
  int findFirstOccurenceOfIVal(const int iValue, int index) const;

  Node *arrayList;
  int size;
  int capacity;
  int maxI;
  int maxJ;
};

#endif /* UserArrayList_hpp */
