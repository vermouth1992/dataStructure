//
//  Stack.h
//  testProgram
//
//  Created by Chi Zhang on 7/27/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

#ifndef __testProgram__Stack__
#define __testProgram__Stack__

#include <stdio.h>
#include "MyVector.h"

template <typename T>
class MyStack: public MyVector<T> {
public:
    void push(T const& e) {this->insert(this->size(), e);}
    T pop() {return remove(this->size() - 1);}
    T& top() {return (*this)[this->size() - 1];}
};



#endif /* defined(__testProgram__Stack__) */
