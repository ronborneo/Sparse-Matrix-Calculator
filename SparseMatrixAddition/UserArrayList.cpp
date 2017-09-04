//
//  UserArrayList.cpp
//  SparseMatrixAddition
//
//  Created by Ron Borneo on 8/26/17.
//  Copyright © 2017 Ron Borneo. All rights reserved.
//

#include "UserArrayList.hpp"

UserArrayList& UserArrayList::operator=(const UserArrayList& otherList){
  delete [] arrayList;
  size = otherList.getSize();
  capacity = otherList.getCapacity();
  arrayList = new Node[capacity];
  for(int i = 0; i < size; i++){
    arrayList[i] = Node(otherList[i].i, otherList[i].j, otherList[i].value);
  }
  return *this;
}

UserArrayList UserArrayList::operator+(const UserArrayList& otherList){
  if(!checkIfValidMatrixAddition(otherList)){
    exit(0);
  }
  bool* usedValues = new bool[otherList.getSize()];
  UserArrayList resultList;
  for(int i = 0; i < size; i++){
    for(int j = 0; j < otherList.getSize(); j++){
      if(arrayList[i].i == otherList[j].i && arrayList[i].j == otherList[j].j){
        double sum = arrayList[i].value + otherList[j].value;
        resultList.pushBack(Node(arrayList[i].i, arrayList[i].j, sum));
        arrayList[i].used = true;
        usedValues[j] = true;
        break;
      }
    }
    if(!arrayList[i].used && (checkIfMax(arrayList[i]) || (arrayList[i].value != 0))){
      resultList.pushBack(arrayList[i]);
    }
  }
  insertRemainingEntries(resultList, otherList, usedValues);
  delete [] usedValues;
  return resultList;
}

Node& UserArrayList::operator[](int index) {
  if(index >= capacity || index < 0){
    std::cout << "ERROR: Out of bounds index.";
    exit(0);
  }
  return arrayList[index];
}

const Node& UserArrayList::operator[](int index) const {
  if(index >= capacity || index < 0){
    std::cout << "ERROR: Out of bounds index.";
    exit(0);
  }
  return arrayList[index];
}

void UserArrayList::insertRemainingEntries(UserArrayList& resultList, const UserArrayList& otherList, bool* usedValues){
  for(int i = 0; i < otherList.size; i++){
    if(!usedValues[i] && (otherList[i].value != 0 || checkIfMax(otherList[i]))){
      resultList.pushBack(otherList[i]);
    }
  }
}

void UserArrayList::updateMax(const Node newEntry) {
  if(newEntry.i >= maxI && newEntry.j >= maxJ){
    maxI = newEntry.i;
    maxJ = newEntry.j;
  }
}

void UserArrayList::pushBack(const Node newEntry) {
  if(size + 1 == capacity){
    Node* newList = new Node[capacity * 2];
    copyOver(newList);
  }
  updateMax(newEntry);
  if(!checkIfMax(newEntry) && newEntry.value == 0)
    return;
  arrayList[size++] = newEntry;
}

void UserArrayList::pushBackSorted(const Node newEntry) {
  
  /**
   *
   *  Implement so there is no need to keep calling merge sort after every insert
   *  - Reduces over head and increases performance
   *
   */
  
  /*
  if(size + 1 == capacity){
    Node* newList = new Node[capacity * 2];
    copyOver(newList);
  }
  updateMax(newEntry);
  if(!checkIfMax(newEntry) && newEntry.value == 0)
    return;
  arrayList[size++] = newEntry;
   */
}

void UserArrayList::copyOver(Node* newList){
  for(int i = 0; i < capacity; i++){
    newList[i] = arrayList[i];
  }
  this->capacity *= 2;
  delete [] arrayList;
  arrayList = newList;
}

void UserArrayList::myMergeSort(Node* list, const int size, const char orderBy){
  if(size < 2){
    return;
  }
  int mid = size / 2;
  Node* leftSide = new Node[mid];
  Node* rightSide = new Node[size - mid];
  for(int i = 0; i < mid; i++){
    leftSide[i] = list[i];
  }
  for(int i = 0; i < size - mid; i++){
    int currentIndex = i + mid;
    rightSide[i] = list[currentIndex];
  }
  myMergeSort(leftSide, mid, orderBy);
  myMergeSort(rightSide, size - mid, orderBy);
  mergeRoutine(list, leftSide, mid, rightSide, size - mid, orderBy);
  delete [] leftSide;
  delete [] rightSide;
}

void UserArrayList::mergeRoutine(Node* resultList, Node* leftSide, const int leftSideCount, Node* rightSide, const int rightSideCount, const char orderBy){
  int leftSideIndex = 0, rightSideIndex = 0, resultIndex = 0;
  if(orderBy == 'j'){
    while(leftSideIndex < leftSideCount && rightSideIndex < rightSideCount){
      if(leftSide[leftSideIndex].isLessThanByJ(rightSide[rightSideIndex])){
        resultList[resultIndex++] = leftSide[leftSideIndex++];
      } else {
        resultList[resultIndex++] = rightSide[rightSideIndex++];
      }
    }
  } else {
    while(leftSideIndex < leftSideCount && rightSideIndex < rightSideCount){
      if(leftSide[leftSideIndex] < rightSide[rightSideIndex]){
        resultList[resultIndex++] = leftSide[leftSideIndex++];
      } else {
        resultList[resultIndex++] = rightSide[rightSideIndex++];
      }
    }
  }
  
  while(leftSideIndex < leftSideCount){
    resultList[resultIndex++] = leftSide[leftSideIndex++];
  }
  while(rightSideIndex < rightSideCount){
    resultList[resultIndex++] = rightSide[rightSideIndex++];
  }
}

void UserArrayList::sortList(const char orderBy = 'i'){
  myMergeSort(arrayList, size, orderBy);
}

UserArrayList UserArrayList::recursiveAddition(const UserArrayList& otherList){
  if(!checkIfValidMatrixAddition(otherList)){
    exit(0);
  }
  UserArrayList resultList;
  bool* usedValues = new bool[otherList.size];
  recAdditionHelper(resultList, otherList, 0, 0, usedValues);
  insertRemainingEntries(resultList, otherList, usedValues);
  return resultList;
}

void UserArrayList::recAdditionHelper(UserArrayList& resultMatrix, const UserArrayList& otherList, int index1, int index2, bool* usedValues){
  if(index1 == size)
    return;
  recAdditionHelper2(resultMatrix, otherList, index1, index2, usedValues);
  recAdditionHelper(resultMatrix, otherList, index1 + 1, index2, usedValues);
}

void UserArrayList::recAdditionHelper2(UserArrayList& resultMatrix, const UserArrayList& otherList, int index1, int index2, bool* usedValues){
  if(index2 == otherList.getSize()){
    // If the current node did not find a match, it may still be added if it is the corner or it's a value is not zero
    if(!arrayList[index1].used && (checkIfMax(arrayList[index1]) || arrayList[index1].value != 0)){
      resultMatrix.pushBack(arrayList[index1]);
    }
    return;
  }
  
  if(arrayList[index1].i == otherList[index2].i && arrayList[index1].j == otherList[index2].j){
    double sum = arrayList[index1].value + otherList[index2].value;
    resultMatrix.pushBack(Node(arrayList[index1].i, arrayList[index1].j, sum));
    arrayList[index1].used = true;
    usedValues[index2] = true;
    return;
  }
  
  recAdditionHelper2(resultMatrix, otherList, index1, index2 + 1, usedValues);
}

bool UserArrayList::isSorted() const {
  for(int i = 0; i < size - 1; i++) {
    if(arrayList[i] > arrayList[i + 1])
      return false;
  }
  return true;
}

UserArrayList UserArrayList::operator*(const UserArrayList& otherList) {
  if(!checkIfValidMatrixMultiplication(otherList)){
    std::cout << "Invalid Matrix Dimensions\n";
    exit(0);
  }
  
  UserArrayList resultList;
  
  for(int m = 0; m < size; m++) {
    int indexForListB = otherList.binarySearchForIndex(0, otherList.getSize(), arrayList[m].j, 'i');
    if(indexForListB != -1) {
      do {
        int product = arrayList[m].value * otherList[indexForListB].value;
        if(product == 0 && !(arrayList[m].i == maxI && otherList[indexForListB].j == otherList.getMaxJ())) {
          indexForListB++;
          continue;
        }
        Node newNode(arrayList[m].i, otherList[indexForListB].j, product);
        int indexForInsertion = resultList.binarySearchForNode(0, resultList.getSize(), newNode);
        if(indexForInsertion != -1) {
          // Aggregate Sum
          resultList[indexForInsertion].value += product;
        } else {
          // Add new entry into array, keep array sorted.
          // Implement pushBackSorted.
          resultList.pushBack(newNode);
          resultList.sortList();
        }
        indexForListB++;
      } while(indexForListB < otherList.getSize() && otherList[indexForListB].i == otherList[indexForListB - 1].i);
    }
  }
  return resultList;
}

/*
 * To be used when inserting into the resultList
 */
int UserArrayList::binarySearchForNode(int startIndex, int endIndex, const Node& nodeToSearchFor) const {
  if(endIndex >= startIndex) {
    int mid = startIndex + (endIndex - startIndex) / 2;
    if(arrayList[mid] == nodeToSearchFor) {
      return mid;
    } else if(arrayList[mid] > nodeToSearchFor) {
      return binarySearchForNode(startIndex, mid - 1, nodeToSearchFor);
    } else {
      return binarySearchForNode(mid + 1, endIndex, nodeToSearchFor);
    }
  }
  // Reached when node is not found
  return -1;
}

/**
 * Standard binary search to return index of node with a matching j value.
 */
int UserArrayList::binarySearchForIndex(int startIndex, int endIndex, int valueToSearchFor, const char iOrJ) const {
  if(endIndex >= startIndex) {
    int mid = startIndex + (endIndex - startIndex) / 2;
    if(iOrJ == 'j') {
      if(arrayList[mid].j == valueToSearchFor) {
        // Shift to first occurence of jValue
        mid = findFirstOccurenceOfJVal(valueToSearchFor, mid);
        return mid;
      } else if(arrayList[mid].j > valueToSearchFor) {
        return binarySearchForIndex(startIndex, mid - 1, valueToSearchFor, iOrJ);
      } else {
        return binarySearchForIndex(mid + 1, endIndex, valueToSearchFor, iOrJ);
      }
    } else {
      if(arrayList[mid].i == valueToSearchFor) {
        // Shift to first occurence of iValue
        mid = findFirstOccurenceOfIVal(valueToSearchFor, mid);
        return mid;
      } else if(arrayList[mid].i > valueToSearchFor) {
        return binarySearchForIndex(startIndex, mid - 1, valueToSearchFor, iOrJ);
      } else {
        return binarySearchForIndex(mid + 1, endIndex, valueToSearchFor, iOrJ);
      }
    }
  }
  // Reached when element is not found
  return -1;
}

/**
 * Shift the index down to the lowest possible index with a match j value.
 */
int UserArrayList::findFirstOccurenceOfJVal(const int jValue, int index) const {
  while(index > 0 && arrayList[index - 1].j == jValue){
    index--;
  }
  return index;
}

/**
 * Shift the index down to the lowest possible index with a match i value.
 */
int UserArrayList::findFirstOccurenceOfIVal(const int iValue, int index) const {
  while(index > 0 && arrayList[index - 1].i == iValue){
    index--;
  }
  return index;
}










