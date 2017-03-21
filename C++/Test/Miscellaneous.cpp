//
//  Miscellaneous.cpp
//  dataStructure
//
//  Created by Chi Zhang on 6/17/16.
//  Copyright © 2016 University of Southern California. All rights reserved.
//

#include <stdio.h>

#include "gtest/gtest.h"

// test the 2D array in memory
TEST(arrayTest, twoDLayout)
{
    int twoDimensionData[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    int *p = (int *) twoDimensionData;
    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(twoDimensionData[i / 2][i % 2], *(p + i));
    }
}
