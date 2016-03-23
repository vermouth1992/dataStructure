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
#include <ctime>

#include "TestForStack.h"
#include "TestForList.h"
#include "TestForVector.h"
#include "TestForBinTree.hpp"

#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater

using namespace std;

/*
class mycomparison
{
    bool reverse;
public:
    mycomparison(const bool& revparam=false)
    {reverse=revparam;}
    bool operator() (const int& lhs, const int&rhs) const
    {
        if (reverse) return (lhs>rhs);
        else return (lhs<rhs);
    }
};

int main ()
{
    int myints[]= {10,60,50,20};
    
    std::priority_queue<int> first;
    std::priority_queue<int> second (myints,myints+4);
    std::priority_queue<int, std::vector<int>, std::greater<int> >
    third (myints,myints+4);
    // using mycomparison:
    typedef std::priority_queue<int,std::vector<int>,mycomparison> mypq_type;
    
    mypq_type fourth;                       // less-than comparison
    mypq_type fifth (mycomparison(true));   // greater-than comparison
    
    fourth.push(1);
    fourth.push(10);
    fourth.push(5);
    cout << fourth.top();
    return 0;
}
*/

int main(int argc, const char * argv[]) {
//    srand(time(NULL)); //this line should be global, but not in any function
    return 0;
}








