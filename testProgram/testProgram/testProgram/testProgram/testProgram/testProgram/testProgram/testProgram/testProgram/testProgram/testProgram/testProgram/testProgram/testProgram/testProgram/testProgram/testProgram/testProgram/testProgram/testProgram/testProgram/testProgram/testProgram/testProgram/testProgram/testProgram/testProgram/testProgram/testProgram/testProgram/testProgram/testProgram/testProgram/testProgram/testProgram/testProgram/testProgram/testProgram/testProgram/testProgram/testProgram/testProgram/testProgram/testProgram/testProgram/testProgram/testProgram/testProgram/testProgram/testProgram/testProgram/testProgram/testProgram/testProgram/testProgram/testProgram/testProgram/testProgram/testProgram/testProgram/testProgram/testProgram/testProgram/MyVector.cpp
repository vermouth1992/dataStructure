//
//  MyVector.cpp
//  testProgram
//
//  Created by Chi Zhang on 7/15/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

#include "MyVector.h"
#include "Fibonacci.h"
#include "stdafx.h"

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
    _elem = new T[_capacity * 2];
    for (int i = 0; i < _size; i++) {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
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
    _elem = new T[_capacity / 2];
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
        return binSearch(_elem, e, low, high);
    } else {
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
static int binSearcgTypeC(T* A, T const& e, int low, int high)
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
    switch (rand() % 4) {
        case 1: bubbleSort(low, high); break;
        case 2: mergeSort(low, high); break;
        case 3: heapSort(low, high); break;
        default: quickSort(low, high); break;
    }
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
        while ((j < lb) && (B[j] < C[k])) {
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




