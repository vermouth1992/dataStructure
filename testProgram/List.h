//
//  List.h
//  testProgram
//
//  Created by Chi Zhang on 7/13/15.
//  This is a self-paced data structure exercises described in C++
/* Copyright (C) <2015> <Chi Zhang>
 This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 If you have any questions, please email zhan527@usc.edu
*/

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

template <typename T>
void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer; header->pred = NULL;
    trailer->pred = header; trailer->succ = NULL;
    _size = 0;
}

template <typename T>
ListNode<T>* List<T>::operator[](int r) const  //0 <= r < _size
{
    ListNode<T>* p = first();
    while (r > 0) {
        p = p->succ;
        r -= 1;
    }
    return p;
}

//无序查找，往前查找
template <typename T>
ListNode<T>* List<T>::find(const T &e, int n, ListNode<T> *p) const
{
    while (n > 0) {
        p = p->pred;
        if (p->data == e) {
            return p;
        }
        n -= 1;
    }
    return NULL;
}

//插入算法
template <typename T>
ListNode<T>* List<T>::insertAsFirst(const T &e)
{
    _size += 1;
    return header->insertAsSucc(e);
}

template <typename T>
ListNode<T>* List<T>::insertAsLast(const T &e)
{
    _size += 1;
    return trailer->insertAsPred(e);
}

template <typename T>
ListNode<T>* List<T>::insertAfter(ListNode<T> *p, const T &e)
{
    _size += 1;
    return p->insertAsSucc(e);
}

template <typename T>
ListNode<T>* List<T>::insertBefore(ListNode<T> *p, const T &e)
{
    _size += 1;
    return p->insertAsPred(e);
}


//拷贝构造函数
template <typename T>
void List<T>::copyNodes(ListNode<T> *p, int n) //从节点p开始，复制之后n-1项，一共n项
{
    init();
    while (n > 0) {
        insertAsLast(p->data);
        p = p->succ;
        n -= 1;
    }
}

template <typename T>
List<T>::List(ListNode<T>* p, int n)
{
    copyNodes(p, n);
}

template <typename T>
List<T>::List(List<T> const& L)
{
    copyNodes(L.first(), L._size);
}

template <typename T>
List<T>::List(List<T> const& L, int r, int n)  //拷贝L中从r开始的n项
{
    copyNodes(L[r], n);
}

//删除算法
template <typename T>
T List<T>::remove(ListNode<T> *p)
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    _size -= 1;
    delete p;
    return e;
}

//析构
template <typename T>
List<T>::~List()
{
    clear(); delete header; delete trailer;
}

//清除并释放有效节点
template <typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while (_size > 0) {
        remove(first());
    }
    return oldSize;
}

template <typename T>
int List<T>::deduplicate()
{
    if (_size < 2) {
        return 0;
    }
    int oldSize = _size;
    ListNode<T>* p = header; int r = 0;
    while (trailer != p->succ) {
        p = p->succ;
        ListNode<T>* q = find(p->data, r, p);  //从p开始往前找相同的元素
        if (q == NULL) {
            r += 1;
        } else {
            remove(q);
        }
    }
    return oldSize - _size;  //记录长度的变化量
}

//遍历
template <typename T>
void List<T>::traverse(void (*visit)(T &))
{
    ListNode<T>* p = header;
    while (p->succ != trailer) {
        p = p->succ;
        visit(p->data);
    }
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST &visit)
{
    ListNode<T>* p = header;
    while (p->succ != trailer) {
        p = p->succ;
        visit(p->data);
    }
}

template <typename T>
int List<T>::disordered() const
{
    int i = 0;
    ListNode<T>* p = first();
    while (p->succ != trailer) {
        if (p->data > p->succ->data) {  //如果逆序
            i += 1;
        }
        p = p->succ;
    }
    return i;
}

//有序去重
template <typename T>
int List<T>::uniquify()
{
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNode<T>* q = first();
    while (q->succ != trailer) {
        ListNode<T>* p = q;
        q = p->succ;
        if (p->data == q->data) {
            remove(q);
            q = p;
        }
    }
    return oldSize - _size;
}

//有序查找  在p的n个真前驱中找到不大于e的最后者 为了方便插入操作
template <typename T>
ListNode<T>* List<T>::search(const T &e, int n, ListNode<T> *p) const
{
    while (n > 0) {
        p = p->pred;
        if (p->data <= e) {
            break;
        }
        n -= 1;
    }
    return p;
}

//排序算法
template <typename T>  //从p开始对其后n-1排序
void List<T>::sort(ListNode<T> *p, int n)
{
    switch (rand() % 3) {
        case 0:
            cout << "insertion sort" << endl;
            insertionSort(p, n);
            break;
        case 1:
            cout << "selection sort" << endl;
            selectionSort(p, n);
            break;
        default:
            cout << "merge sort" << endl;
            mergeSort(p, n);
            break;
    }
}

template <typename T>
void List<T>::insertionSort(ListNode<T> *p, int n)
{
    for (int i = 0; i < n; i++) {   //从当前的p开始往前已经是顺序
        insertAfter(search(p->data, i, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
void List<T>::selectionSort(ListNode<T> *p, int n)  //从节点p开始，对后面n个元素使用选择排序
{
    ListNode<T>* head = p->pred;
    ListNode<T>* tail = p;
    for (int i = 0; i < n; i++) {
        tail = tail->succ;
    }
    while (n > 1) {  //at least for two elements
        ListNode<T>* max = selectMax(head->succ, n);
        insertBefore(tail, remove(max));   //remove() returns value in the node
        tail = tail->pred;
        n -= 1;
    }
}

template <typename T>
ListNode<T>* List<T>::selectMax(ListNode<T> *p, int n)
{
    ListNode<T>* max = p;
    while (n > 1) {       //除去自己还剩n-1个元素待比较
        if (p->succ->data > max->data) {
            max = p->succ;
        }
        p = p->succ;
        n -= 1;
    }
    return max;
}

template <typename T>  //当前列表从p开始的n个元素与L中从q开始的m个元素归并
void List<T>::merge(ListNode<T> *&p, int n, List<T> &L, ListNode<T> *q, int m)
{
    ListNode<T>* pp = p->pred;   //to keep the original header
    while (m > 0) {
        if (n > 0 && (p->data < q->data)) {
            p = p->succ;
            if (p == q) {
                break;     //in case that L == this
            }
            n -= 1;
        } else {
            q = q->succ;   //we have to keep pointer q
            insertBefore(p, remove(q->pred));   //thus choose to delete q->pred
            m -= 1;
        }
    }
    p = pp->succ;
}

template <typename T>
void List<T>::mergeSort(ListNode<T> *&p, int n)  //对于当前列表从p开始的n个元素排序
{
    if (n < 2) {
        return;
    }
    int m = n >> 1;
    ListNode<T>* q = p;
    for (int i = 0; i < m; i++) {
        q = q->succ;
    }
    mergeSort(p, m);
    mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);
}

template <typename T>
void List<T>::showList()
{
    void (*pFunction)(T &);   //the data parameter has to be & for this application
    pFunction = &show;
    traverse(pFunction);
    cout << endl;
}

#endif /* defined(__testProgram__List__) */
