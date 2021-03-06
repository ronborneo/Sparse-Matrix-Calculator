//
//  Node.h
//  SparseMatrixAddition
//
//  Created by Ron Borneo on 8/26/17.
//  Copyright © 2017 Ron Borneo. All rights reserved.
//

#ifndef Node_h
#define Node_h

struct Node {
  int i, j;
  double value;
  bool used;
  Node() : i(0), j(0), value(0), used(false) { }
  Node(int i, int j, double v){
    this->i = i;
    this->j = j;
    this->value = v;
    used = false;
  }
  Node(const Node &otherNode) {
    i = otherNode.i;
    j = otherNode.j;
    value = otherNode.value;
    used = false;
  }
  
  Node& operator=(const Node &otherNode) {
    i = otherNode.i;
    j = otherNode.j;
    value = otherNode.value;
    used = otherNode.used;
    return *this;
  }
  
  void printNode() {
    std::cout << i << ' ' << j << ' ' << std::fixed << std::setprecision(2) << value << '\n';
  }
  bool operator < (const Node& otherEntry){
    return i < otherEntry.i || (i == otherEntry.i && j < otherEntry.j);
  }
  
  bool operator > (const Node& otherEntry){
    return !(*this < otherEntry);
  }
  
  bool operator == (const Node& otherEntry){
    return i == otherEntry.i && j == otherEntry.j;
  }
  
  bool isLessThanByJ(const Node& otherEntry) {
    return j < otherEntry.j || (j == otherEntry.j && i < otherEntry.i);
  }
  
  bool isGreaterThanByJ(const Node& otherEntry) {
    return !(this->isLessThanByJ(otherEntry));
  }
};

#endif /* Node_h */
