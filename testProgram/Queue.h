//
//  Queue.h
//  testProgram
//
//  Created by Chi Zhang on 7/27/15.
//  Copyright (c) 2015 Chi Zhang
/*
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

#ifndef __testProgram__Queue__
#define __testProgram__Queue__

#include <stdio.h>
#include "List.h"

template <typename T>
class Queue: public List<T> {
public:
    void enqueue(T const& e) { this->insertAsFirst(e);}
    T dequeue() { return this->remove(this->last());}
    T& front() { return this->last();}
};

void testForQueue() //堆栈使用vector，队列使用list的好处是方便插入和删除
{
    Queue<int> testQueue;
    testQueue.enqueue(5);
    testQueue.enqueue(10);
    testQueue.showList();
    testQueue.dequeue();
    testQueue.showList();
}


#endif /* defined(__testProgram__Queue__) */
