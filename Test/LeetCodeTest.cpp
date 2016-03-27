//
//  LeetCodeTest.cpp
//  testProgram
//
//  Created by Chi Zhang on 3/21/16.
//  Copyright © 2016 University of Southern California. All rights reserved.
//

#include <stdio.h>
#include <queue>          // std::priority_queue
#include <math.h>

#include "LeetCode.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace LeetCode;

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

TEST(sum, DISABLED_fourSum2)
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

TEST(sum, DISABLED_threeSumClosest)
{
    int myints[] = {13,2,0,-14,-20,19,8,-5,-13,-3,20,15,20,5,13,14,-17,-7,12,-6,0,20,-19,-1,-15,-2,8,-2,-9,13,0,-3,-18,-9,-9,-19,17,-14,-19,-4,-16,2,0,9,5,-7,-4,20,18,9,0,12,-1,10,-17,-11,16,-13,-14,-3,0,2,-18,2,8,20,-15,3,-13,-12,-2,-19,11,11,-10,1,1,-10,-2,12,0,17,-19,-7,8,-19,-17,5,-5,-10,8,0,-12,4,19,2,0,12,14,-9,15,7,0,-16,-5,16,-12,0,2,-16,14,18,12,13,5,0,5,6};
    int target = -59;
    vector<int> test_vector (myints, myints + sizeof(myints) / sizeof(int) );
    int expected = -58;
    int actual = threeSumClosest(test_vector, target);
    EXPECT_EQ(expected, actual);
    
    test_vector = {0, 0, 0};
    target = 1;
    expected = 0;
    actual = threeSumClosest(test_vector, target);
    EXPECT_EQ(expected, actual);
    
    test_vector = {1,1,-1,-1,3};
    target = 3;
    expected = 3;
    actual = threeSumClosest(test_vector, target);
    EXPECT_EQ(expected, actual);
}

//helper function
int toInt(ListNode* l)
{
    int unit = 1;
    int result = 0;
    while (l != NULL) {
        result = result + unit * l->val;
        unit *= 10;
        l = l->next;
    }
    return result;
}

TEST(add, addTwoNum)
{
    ListNode* l1 = new ListNode(9);
    l1->next = new ListNode(9);
    l1->next->next = new ListNode(9);
    
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(0);
    l2->next->next = new ListNode(0);
    
    ListNode* expected = new ListNode(0);
    expected->next = new ListNode(0);
    expected->next->next = new ListNode(0);
    expected->next->next->next = new ListNode(1);
    
    ListNode* actual = addTwoNumbers(l1, l2);
    EXPECT_EQ(toInt(expected), toInt(actual));
}


TEST(add, addBinary)
{
    string a = "111";
    string b = "1";
    string expected = "1000";
    string actual = addBinary(a, b);
    EXPECT_EQ(expected, actual);
}

TEST(add, plusOne)
{
    vector<int> test_vector = {9, 9, 9, 9};
    vector<int> actual = plusOne(test_vector);
    vector<int> expected = {1, 0, 0, 0, 0};
    EXPECT_EQ(expected, actual);
}

TEST(add, multiply)
{
    string num1 = "321313021";
    string num2 = "32323820";
    string actual = multiply(num1, num2);
    string expected = "10386064254460220";
    EXPECT_EQ(expected, actual);
}


TEST(merge, mergeTwoSortedList)
{
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(9);
    l1->next->next = new ListNode(10);
    
    ListNode* l2 = new ListNode(2);
    l2->next = new ListNode(8);
    l2->next->next = new ListNode(11);
    
    ListNode* expected = new ListNode(1);
    ListNode* expected_working = expected;
    expected_working->next = new ListNode(2);
    expected_working = expected_working->next;
    expected_working->next = new ListNode(8);
    expected_working = expected_working->next;
    expected_working->next = new ListNode(9);
    expected_working = expected_working->next;
    expected_working->next = new ListNode(10);
    expected_working = expected_working->next;
    expected_working->next = new ListNode(11);
    
    ListNode* actual = mergeTwoLists(l1, l2);
    EXPECT_EQ(toInt(expected), toInt(actual));

}


TEST(merge, PQ)
{
    std::priority_queue<ListNode*, std::vector<ListNode*>, ListNode::LessThanByValue> tester;
    vector<int> a = {1, 10, 9, 5};
    ListNode* temp = vectorToList<int>(a);
    while (temp != NULL) {
        tester.push(temp);
        temp = temp->next;
    }
    EXPECT_EQ(tester.top()->val, 1);
    tester.pop();
    EXPECT_EQ(tester.top()->val, 5);
    tester.pop();
    EXPECT_EQ(tester.top()->val, 9);
    tester.pop();
    EXPECT_EQ(tester.top()->val, 10);
    tester.pop();
}

TEST(merge, mergeKSortedList)
{
    vector<ListNode*> tester;
    
    vector<int> a = {1, 5, 9, 10};
    ListNode* temp_a = vectorToList<int>(a);
    tester.push_back(temp_a);
    
    vector<int> b = {2};
    ListNode* temp_b = vectorToList<int>(b);
    tester.push_back(temp_b);
    
    vector<int> c = {0, 3, 4, 9, 20};
    ListNode* temp_c = vectorToList<int>(c);
    tester.push_back(temp_c);
    
    ListNode* actual = mergeKLists(tester);
    
    vector<int> expected_vector = {0, 1, 2, 3, 4, 5, 9, 9, 10, 20};
    ListNode* expected = vectorToList<int>(expected_vector);
    
    EXPECT_EQ(toInt(actual), toInt(expected));
}

TEST(merge, mergeSortedArray)
{
    vector<int> a = {0, 3, 4, 5, 7};
    vector<int> b = {2, 6, 8, 10};
    merge(a, (int)a.size(), b, (int)b.size());
    vector<int> expected = {0, 2, 3, 4, 5, 6, 7, 8, 10};
    EXPECT_EQ(expected, a);
}

TEST(math, myAtoi)
{
    int actual, expected;
    string tester;
    tester = "-1";
    actual = myAtoi(tester);
    expected = -1;
    EXPECT_EQ(expected, actual);
    
    tester = "2147483648";
    actual = myAtoi(tester);
    expected = 2147483647;
    EXPECT_EQ(expected, actual);
    
    tester = "    10522545459";
    actual = myAtoi(tester);
    expected = 2147483647;
    EXPECT_EQ(expected, actual);
}

TEST(math, mySqrt)
{
    EXPECT_EQ(0, mySqrt(0));
    EXPECT_EQ(1, mySqrt(1));
    EXPECT_EQ(1, mySqrt(3));
    EXPECT_EQ(2, mySqrt(4));
    EXPECT_EQ(2, mySqrt(5));
    EXPECT_EQ((int)sqrt(2147395599), mySqrt(2147395599));
    EXPECT_EQ((int)sqrt(2147483647), mySqrt(2147483647));
}

TEST(math, isNumber)
{
    EXPECT_TRUE(isNumber("-.02e-2"));
    EXPECT_TRUE(isNumber("+.02e+2"));
    EXPECT_TRUE(!isNumber("-.e-2"));
    EXPECT_TRUE(!isNumber("."));
    EXPECT_TRUE(isNumber("3."));
    EXPECT_TRUE(!isNumber("3.."));
}

TEST(math, countBits)
{
    vector<int> actual = countBits(8);
    vector<int> expected = {0,1,1,2,1,2,2,3,1};
    EXPECT_EQ(expected, actual);
}

TEST(string, lengthOfLongestSubstring)
{
    string s = "abcabcbb";
    EXPECT_EQ(3, lengthOfLongestSubstring(s));
    s = "bbbbb";
    EXPECT_EQ(1, lengthOfLongestSubstring(s));
    s = "12oqwer";
    EXPECT_EQ(s.size(), lengthOfLongestSubstring(s));
    s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCD";
    EXPECT_EQ(95, lengthOfLongestSubstring(s));
    s = "aabopiuy";
    EXPECT_EQ(7, lengthOfLongestSubstring(s));
    EXPECT_EQ(3, lengthOfLongestSubstring("dvdf"));
    EXPECT_EQ(2, lengthOfLongestSubstring("abba"));
}

TEST(array, minPathSum)
{
    vector<vector<int>> grid = {{0, 0, 1}, {0, 1, 2}};
    int actual = minPathSum(grid);
    EXPECT_EQ(3, actual);
}

TEST(array, uniquePaths)
{
    Solution_62 sol;
    EXPECT_EQ(120, sol.uniquePaths(8, 4));
    EXPECT_EQ(120, sol.uniquePaths(4, 8));
    EXPECT_EQ(1, sol.uniquePaths(1, 2));
    EXPECT_EQ(1, sol.uniquePaths(2, 1));
    EXPECT_EQ(48620, sol.uniquePaths(10, 10));
    EXPECT_EQ(1916797311, sol.uniquePaths(51, 9));
}

TEST(array, uniquePaths2)
{
    Solution_63 sol;
    vector<vector<int>> obstacles = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    EXPECT_EQ(2, sol.uniquePathsWithObstacles(obstacles));
    obstacles = {{0}};
    EXPECT_EQ(1, sol.uniquePathsWithObstacles(obstacles));
    obstacles = {{0, 1}};
    EXPECT_EQ(0, sol.uniquePathsWithObstacles(obstacles));
}



