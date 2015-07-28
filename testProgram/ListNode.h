//
//  ListNode.h
//  testProgram
//
//  Created by Chi Zhang on 7/13/15.
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

#ifndef __testProgram__ListNode__
#define __testProgram__ListNode__

#include <stdio.h>

template <typename T>
class ListNode {   //双向链表
public:
    //variable
    T data;
    ListNode<T>* pred;  //predecessor pointer
    ListNode<T>* succ;  //successor pointer
    
    //function
    ListNode() {} //special for head and tail since they don't have data
    ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL): data(e), pred(p), succ(s) {} //initializer
    ListNode<T>* insertAsPred(T const& e);
    ListNode<T>* insertAsSucc(T const& e);
};

template <typename T>
ListNode<T>* ListNode<T>::insertAsPred(const T &e)
{
    ListNode<T>* x = new ListNode<T>(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template <typename T>
ListNode<T>* ListNode<T>::insertAsSucc(const T &e)
{
    ListNode<T>* x = new ListNode<T>(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

#endif /* defined(__testProgram__ListNode__) */
