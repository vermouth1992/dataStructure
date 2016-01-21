//
//  Heap.hpp
//  testProgram
//
//  Created by Chi Zhang on 1/20/16.
//  Copyright © 2016 University of Southern California. All rights reserved.
//  The implementation of heap is actual using vector

#ifndef Heap_hpp
#define Heap_hpp

#include <stdio.h>
#include <vector>
#include "PriorityQueue.hpp"

using namespace std;

#define get_leftChind(x) 2*x+1
#define get_rightChild(x) 2*x+2
#define get_parent(x) (x-1)/2        // x has to be (int) in this case


template <typename T>
class CompleteBinaryHeap: public PriorityQueue<T> {
private:
    vector<T> *heap;
    void adjustUp(unsigned int location);
    void adjustDown(unsigned int location);
public:
    CompleteBinaryHeap() { heap = new vector<T>(); }
    ~CompleteBinaryHeap() { delete heap; }
    size_t size() { return heap->size(); }
    void insert(T x);
    T getMax();
    T delMax();
};

// adjust from location up, used for insert
template <typename T>
void CompleteBinaryHeap<T>::adjustUp(unsigned int location) {
    int parent = get_parent(location);
    while (location > 0 && (*heap)[location] > (*heap)[parent]) {
        std::swap((*heap)[location], (*heap)[parent]);
        location = parent;
        parent = get_parent(location);
    }
}

// adjust from location down, used for delete
template <typename T>
void CompleteBinaryHeap<T>::adjustDown(unsigned int location) {
    int leftChild = get_leftChind(location);
    int rightChild = get_rightChild(location);
    do {
        // has reach the bottome
        if (leftChild >= size()) {
            return;
        }
        if (rightChild >= size()) {
            if ((*heap)[location] < (*heap)[leftChild]) {
                std::swap((*heap)[location], (*heap)[leftChild]);
            }
            return;
        }
        if ((*heap)[leftChild] > (*heap)[rightChild]) {
            std::swap((*heap)[location], (*heap)[leftChild]);
            location = leftChild;
        } else {
            std::swap((*heap)[location], (*heap)[rightChild]);
            location = rightChild;
        }
        leftChild = get_leftChind(location);
        rightChild = get_rightChild(location);
    } while(1);
}

template <typename T>
T CompleteBinaryHeap<T>::getMax() {
    return (*heap)[0];
}

template <typename T>
void CompleteBinaryHeap<T>::insert(T x) {
    heap->push_back(x);
    adjustUp(int(size())-1);
}

template <typename T>
T CompleteBinaryHeap<T>::delMax() {
    // copy the maximum value
    T max = getMax();
    // copy the end value to the front
    (*heap)[0] = heap->back();
    // pop the last value
    heap->pop_back();
    adjustDown(0);
    return max;
}



#endif /* Heap_hpp */
