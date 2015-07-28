//
//  ListNode.cpp
//  testProgram
//
//  Created by Chi Zhang on 7/23/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

#include "ListNode.h"

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
