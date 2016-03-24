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
#include <stdlib.h>
#include <vector>
#include "PriorityQueue.hpp"

using namespace std;

#define get_leftChind(x) 2*x+1
#define get_rightChild(x) 2*x+2
#define get_parent(x) (x-1)/2        // x has to be (int) in this case

template <typename T>
void adjustUp(vector<T> *heap, unsigned int location);

template <typename T>
void adjustDown(vector<T> *heap, unsigned int location);

template <typename T>
void heapification(vector<T> &heap);

template <typename T>
class CompleteBinaryHeap: public PriorityQueue<T> {
private:
    vector<T> *heap;
public:
    CompleteBinaryHeap() { heap = new vector<T>(); }
    CompleteBinaryHeap(vector<T> a);    // constructor using Floyd algorithm
    ~CompleteBinaryHeap() { delete heap; }
    size_t size() { return heap->size(); }
    void insert(T x);
    T getMax();
    T delMax();
    bool isMaxHeap();
};

// heapification constructor
template <typename T>
CompleteBinaryHeap<T>::CompleteBinaryHeap(vector<T> a) {
    heap = new vector<T>(a);
    for (int i = (int)size() - 1; i >= 0; i--) {
        adjustDown(heap, i);
    }
}

// return whether it is a max heap, for test purpose
template <typename T>
bool CompleteBinaryHeap<T>::isMaxHeap() {
    int leftChild, rightChild;
    for (int i = 0; i < (int)this->size(); i++) {
        leftChild = get_leftChind(i);
        rightChild = get_rightChild(i);
        if (leftChild < this->size() && (*heap)[leftChild] > (*heap)[i]) {
            return false;
        }
        if (rightChild < this->size() && (*heap)[rightChild] > (*heap)[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
T CompleteBinaryHeap<T>::getMax() {
    return (*heap)[0];
}

template <typename T>
void CompleteBinaryHeap<T>::insert(T x) {
    heap->push_back(x);
    adjustUp(heap, int(size())-1);
}

template <typename T>
T CompleteBinaryHeap<T>::delMax() {
    // copy the maximum value
    T max = getMax();
    // copy the end value to the front
    (*heap)[0] = heap->back();
    // pop the last value
    heap->pop_back();
    adjustDown(heap, 0);
    return max;
}


// helper functions, not method
template <typename T>
void heapification(vector<T> &heap) {
    for (int i = (int)heap.size() - 1; i >= 0; i--) {
        adjustDown(&heap, i);
    }
}

// adjust from location up, used for insert
template <typename T>
void adjustUp(vector<T> *heap, unsigned int location) {
    int parent = get_parent(location);
    while (location > 0 && (*heap)[location] > (*heap)[parent]) {
        std::swap((*heap)[location], (*heap)[parent]);
        location = parent;
        parent = get_parent(location);
    }
}

// adjust from location down, used for delete
template <typename T>
void adjustDown(vector<T> *heap, unsigned int location) {
    int leftChild = get_leftChind(location);
    int rightChild = get_rightChild(location);
    do {
        // has reach the bottom
        if (leftChild >= heap->size()) {
            return;
        }
        if (rightChild >= heap->size()) {
            if ((*heap)[location] < (*heap)[leftChild]) {
                std::swap((*heap)[location], (*heap)[leftChild]);
            }
            return;
        }
        // have both leftChild and rightChild
        if ((*heap)[location] >= (*heap)[leftChild] && (*heap)[location] >= (*heap)[rightChild]) {
            return;
        } else {
            if ((*heap)[leftChild] > (*heap)[rightChild]) {
                std::swap((*heap)[location], (*heap)[leftChild]);
                location = leftChild;
            } else {
                std::swap((*heap)[location], (*heap)[rightChild]);
                location = rightChild;
            }
        }
        leftChild = get_leftChind(location);
        rightChild = get_rightChild(location);
    } while(1);
}

template <typename T>
void heapSort(vector<T> &a) {
    CompleteBinaryHeap<T> helper_heap(a);
    a.clear();
    while (!helper_heap.empty()) {
        a.push_back(helper_heap.delMax());
    }
}

#endif /* Heap_hpp */
