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
#include <map>
#include <random>
#include <vector>
#include <unistd.h>
#include <ctime>

#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater

#include <chrono>
#include <string>

#include <Accelerate/Accelerate.h>

using namespace std;


int main(int argc, const char * argv[]) {
    srand(time(NULL)); //this line should be global, but not in any function
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({0.2,0.3,0.0,0.4});
    std::map<int, int> m;
    for (int n = 0; n < 10000; ++n) {
        ++m[d(gen)];
    }
    for (auto p : m) {
        std::cout << p.first << " generated " << p.second << " times\n";
    }
    
    int data_size = 5;
    vector<float> A(data_size);
    
    float start = 5;
    float end   = 15;
    vDSP_vgen(&start, &end, &A[0], 1, data_size);
    
    for (int i = 0; i < data_size; i++) {
        std::cout << A[i] << " ";
    }
    
    return 0;
}








