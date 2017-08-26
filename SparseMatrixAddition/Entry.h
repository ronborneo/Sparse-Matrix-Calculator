//
//  Entry.h
//  SparseMatrixAddition
//
//  Created by Ron Borneo on 8/26/17.
//  Copyright © 2017 Ron Borneo. All rights reserved.
//

#ifndef Entry_h
#define Entry_h

struct Entry {
  int i;
  int j;
  double v;
  bool used;
  Entry* link;
  
  Entry(int i, int j, double v){
    this->i = i;
    this->j = j;
    this->v = v;
    used = false;
    link = nullptr;
  }
  bool operator < (const Entry& otherEntry){
    return i < otherEntry.i || (i == otherEntry.i && j < otherEntry.j);
  }
  bool operator > (const Entry& otherEntry){
    return !(*this < otherEntry);
  }
};

#endif /* Entry_h */
