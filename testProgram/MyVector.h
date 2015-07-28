//
//  MyVector.h
//  testProgram
//
//  Created by Chi Zhang on 7/15/15.
//  This is a self-paced data structure exercises described in C++
/* Copyright (C) <2015> <Chi Zhang>
 This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 General Public License as published by the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 License for more details.
 You should have received a copy of the GNU General Public License along with this program; if not, write
 to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 If you have any questions, please email zhan527@usc.edu
 */

#ifndef __testProgram__MyVector__
#define __testProgram__MyVector__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Fibonacci.h"
#include <assert.h>

#define default_capacity 3

using namespace std;

template <typename T>
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
    int size() const {cout << "Current size is " << _size << endl; return _size;}
    int capacity() const {cout << "Current capacity is " << _capacity << endl; return _capacity;}
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
    
    //print all the elements
    void show();
    
    //遍历 the purpose is to conduct same operation to all the elements
    void traverse(void (*)(T&)); //* represents pointer for function, T& is the parameter
    template <typename VST>
    void traverse(VST& visit);
    
};

//
//  MyVector.cpp
//  testProgram
//
//  Created by Chi Zhang on 7/15/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

template<typename T>
static int binSearch(T* A, T const& e, int low, int high);
template<typename T>
static int binSearchTypeA(T* A, T const& e, int low, int high);
template<typename T>
static int binSearchTypeB(T* A, T const& e, int low, int high);
template<typename T>
static int binSearchTypeC(T* A, T const& e, int low, int high);
template<typename T>
static int fibSearch(T* A, T const& e, int low, int high);

template <typename T>
void MyVector<T>::copyFrom(T* const A, int low, int high)
{
    _capacity = 2 * (high - low); //初始化容量是初始元素个数的两倍
    _elem = new T[_capacity];
    _size = 0;
    for (int i = low; i < high; i++) {
        _elem[_size] = A[i];   //copy from [low, high)
        _size += 1;
    }
}

template <typename T>
MyVector<T>& MyVector<T>::operator = (MyVector<T> const& V)
{
    if (_capacity < V.size()) {
        delete[] _elem;
        _elem = new T[V.size() * 2];
    }
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template <typename T>
void MyVector<T>::expand()   //before insert operation, expand() shoud be called
{
    //check before expand capacity
    if (_size < _capacity) {
        return;
    }
    if (_capacity < default_capacity) {
        _capacity = default_capacity;
    }
    T* oldElem = _elem;
    _capacity = _capacity * 2;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

template <typename T>
void MyVector<T>::shrink()   //call after delete operation
{
    if (_capacity < default_capacity) {
        return;
    }
    if (_capacity < _size * 4) { //25%为界
        return;
    }
    T* oldElem = _elem;
    _capacity = _capacity / 2;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

template <typename T>
T& MyVector<T>::operator[](int r) const
{
    return _elem[r];
}

template <typename T>
void MyVector<T>::unsort(int low, int high)
{
    for (int i = high - low; i > 0; i--) {
        std::swap(_elem[i+low-1], _elem[rand()%i+low]);
    }
}

template <typename T>
int MyVector<T>::find(const T &e, int low, int high) const
{
    for (int i = high - 1; i >= low; i--) {
        if (_elem[i] == e) {
            return i;
        }
    }
    return -1;
}

template<typename T>
int MyVector<T>::insert(int r, const T &e)
{
    //throw exception when the position is invalid
    if (r > _size) {
        std::cout << "Invalid position!" << std::endl;
        return -1;
    }
    expand(); //expand _capacity if necessary
    for (int i = _size; i > r; i--) {
        _elem[i] = _elem[i-1];
    }
    _elem[r] = e;
    _size += 1;
    return r;
}

template<typename T>
int MyVector<T>::remove(int low, int high) //remove _elem[low, high)
{
    if (low == high) {
        return 0;
    }
    while (high < _size) {
        _elem[low] = _elem[high];
        low += 1;
        high += 1;
    }
    _size = low;
    shrink();
    return high - low; //return the number deleted
}

template<typename T>
T MyVector<T>::remove(int r)
{
    T e = _elem[r];
    remove(r, r+1);
    return e;
}

template<typename T>
int MyVector<T>::deduplicate()
{
    int oldSize = _size;
    for (int i = 1; i < _size; i++)
    {
        if (find(_elem[i], 0, i) >= 0) //find the same element
        {
            remove(i);
        }
    }
    return oldSize - _size;
}

template<typename T>
void MyVector<T>::traverse(void (*visit)(T &)) //function pointer
{
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);  //do the same operation for all the elements in Vector
    }
}

template<typename T>
template<typename VST>
void MyVector<T>::traverse(VST &visit)  //函数对象机制，可全局修改
{
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

template<typename T>
int MyVector<T>::disordered() const
{
    int count = 0;
    for (int i = 1; i < _size; i++) {
        if (_elem[i-1] > _elem[i]) {
            count += 1;
        }
    }
    return count;
}

template<typename T>
int MyVector<T>::uniquify()  //去除有序向量中重复的元素
{
    int ptr1 = 0, ptr2 = 0;  //two working pointer
    while(ptr2 < _size)
    {
        if (_elem[ptr1] != _elem[ptr2]) {
            ptr1 += 1;                    //left pointer move
            _elem[ptr1] = _elem[ptr2];  //copy the first unequal value right after
        }
        ptr2 += 1;
    }
    _size = ptr1 + 1;
    shrink();  //shrink if necessary
    return ptr2 - ptr1;  //return how many elements has been deleted
}

template<typename T>
int MyVector<T>::search(const T &e, int low, int high) const  //search in an ordered vector
{
    if (rand() % 2) {
        std::cout << "Binary Search" << std::endl;
        return binSearch(_elem, e, low, high);
    } else {
        std::cout << "Fibonacci Search" << std::endl;
        return fibSearch(_elem, e, low, high);
    }
}

//binary search
template<typename T>
static int binSearch(T* A, T const& e, int low, int high)
{
    int temp = rand() % 3;
    if (temp == 0) {
        return binSearchTypeA(A, e, low, high);
    } else if (temp == 1) {
        return binSearchTypeB(A, e, low, high);
    } else {
        return binSearchTypeC(A, e, low, high);
    }
}

//type A binary search
template<typename T>
static int binSearchTypeA(T* A, T const& e, int low, int high)
{
    while (low < high) {
        int middle = (low + high) / 2;
        if (e < A[middle]) {
            high = middle;
        } else if (e > A[middle]) {
            low = middle + 1;
        } else {
            return middle;
        }
    }
    return -1;
}

//type B binary search
template<typename T>
static int binSearchTypeB(T* A, T const& e, int low, int high)
{
    while (high - low > 1) {
        int middle = (low + high) / 2;
        if (e < A[middle]) {      //left search and right search weigh the same
            high = middle;
        } else {
            low = middle;
        }
    }
    if (A[low] == e) {
        return low;
    } else {
        return -1;
    }
}

//type C binary search
template<typename T>
static int binSearchTypeC(T* A, T const& e, int low, int high)
{
    while (high > low) {
        int middle = (low + high) / 2;
        if (e < A[middle]) {
            high = middle;
        } else {
            low = middle + 1;
        }
    }
    low = low - 1;
    if (A[low] == e) {
        return low;
    } else {
        return -1;
    }
}

//Fibonacci search
template<typename T>
static int fibSearch(T* A, T const& e, int low, int high)
{
    Fib searchFib(high - low);
    while (low < high) {
        while (searchFib.getCurrent() > high - low) {
            searchFib.prev();
        }
        int middle = low + searchFib.getCurrent() - 1;
        if (e < A[middle]) {
            high = middle;
        } else if (e > A[middle]) {
            low = middle + 1;
        } else {
            return middle;
        }
    }
    return -1;  //search fail
}

template<typename T>
void MyVector<T>::sort(int low, int high)
{
    switch (rand() % 2) {
        case 0: bubbleSort(low, high); std::cout << "Bubble Sort" << std::endl; break;
        case 1: mergeSort(low, high); std::cout << "Merge Sort" << std::endl; break;
        case 2: heapSort(low, high); std::cout << "Heap Sort" << std::endl; break;
        default: quickSort(low, high); std::cout << "Quick Sort" << std::endl; break;
    }
}

template<typename T>
void MyVector<T>::heapSort(int low, int high)
{
    return;
}

template<typename T>
void MyVector<T>::quickSort(int low, int high)
{
    return;
}

template<typename T>
bool MyVector<T>::bubble(int low, int high)
{
    bool sorted = true;
    while (low < high) {
        if (_elem[low+1] < _elem[low]) {
            sorted = false;
            std::swap(_elem[low+1], _elem[low]);
        }
        low += 1;
    }
    return sorted;
}

template<typename T>
void MyVector<T>::bubbleSort(int low, int high)
{
    while (bubble(low, high) == false) {
        high -= 1;
    }
}

template<typename T>
void MyVector<T>::mergeSort(int low, int high)
{
    if (high - low < 2) {
        return;
    }
    int middle = (low + high) >> 1;
    mergeSort(low, middle);
    mergeSort(middle, high);
    merge(low, middle, high);
}

template<typename T>
void MyVector<T>::merge(int low, int middle, int high)
{
    T* A = _elem + low;
    //open a new space to store the lower half data, pointer B
    int lb = middle - low;  //length of the lower half
    T* B = new T[lb];
    //pointer C points to the higher half of data
    T* C = _elem + middle;
    int lc = high - middle;   //length of the higher half
    for (int i = 0; i < lb; i++) {
        B[i] = A[i];
    }
    int i = 0;
    int j = 0;
    int k = 0;
    while ((j < lb) && (k < lc)) {     //一定要注意区间是左闭右开[low, middle), [middle, high)
        while ((j < lb) && (B[j] <= C[k])) {
            A[i] = B[j];
            i += 1;
            j += 1;
        }
        while ((k < lc) && (C[k] < B[j])) {
            A[i] = C[k];
            i += 1;
            k += 1;
        }
    }
    while (j < lb) {    //we don't have to do with C because if C left elements, they are already there.
        A[i] = B[j];
        i += 1;
        j += 1;
    }
    delete [] B;
}

template<typename T>
void MyVector<T>::show()
{
    for (int i = 0; i < _size; i++) {
        std::cout << _elem[i] << ' ';
    }
    std::cout << std::endl;
}


#endif /* defined(__testProgram__MyVector__) */

