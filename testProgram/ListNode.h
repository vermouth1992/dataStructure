//
//  ListNode.h
//  testProgram
//
//  Created by Chi Zhang on 7/23/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

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



#endif /* defined(__testProgram__ListNode__) */
