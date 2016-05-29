//
//  PriorityQueue.hpp
//  testProgram
//
//  Created by Chi Zhang on 1/20/16.
//  Copyright © 2016 University of Southern California. All rights reserved.
//  Define a priority queue ADT

#ifndef PriorityQueue_hpp
#define PriorityQueue_hpp

#include <stdio.h>

template <typename T>
class PriorityQueue {
public:
    virtual size_t size() = 0;
    virtual void insert(T x) = 0;
    virtual T getMax() = 0;
    virtual T delMax() = 0;
    bool empty() { return !size(); }
};

#endif /* PriorityQueue_hpp */
