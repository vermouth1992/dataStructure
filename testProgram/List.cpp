//
//  List.cpp
//  testProgram
//
//  Created by Chi Zhang on 7/23/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

#include "List.h"
#include <iostream>

using namespace std;

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



