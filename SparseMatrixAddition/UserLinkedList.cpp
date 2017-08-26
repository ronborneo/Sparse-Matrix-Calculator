//
//  UserLinkedList.cpp
//  SparseMatrixAddition
//
//  Created by Ron Borneo on 8/25/17.
//  Copyright © 2017 Ron Borneo. All rights reserved.
//

#include "UserLinkedList.hpp"

UserLinkedList& UserLinkedList::operator=(const UserLinkedList& other){
  //std::cout << "Assignment Operator Called\n";
  deleteList();
  Entry *current = other.getHead();
  while(current != nullptr){
    addEntry(new Entry(current->i, current->j, current->v));
    current = current->link;
  }
  return *this;
}

void UserLinkedList::addEntry(Entry* newEntry){
  checkMaxValues(newEntry->i, newEntry->j);
  if(head == nullptr){
    head = newEntry;
  } else {
    tail->link = newEntry;
  }
  tail = newEntry;
}

void UserLinkedList::setTail(){
  Entry* current = head;
  while(current->link != nullptr){
    current = current->link;
  }
  tail = current;
}

void UserLinkedList::addEntrySorted(Entry *newEntry){
  // Empty List
  if(head == nullptr){
    head = newEntry;
  } else {
    // Easy insertion when value is less than head's value
    if(*newEntry < *head){
      newEntry->link = head;
      head = newEntry;
      // When value is greater than head
    } else if(head->link == nullptr && *newEntry > *head) {
      head->link = newEntry;
    } else {
      Entry* trailCurrent = head;
      Entry* current = head->link;
      while(current != nullptr){
        if(*newEntry < *current){
          trailCurrent->link = newEntry;
          newEntry->link = current;
          break;
        }
        trailCurrent = trailCurrent->link;
        current = current->link;
      }
      if(*trailCurrent < *newEntry){
        trailCurrent->link = newEntry;
      }
    }
  }
}

void UserLinkedList::checkMaxValues(int i, int j){
  if(i > m_maxI)
    m_maxI = i;
  if(j > m_maxJ)
    m_maxJ = j;
}

UserLinkedList UserLinkedList::operator+(const UserLinkedList& otherMatrix){
  if(!isValidAddition(otherMatrix)){
    exit(0);
  }
  UserLinkedList resultMatrix;
  Entry* matrixB_current = nullptr;
  Entry* matrixA_current = head;
  while(matrixA_current != nullptr){
    matrixB_current = otherMatrix.getHead();
    while(matrixB_current != nullptr){
      if(matrixA_current->i == matrixB_current->i && matrixA_current->j == matrixB_current->j){
        double sum = matrixA_current->v + matrixB_current->v;
        resultMatrix.addEntrySorted(new Entry(matrixA_current->i, matrixA_current->j, sum));
        matrixB_current->used = true;
        matrixA_current->used = true;
        break;
      }
      matrixB_current = matrixB_current->link;
    }
    if(!matrixA_current->used && (checkIfMax(matrixA_current) || matrixA_current->v != 0)){
      resultMatrix.addEntrySorted(new Entry(matrixA_current->i, matrixA_current->j, matrixA_current->v));
    }
    matrixA_current = matrixA_current->link;
  }
  addRemainingEntries(resultMatrix, otherMatrix);
  return resultMatrix;
}

void UserLinkedList::addRemainingEntries(UserLinkedList& resultMatrix, const UserLinkedList& otherMatrix){
  Entry *current = otherMatrix.getHead();
  while(current != nullptr){
    if(!current->used && ((current->v != 0) || (current->v == 0 && checkIfMax(current)))){
      resultMatrix.addEntrySorted(new Entry(current->i, current->j, current->v));
    }
    current = current->link;
  }
}

UserLinkedList UserLinkedList::recursiveAddition(const UserLinkedList &otherMatrix){
  if(!isValidAddition(otherMatrix)){
    exit(0);
  }
  UserLinkedList resultList;
  recAdditionHelper(resultList, head, otherMatrix.getHead());
  addRemainingEntries(resultList, otherMatrix);
  return resultList;
}

void UserLinkedList::recAdditionHelper(UserLinkedList& resultMatrix, Entry* current, Entry* otherHead){
  if(current == nullptr)
    return;
  recAdditionHelper2(resultMatrix, current, otherHead);
  recAdditionHelper(resultMatrix, current->link, otherHead);
}

void UserLinkedList::recAdditionHelper2(UserLinkedList& resultMatrix, Entry* current, Entry* current2){
  if(current2 == nullptr){
    // If the current node did not find a match, it may still be added if it is the corner or it's a value is not zero
    if(!current->used && (checkIfMax(current) || current->v != 0)){
      resultMatrix.addEntrySorted(new Entry(current->i, current->j, current->v));
    }
    return;
  }
  
  if(current->i == current2->i && current->j == current2->j){
    double sum = current->v + current2->v;
    resultMatrix.addEntrySorted(new Entry(current->i, current->j, sum));
    current2->used = true;
    current->used = true;
    return;
  }
  
  recAdditionHelper2(resultMatrix, current, current2->link);
}

void UserLinkedList::printList(){
  Entry* temp = head;
  while(temp != nullptr){
    std::cout
    << temp->i << ' '
    << temp->j << ' '
    << std::fixed << std::setprecision(2)
    << temp->v << '\n';
    temp = temp->link;
  }
}

void UserLinkedList::deleteList(){
  Entry* temp = head;
  while(head != nullptr){
    temp = head;
    head = head->link;
    delete temp;
  }
}








