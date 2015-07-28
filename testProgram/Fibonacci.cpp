//
//  Fibonacci.cpp
//  testProgram
//
//  Created by Chi Zhang on 7/13/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

#include "Fibonacci.h"
#include <iostream>

Fib::Fib (int n)
{
    int ptr1 = 0;
    int ptr2 = 1;
    int value = ptr1 + ptr2;
    while (value < n) {
        ptr1 = ptr2;
        ptr2 = value;
        value = ptr1 + ptr2;
    }
    _value = value;
    _nextValue = value + ptr2;
}

int Fib::getCurrent() //the fibonacci start from 0, 1, 1, 2, 3, 5, 8...
{
    return _value;
}

int Fib::getNext()
{
    return _nextValue;
}

int Fib::getPrev()
{
    return _nextValue - _value;
}

void Fib::next()
{
    int tempNextValue = _value + _nextValue;
    _value = _nextValue;
    _nextValue = tempNextValue;
}

void Fib::prev()
{
    int tempPrevValue = _nextValue - _value;
    _nextValue = _value;
    _value = tempPrevValue;
}

void Fib::showValue()
{
    std::cout << getPrev() << " " << getCurrent() << " " << getNext() << std::endl;
}






