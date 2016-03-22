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
    int myints[] = {1, 1, 1, 1};
    vector<int> test_vector (myints, myints + sizeof(myints) / sizeof(int) );
    vector<int> target_index_1;
    target_index_1.push_back(1);
    target_index_1.push_back(1);
/*
    vector<int> target_index_2;
    target_index_2.push_back(1);
    target_index_2.push_back(2);
*/
    vector<vector<int> > target_index;
//    target_index.push_back(target_index_2);
    target_index.push_back(target_index_1);
    vector<vector<int> > result_index = twoSumAll(0, test_vector, 2);
    EXPECT_EQ(target_index, result_index);
}

TEST(sum, DISABLED_threeSum1)
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
    int myints[] = {2, -1, -1, -1};
    vector<int> test_vector (myints, myints + sizeof(myints) / sizeof(int) );
    vector<int> target_index_1 = {-1, -1, 2};
    vector<vector<int>> expected = {target_index_1};
    vector<vector<int>> actual = threeSum(test_vector);
    EXPECT_EQ(expected, actual);
}

TEST(sum, fourSum1)
{
    int myints[] = {1, 0, -1, 0, -2, 2};
    vector<int> test_vector (myints, myints + sizeof(myints) / sizeof(int) );
    vector<vector<int>> expected;
    expected.push_back({-2, -1, 1, 2});
    expected.push_back({-2,  0, 0, 2});
    expected.push_back({-1,  0, 0, 1});
    int target = 0;
    vector<vector<int>> actual = fourSum(test_vector, target);
    EXPECT_EQ(expected, actual);
}

TEST(sum, fourSum2)
{
    int myints[] = {-479,-472,-469,-461,-456,-420,-412,-403,-391,-377,-362,-361,-340,-336,-336,-323,-315,-301,-288,-272,-271,-246,-244,-227,-226,-225,-210,-194,-190,-187,-183,-176,-167,-143,-140,-123,-120,-74,-60,-40,-39,-37,-34,-33,-29,-26,-23,-18,-17,-11,-9,6,8,20,29,35,45,48,58,65,122,124,127,129,145,164,182,198,199,206,207,217,218,226,267,274,278,278,309,322,323,327,350,361,372,376,387,391,434,449,457,465,488};
    vector<int> test_vector (myints, myints + sizeof(myints) / sizeof(int) );
    vector<vector<int>> expected;
    expected.push_back({-1,  0, 0, 1});
    expected.push_back({-2, -1, 1, 2});
    expected.push_back({-2,  0, 0, 2});
    int target = 1979;
    vector<vector<int>> actual = fourSum(test_vector, target);
    EXPECT_EQ(expected, actual);
}


