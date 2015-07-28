//
//  List.h
//  testProgram
//
//  Created by Chi Zhang on 7/23/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

#ifndef __testProgram__List__
#define __testProgram__List__

#include <stdio.h>
#include "ListNode.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

template <typename T>
class List {
private:
    int _size;
    ListNode<T>* header;
    ListNode<T>* trailer;
    
protected:
    void init();
    int clear();
    void copyNodes(ListNode<T>*, int);
    void merge(ListNode<T>*&, int, List<T>&, ListNode<T>*, int); //有序区间列表归并
    void mergeSort(ListNode<T>*&, int);
    void selectionSort(ListNode<T>*, int);
    void insertionSort(ListNode<T>*, int);
    static void show(T &x) {cout << x << ' ';}
    
public:
    //constructor
    List() {init();}
    List(List<T> const& L);
    List(List<T> const& L, int r, int n);  //复制列表L中从r开始的n项
    List(ListNode<T>* p, int n);  //从节点p开始的n项
    //destructor
    ~List();
    //read only
    int size() const {return _size;}
    bool empty() const {return _size <= 0;}
    ListNode<T>* operator[](int r) const;
    ListNode<T>* first() const {return header->succ;}
    ListNode<T>* last() const {return trailer->pred;}
    bool valid(ListNode<T>* p) {return p && (trailer != p) && (header != p);}  //判断p是否合法
    bool valid(ListNode<T>* p, int r, ListNode<T>* q) {  //p是否是q的前继且距离不超过r
        while (r > 0) {
            if (p == q->pred) {
                return true;
            }
            q = q->pred;
            r -= 1;
        }
        return false;
    }
    bool valid(ListNode<T>* p, ListNode<T>* q, int r) {  //p是否是q的后继且距离不超过r
        while (r > 0) {
            if (p == q->succ) {
                return true;
            }
            q = q->succ;
            r -= 1;
        }
        return false;
    }
    int disordered() const;  //判断是否已经排序
    //search
    ListNode<T>* find(T const& e) const {return find(e, _size, trailer);}
    ListNode<T>* find(T const& e, int n, ListNode<T>* p) const;  //无序区间查找
    ListNode<T>* search(T const& e) const {return search(e, _size, trailer);} //有序区间查找
    ListNode<T>* search(T const& e, int n, ListNode<T>* p) const;
    //select max
    ListNode<T>* selectMax(ListNode<T>* p, int n);  //在p及其n-1个后继中选出最大者
    ListNode<T>* selectMax() {return selectMax(header->succ, _size);}
    
    //read and write
    ListNode<T>* insertAsFirst(T const& e);
    ListNode<T>* insertAsLast(T const& e);
    ListNode<T>* insertBefore(ListNode<T>* p, T const& e);
    ListNode<T>* insertAfter(ListNode<T>* p, T const& e);
    T remove(ListNode<T>* p);
    void merge(List<T>& L) {merge(first(), size(), L, L.first(), L._size);}  //全列表归并
    void sort(ListNode<T>* p, int n);  //列表区间排序
    void sort() {sort(first(), _size);} //列表全排序
    int deduplicate();  //无序去重
    int uniquify(); //有序去重
    //遍历
    void traverse(void (*)(T&));
    template <typename VST>
    void traverse(VST&);
    void showList();
};

#endif /* defined(__testProgram__List__) */
