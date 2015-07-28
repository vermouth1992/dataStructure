//
//  Fibonacci.h
//  testProgram
//
//  Created by Chi Zhang on 7/13/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

#ifndef __testProgram__Fibonacci__
#define __testProgram__Fibonacci__

#include <stdio.h>

class Fib {
private:
    int _value;
    int _nextValue;
    
public:
    Fib(int n);
    int getCurrent();
    int getNext();
    int getPrev();
    void next();
    void prev();
    void showValue(); //show the previous, current and next value
};



#endif /* defined(__testProgram__Fibonacci__) */

