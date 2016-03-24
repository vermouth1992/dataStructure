//
//  Fibonacci.cpp
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






