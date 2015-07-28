//
//  MyVector.h
//  testProgram
//
//  Created by Chi Zhang on 7/15/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

#ifndef __testProgram__MyVector__
#define __testProgram__MyVector__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

#endif /* defined(__testProgram__MyVector__) */

#define default_capacity 3

template<typename T>
class MyVector {
private:
    int _size; //how many elements in vector now
    int _capacity; //how many elements can vector have
    T* _elem;  //elements in this vector
    
protected:
    void copyFrom(T* const A, int low, int high);  //复制
    void expand();  //扩容
    void shrink();
    bool bubble(int low, int high);
    void bubbleSort(int low, int high);
    void merge(int low, int middle, int high);
    void mergeSort(int low, int high);
    
    int partition(int low, int high);
    void quickSort(int low, int high);
    void heapSort(int low, int high);
    
public:
    //constructor
    MyVector(int c = default_capacity) {_elem = new T[_capacity = c]; _size = 0;}
    MyVector(T* A, int low, int high) {copyFrom(A, low, high);}
    MyVector(T* A, int n) {copyFrom(A, 0, n);}
    MyVector(MyVector<T> const& V, int low, int high) {copyFrom(V._elem, low, high);}
    MyVector(MyVector<T> const& V) {copyFrom(V._elem, 0, V._size);}
    //
    ~MyVector(){delete[] _elem;}
    //read only
    int size() const {return _size;}
    int capacity() const {return _capacity;}
    bool empty() const {return _size <= 0;}
    int disordered() const;
    int find(T const& e) const {return find(e, 0, _size);} //find in disordered array
    int find(T const& e, int low, int high) const;
    
    int search(T const& e) const {return (_size <= 0) ? -1 : search(e, 0, _size);}
    int search(T const& e, int low, int high) const; //这样的函数不可以修改成员变量
    
    //read and write
    T& operator[] (int r) const;
    MyVector<T>& operator = (MyVector<T> const&);
    
    T remove(int r);
    int remove(int low, int high);
    
    int insert(int r, T const& e);
    int insert(T const& e) {return insert(_size, e);}
    
    void sort(int low, int high);
    void sort() {sort(0, _size);}
    void unsort(int low, int high);
    void unsort() {unsort(0, _size);}
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    
    //遍历 the purpose is to conduct same operation to all the elements
    void traverse(void (*)(T&));
    template<typename VST>
    void traverse(VST& visit);
    
};