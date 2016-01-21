//
//  NormalTest.cpp
//  testProgram
//
//  Created by Chi Zhang on 1/20/16.
//  Copyright © 2016 University of Southern California. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "NormalTest.h"
using namespace std;

int compareUnsignedInt(const void *a, const void *b) {
    if (*(unsigned int*)a < *(unsigned int*)b) {
        return -1;
    } else if (*(unsigned int*)a == *(unsigned int*)b) {
        return 0;
    } else {
        return 1;
    }
}

TEST (quickSort, array)
{
    std::srand((uint)std::time(0));
    size_t length = 10;
    uint *a = new uint[length];
    //uint *a_copy = new uint[length];
    for (int i = 0; i < length; i++) {
        a[i] = (uint) (std::rand());
        //    a_copy[i] = a[i];
    }
    qsort(a, length, sizeof(uint), compareUnsignedInt);
    for (int i = 0; i < length - 1; i++) {
        EXPECT_TRUE(a[i] <= a[i+1]);
    }
}


TEST (quickSort, Addition)
{
    // equal to 20
    EXPECT_EQ(addition(10, 10), 20);
    
    EXPECT_EQ(addition(20, 10), 30);
    
    // not equal to 20
    EXPECT_NE(addition(10, 10), -20);
}

