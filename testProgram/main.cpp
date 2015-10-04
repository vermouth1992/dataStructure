//  main.cpp
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

#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>

#include "Fibonacci.h"
#include "MyVector.h"
#include "List.h"
#include "ListNode.h"
#include "Stack.h"
#include "math.h"
#include "NormalTest.h"
#include "TestForStack.h"
#include "TestForList.h"
#include "TestForVector.h"
#include "labyrinth.h"
#include "Queue.h"
#include "BinNode.h"
#include "BinTree.h"
#include "BinSearchTree.hpp"
#include "Graph.h"
#include "TestForBinTree.hpp"

typedef vector<vector<int> > vec2_int;

using namespace std;

int main(int argc, const char * argv[]) {
//    srand(time(NULL)); //this line should be global, but not in any function
    testBinNode();
    return 0;
}








