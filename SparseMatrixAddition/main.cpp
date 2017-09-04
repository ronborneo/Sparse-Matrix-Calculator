//
//  main.cpp
//  SparseMatrixAddition
//
//  Created by Ron Borneo on 8/25/17.
//  Copyright © 2017 Ron Borneo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "UserLinkedList.hpp"
#include "UserArrayList.hpp"
#include "ArgumentManager.h"

void readInput_linkedList(std::string fileName, UserLinkedList &matrix){
  ifstream matrixInput(fileName);
  std::string str;
  int i, j;
  double value;
  while(getline(matrixInput, str)){
    if(!str.empty() && str[0] != '#'){
      stringstream ss(str.c_str());
      ss >> i;
      ss >> j;
      ss >> value;
      matrix.addEntry(new Entry(i, j, value));
    }
  }
}

void readInput_arrayList(std::string fileName, UserArrayList &list){
  ifstream input(fileName);
  std::string str;
  int i, j;
  double value;
  while(getline(input, str)){
    if(!str.empty() && str[0] != '#'){
      stringstream ss(str.c_str());
      ss >> i;
      ss >> j;
      ss >> value;
      list.pushBack(Node(i, j, value));
    }
  }
}

/**
 In matrix multiplication, you should always sort.
 Allows in simplicity of the calculation.
 */
void sortTheTwoLists(UserArrayList &listA, UserArrayList &listB){
  if(!listA.isSorted()) {
    listA.sortList('i');
  }
  
  if(!listB.isSorted()) {
    listB.sortList('i');
  }
}

int main(int argc, char * argv[]) {
  
  if(argc < 2){
    std::cout << "Invalid Arguments\n";
    exit(0);
  }
  
  ArgumentManager am(argc, argv);
  std::string inputA = am.get("A");
  std::string inputB = am.get("B");
  std::string storage = am.get("Storage");
  std::string recursive = am.get("Recursive");
  std::string operation = am.get("Operation");
  
  if(operation == "Multiply") {
    /**
     Sparse Matrix Multiplication
     
     For multiplication, array list will be used for storage.
     This permits more flexibility in terms of what sorting method is selected.
     */
    UserArrayList listA;
    UserArrayList listB;

    readInput_arrayList(inputA, listA);
    readInput_arrayList(inputB, listB);
    
    sortTheTwoLists(listA, listB);
    
    UserArrayList listC;

    listC = listA * listB;
    listC.printList();
  } else {
    /**
     Sparse Matrix Addition
     
     Storage: LinkedList/ArrayList
     Recursive: Y/N
     */
    if(storage == "LinkedList"){
      UserLinkedList matrixA;
      UserLinkedList matrixB;
      
      readInput_linkedList(inputA, matrixA);
      readInput_linkedList(inputB, matrixB);
      
      UserLinkedList matrixC;
      matrixC = recursive == "Y" ? matrixA.recursiveAddition(matrixB) : matrixA + matrixB;
      matrixC.printList();
    } else {
      UserArrayList listA;
      UserArrayList listB;
      
      readInput_arrayList(inputA, listA);
      readInput_arrayList(inputB, listB);
      
      UserArrayList listC;
      listC = recursive == "Y" ? listA.recursiveAddition(listB) : listA + listB;
      listC.sortList('i');
      listC.printList();
    }
  }
  return 0;
}
