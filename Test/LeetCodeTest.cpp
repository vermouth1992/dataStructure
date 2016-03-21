//
//  LeetCodeTest.cpp
//  testProgram
//
//  Created by Chi Zhang on 3/21/16.
//  Copyright © 2016 University of Southern California. All rights reserved.
//

#include <stdio.h>
#include "LeetCode.hpp"
#include "gtest/gtest.h"

using namespace std;

TEST(twoSum, basic_test)
{
    int myints[] = {2,16,29,77};
    vector<int> test_vector (myints, myints + sizeof(myints) / sizeof(int) );
    vector<int> target_index;
    target_index.push_back(1);
    target_index.push_back(3);
    vector<int> result_index = twoSum(test_vector, target_index[0] + target_index[1]);
    EXPECT_EQ(target_index, result_index);
}
