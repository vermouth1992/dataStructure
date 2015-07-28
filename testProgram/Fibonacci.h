//
//  Fibonacci.h
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

