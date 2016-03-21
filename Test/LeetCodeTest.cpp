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

TEST(sum, twoSum)
{
    int myints[] = {0, 4, 3, 0};
    vector<int> test_vector (myints, myints + sizeof(myints) / sizeof(int) );
    vector<int> target_index;
    target_index.push_back(0);
    target_index.push_back(3);
    vector<int> result_index = twoSum(test_vector, test_vector[target_index[0]] + test_vector[target_index[1]]);
    EXPECT_EQ(target_index, result_index);
}

TEST(sum, twoSumAll)
{
    int myints[] = {2, 4, 3, 5};
    vector<int> test_vector (myints, myints + sizeof(myints) / sizeof(int) );
    vector<int> target_index_1;
    target_index_1.push_back(0);
    target_index_1.push_back(3);
    vector<int> target_index_2;
    target_index_2.push_back(1);
    target_index_2.push_back(2);
    vector<vector<int> > target_index;
    target_index.push_back(target_index_2);
    target_index.push_back(target_index_1);
    vector<vector<int> > result_index = twoSumAll(0, test_vector, 7);
    EXPECT_EQ(target_index, result_index);
}

TEST(sum, threeSum1)
{
    int myints[] = {7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6};
    vector<int> test_vector (myints, myints + sizeof(myints) / sizeof(int) );
    vector<int> target_index_1 = {-1, 0, 1};
    vector<int> target_index_2 = {-1, -1, 2};
    vector<vector<int>> expected = {target_index_1, target_index_2};
    vector<vector<int>> actual = threeSum(test_vector);
    EXPECT_EQ(expected, actual);
}

TEST(sum, threeSum2)
{
    int myints[] = {0, 0, 0};
    vector<int> test_vector (myints, myints + sizeof(myints) / sizeof(int) );
    vector<int> target_index_1 = {0, 0, 0};
    vector<vector<int>> expected = {target_index_1};
    vector<vector<int>> actual = threeSum(test_vector);
    EXPECT_EQ(expected, actual);
}




