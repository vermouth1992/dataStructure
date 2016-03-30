//
//  LeetCode.hpp
//  testProgram
//
//  Created by Chi Zhang on 3/21/16.
//  Copyright © 2016 University of Southern California. All rights reserved.
//

#ifndef LeetCode_h
#define LeetCode_h

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <stdio.h>
#include <stdlib.h>

namespace LeetCode {
    using namespace std;
    
    // common interfaces
    // singly-linked list
    class ListNode {
    public:
        struct LessThanByValue {
            // why can't we pass by reference here
            bool operator () (const ListNode* lhs, const ListNode* rhs) const {
                return (lhs->val > rhs->val);
            }
        };
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    
    template <typename T>
    ListNode* vectorToList(vector<T>& v) {
        if (v.empty()) {
            return NULL;
        }
        ListNode* result = new ListNode(v[0]);
        ListNode* working_ptr = result;
        for (int i = 1; i < v.size(); i++) {
            working_ptr->next = new ListNode(v[i]);
            working_ptr = working_ptr->next;
        }
        return result;
    }
    
    
    // 1. two sum
    /* using map, total time complexity is O(n) + O(n) = O(n) */
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, int> nums_map;
        // O(n) to iterate
        vector<int> result;
        std::map<int, int>::iterator map_it;
        for (int i = 0; i < nums.size(); i++) {
            map_it = nums_map.find(target - nums[i]);
            if (map_it != nums_map.end()) {
                return {map_it->second, i};
            }
            nums_map[nums[i]] = i;
        }
        return result;
    }
    
    // 2. Add Two Numbers
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == NULL) {
            return l2;
        } else if (l2 == NULL) {
            return l1;
        }
        ListNode* ptr1 = l1;
        ListNode* ptr2 = l2;
        int unit = (ptr1->val + ptr2->val) % 10;
        int overflow = (ptr1->val + ptr2->val) / 10;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        ListNode* result = new ListNode(unit);
        ListNode* result_ptr = result;
        int digit;
        // common part
        while (ptr1 != NULL && ptr2 != NULL) {
            digit = ptr1->val + ptr2->val + overflow;
            unit = digit % 10;
            overflow = digit / 10;
            result_ptr->next = new ListNode(unit);
            
            result_ptr = result_ptr->next;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        // ptr1 is NULL
        if (ptr1 == NULL) {
            if (ptr2 != NULL) {
                while (ptr2 != NULL) {
                    digit = ptr2->val + overflow;
                    unit = digit % 10;
                    overflow = digit / 10;
                    result_ptr->next = new ListNode(unit);
                    result_ptr = result_ptr->next;
                    ptr2 = ptr2->next;
                }
            }
        } else {  //ptr2 is NULL
            if (ptr1 != NULL) {
                while (ptr1 != NULL) {
                    digit = ptr1->val + overflow;
                    unit = digit % 10;
                    overflow = digit / 10;
                    result_ptr->next = new ListNode(unit);
                    result_ptr = result_ptr->next;
                    ptr1 = ptr1->next;
                }
            }
        }
        if (overflow == 1) {
            result_ptr->next = new ListNode(1);
        }
        return result;
    }
    
    // 3. Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(string s) {
        // since it is a char hash table, we can actually use a vector indexing from 0-255
        std::map<char, int> char_dictionary;
        int curr_length = 0;
        int start = 0;
        int maxLength = 0;
        std::map<char,int>::iterator it;
        for (int curr_index = 0; curr_index < s.size(); curr_index++) {
            char curr_char = s[curr_index];
            // if curr_char is not in the map
            it = char_dictionary.find(curr_char);
            if (it == char_dictionary.end()) {
                char_dictionary[curr_char] = curr_index;  // the first time a char occurs
            } else {
                int curr_mapping = it->second;
                if (curr_mapping >= start) {  // if curr_char is in the current substring
                    curr_length = curr_index - start;
                    maxLength = max(maxLength, curr_length);
                    start = curr_mapping + 1;
                    it->second = curr_index;
                } else { // curr_char is in the dict but not in the substring
                    it->second = curr_index;   // renew the index to be
                }
            }
        }
        curr_length = (int)s.size() - start;
        return max(curr_length, maxLength);
    }
    
    // 4. Median of Two Sorted Arrays
    // helper function
/*
    double findMedianSortedArraysIndex(vector<int>& nums1, int start1, int end1, vector<int>& nums2, int start2, int end2) {
        int mid1 = end1 - start1;
        int mid2 = end2 - start2;
        // base case
        if (condition) {
            statements
        }
    }
    
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        return findMedianSortedArraysIndex(nums1, 0, (int)nums1.size(), nums2, 0, (int)nums2.size());
    }
*/
    // 8. String to Integer (atoi)
    enum atoiState {ATOI_IDLE, NEGATIVE, POSITIVE};
    
    int myAtoi(string str) {
        atoiState curr_state = ATOI_IDLE;
        int result = 0;
        int num_digits = 0;
        for (int i = 0; i < str.size(); i++) {
            switch (curr_state) {
                case ATOI_IDLE:
                    if (str[i] != ' ' && str[i] != '-' && str[i] != '+' && (str[i] < '0' || str[i] > '9')) {
                        return result;
                    } else if (str[i] == '+') {
                        curr_state = POSITIVE;
                    } else if (str[i] == '-') {
                        curr_state = NEGATIVE;
                    } else if (str[i] >= '0' && str[i] <= '9') {
                        curr_state = POSITIVE;
                        result = str[i] - '0';
                        num_digits += 1;
                    }
                    break;
                case NEGATIVE:
                    if (str[i] >= '0' && str[i] <= '9') {
                        result = result * 10 + str[i] - '0';
                        if (num_digits == 10 || result < 0) {
                            return INT_MIN;
                        }
                        num_digits += 1;
                    } else {
                        return -result;
                    }
                    break;
                case POSITIVE:
                    if (str[i] >= '0' && str[i] <= '9') {
                        result = result * 10 + str[i] - '0';
                        if (num_digits == 10 || result < 0) {
                            return INT_MAX;
                        }
                        num_digits += 1;
                    } else {
                        return result;
                    }
                    break;
                default:
                    break;
            }
        }
        if (curr_state == POSITIVE) {
            return result;
        } else {
            return -result;
        }
        
    }
    
    // 13. Roman to Integer, Input is guaranteed to be within the range from 1 to 3999.
    int romanToInt(string s) {
        
    }
    
    // 14. Longest Common Prefix
    string longestCommonPrefix(vector<string>& strs) {
        string commonPrefix = "";
        if (strs.size() == 0) {
            return commonPrefix;
        }
        for (int i = 0; i < strs[0].size(); i++) {
            char possibleCommonChar = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (i >= strs[j].size() || strs[j][i] != possibleCommonChar) {
                    return commonPrefix;
                }
            }
            commonPrefix += possibleCommonChar;
        }
        return commonPrefix;
    }
    
    
    // #15, 3Sum
    /* helper function, the output two-d vector should be a set, the nums should be in sorted order
     * We don't need to use map in this implementation
     */
    vector<vector<int> > twoSumAll(int starting, vector<int>& nums, int target) {
        vector<vector<int> > result;
        int front_ptr = starting;
        int back_ptr = (int)nums.size() - 1;
        while (front_ptr < back_ptr) {
            if (nums[front_ptr] + nums[back_ptr] == target) {
                vector<int> oneResult = {nums[front_ptr], nums[back_ptr]};
                if (!result.empty() && oneResult == result[result.size()-1]) {
                    front_ptr += 1;
                    back_ptr -= 1;
                } else {
                    result.push_back(oneResult);
                    front_ptr += 1;
                    back_ptr -= 1;
                }
            } else if (nums[front_ptr] + nums[back_ptr] < target) {
                front_ptr += 1;
            } else {
                back_ptr -= 1;
            }
        }
        return result;
    }
    
    /* Although the time complexity is O(n^2), but in LeetCode, the runtime is too long */
    vector<vector<int>> threeSum(vector<int>& nums) {
        // sort the array
        std::sort(nums.begin(), nums.end());
        vector<vector<int> > result;
        vector<vector<int> > twoSumResult;
        for (int i = 0; i < nums.size(); i++) {
            // step over duplicate elements
            if (i != 0 && nums[i] == nums[i-1]) {
                continue;
            }
            twoSumResult = twoSumAll(i + 1, nums, -nums[i]);
            for (int j = 0; j < twoSumResult.size(); j++) {
                vector<int> singleTwoResult = twoSumResult[j];
                singleTwoResult.insert(singleTwoResult.begin(), nums[i]);
                result.push_back(singleTwoResult);
            }
        }
        return result;
    }
    
    // 16. 3Sum Closest
    int twoSumClosest(int starting, vector<int>& nums, int target) {
        int front_ptr = starting;
        int back_ptr = (int)nums.size() - 1;
        int closestNum = nums[front_ptr] + nums[back_ptr];
        while (front_ptr < back_ptr - 1) {
            break;
        }
        return closestNum;
    }
    
    
    int threeSumClosest(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int closestNum = nums[0] + nums[1] + nums[nums.size() - 1];
        for (int i = 0; i < nums.size() - 2; i++) {
            if (i != 0 && nums[i] == nums[i-1]) {
                continue;
            }
            int closestNumCandidate = twoSumClosest(i + 1, nums, target - nums[i]) + nums[i];
            if (abs(closestNumCandidate - target) <= abs(closestNum - target)) {
                closestNum = closestNumCandidate;
            }
        }
        return closestNum;
    }
    
    
    // #18, fourSum
    vector<vector<int>> threeSumAll(int starting, vector<int>& nums, int target) {
        vector<vector<int> > result;
        vector<vector<int> > twoSumResult;
        for (int i = starting; i < nums.size(); i++) {
            // step over duplicate elements
            if (i != starting && nums[i] == nums[i-1]) {
                continue;
            }
            twoSumResult = twoSumAll(i + 1, nums, target - nums[i]);
            for (int j = 0; j < twoSumResult.size(); j++) {
                vector<int> singleTwoResult = twoSumResult[j];
                singleTwoResult.insert(singleTwoResult.begin(), nums[i]);
                result.push_back(singleTwoResult);
            }
        }
        return result;
    }
    
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        // sort the array
        std::sort(nums.begin(), nums.end());
        vector<vector<int> > result;
        vector<vector<int> > threeSumResult;
        for (int i = 0; i < nums.size() - 2; i++) {
            // step over duplicate elements
            if (i != 0 && nums[i] == nums[i-1]) {
                continue;
            }
            threeSumResult = threeSumAll(i + 1, nums, target - nums[i]);
            for (int j = 0; j < threeSumResult.size(); j++) {
                vector<int> singleThreeResult = threeSumResult[j];
                singleThreeResult.insert(singleThreeResult.begin(), nums[i]);
                result.push_back(singleThreeResult);
            }
        }
        return result;
    }
    
    // 21. Merge Two Sorted Lists
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == NULL) {
            return l2;
        } else if (l2 == NULL) {
            return l1;
        }
        ListNode* result;
        ListNode* ptr1 = l1;
        ListNode* ptr2 = l2;
        
        if (l1->val < l2->val) {
            result = l1;
            ptr1 = ptr1->next;
        } else {
            result = l2;
            ptr2 = ptr2->next;
        }
        ListNode* result_ptr = result;
        while (ptr1 != NULL && ptr2 != NULL) {
            if (ptr1->val < ptr2->val) {
                result_ptr->next = ptr1;
                ptr1 = ptr1->next;
            } else {
                result_ptr->next = ptr2;
                ptr2 = ptr2->next;
            }
            result_ptr = result_ptr->next;
        }
        if (ptr1 == NULL) {
            result_ptr->next = ptr2;
        } else{
            result_ptr->next = ptr1;
        }
        
        return result;
    }
    
    // 23. Merge k Sorted Lists
    // minHeap comparator class
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // construction a PQ
        std::priority_queue<ListNode*, std::vector<ListNode*>, ListNode::LessThanByValue> helper_PQ;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != NULL) {
                helper_PQ.push(lists[i]);
            }
        }
        // if all the ListNode are NULL
        if (helper_PQ.empty()) {
            return NULL;
        }
        ListNode* result = helper_PQ.top();
        ListNode* working_ptr = result;
        helper_PQ.pop();
        if (working_ptr->next != NULL) {
            helper_PQ.push(working_ptr->next);
        }
        
        while (!helper_PQ.empty()) {
            // repoint the current next
            working_ptr->next = helper_PQ.top();
            // move working pointer
            working_ptr = working_ptr->next;
            helper_PQ.pop();
            if (working_ptr->next != NULL) {
                helper_PQ.push(working_ptr->next);
            }
        }
        
        return result;
    }
    
// LeetCode 30 Start
    
    // 36. Valid Sudoku
    bool checkSubBox(int m, int n, vector<vector<char>>& board) {
        vector<bool> occurs(9, false);
        for (int i = m; i < m + 3; i++) {
            for (int j = n; j < n + 3; j++) {
                if (board[i][j] == '.') {
                    continue;
                } else if (occurs[board[i][j] - '0'] == false) {
                    occurs[board[i][j] - '0'] = true;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool isValidSudoku(vector<vector<char>>& board) {
        // check board size
        if (board.size() != 9 || board[0].size() != 9) {
            return false;
        }
        // check row
        for (int i = 0; i < 9; i++) {
            vector<char> currLine = board[i];
            vector<bool> occurs(9, false);
            for (int j = 0; j < 9; j++) {
                if (currLine[j] == '.') {
                    continue;
                } else if (occurs[currLine[j] - '0'] == false) {
                    occurs[currLine[j] - '0'] = true;
                } else {
                    return false;
                }
            }
        }
        // check column
        for (int i = 0; i < 9; i++) {
            vector<bool> occurs(9, false);
            for (int j = 0; j < 9; j++) {
                if (board[j][i] == '.') {
                    continue;
                } else if (occurs[board[j][i] - '0'] == false) {
                    occurs[board[j][i] - '0'] = true;
                } else {
                    return false;
                }
            }
        }
        // check sub-box
        for (int i = 0; i < 7; i+=3) {
            for (int j = 0; j < 7; j+=3) {
                if (checkSubBox(i, j, board) == false) {
                    return false;
                }
            }
        }
        return true;
    }
    
// LeetCode 40 Start
    
    // 43. Multiply Strings
    //helper function
    string oneDigitMultiply(string num, char digit) {
        // speed up for simple case
        if (digit == '0') {
            return "0";
        } else if (digit == '1') {
            return num;
        }
        
        string result;
        int overflow = 0;
        int int_digit = digit - '0';
        int curr_num_digit, unit;
        for (int i = (int)num.size() - 1; i >= 0; i--) {
            if (num[i] == '0') {
                unit = overflow;
                overflow = 0;
            } else {
                curr_num_digit = num[i] - '0';
                unit = (curr_num_digit * int_digit + overflow) % 10;
                overflow = (curr_num_digit * int_digit + overflow) / 10;
            }
            result.insert(result.begin(), unit + '0');
        }
        if (overflow != 0) {
            result.insert(result.begin(), overflow + '0');
        }
        return result;
    }
    
    string add(string a, string b, int base) {
        if (a.size() == 0) {
            return b;
        } else if (b.size() == 0) {
            return a;
        }
        int ptr_a = (int)a.size() - 1;
        int ptr_b = (int)b.size() - 1;
        int overflow = 0;
        int unit, digit;
        string result;
        while (ptr_a >= 0 && ptr_b >= 0) {
            unit = (a[ptr_a] - '0') + (b[ptr_b] - '0') + overflow;
            overflow = unit / base;
            digit = unit % base;
            result.insert(result.begin(), digit + '0');
            ptr_a -= 1;
            ptr_b -= 1;
        }
        if (ptr_a == -1) {
            if (ptr_b != -1) {
                while (ptr_b >= 0) {
                    unit = (b[ptr_b] - '0') + overflow;
                    overflow = unit / base;
                    digit = unit % base;
                    result.insert(result.begin(), digit + '0');
                    ptr_b -= 1;
                }
            }
        } else {
            if (ptr_a != -1) {
                while (ptr_a >= 0) {
                    unit = (a[ptr_a] - '0') + overflow;
                    overflow = unit / base;
                    digit = unit % base;
                    result.insert(result.begin(), digit + '0');
                    ptr_a -= 1;
                }
            }
        }
        if (overflow == 1) {
            result.insert(result.begin(), '1');
        }
        return result;
    }
    
    
    string multiply(string num1, string num2) {
        // speed up for simple case
        if (num1 == "0" || num2 == "0") {
            return "0";
        } else if (num1 == "1") {
            return num2;
        } else if (num2 == "1") {
            return num1;
        }
        vector<string> temp_result;
        string result = "0";
        for (int i = 0; i < (int)num2.size(); i++) {
            string oneDigitResult = oneDigitMultiply(num1, num2[i]);
            for (int j = 1; j < (int)num2.size() - i; j++) {
                oneDigitResult.push_back('0');
            }
            temp_result.push_back(oneDigitResult);
        }
        for (int i = 0; i < temp_result.size(); i++) {
            result = add(result, temp_result[i], 10);
        }
        return result;
    }
    
    // 62. Unique Paths
    // we should have memoization for practice, however, the fastest way is to use iteration
    class Solution_62 {
    private:
        std::map<vector<int>, int> cache;
    public:
        int uniquePaths(int m, int n) {
            vector<int> key = {m, n};
            std::map<vector<int>, int>::iterator it = cache.find(key);
            // result already in the cache
            if (it != cache.end()) {
                return it->second;
            }
            if (m - 1 == 0 || n - 1 == 0) {
                cache[key] = 1;
                return 1;
            }
            
            int right = uniquePaths(m - 1, n);
            vector<int> right_key = {m - 1, n};
            cache[right_key] = right;
            
            int down = uniquePaths(m, n - 1);
            vector<int> down_key = {m, n - 1};
            cache[down_key] = down;
            int result = right + down;
            cache[key] = result;
            return result;
        }
    };
    
    // 63. Unique Paths II
    class Solution_63 {
    private:
        std::map<vector<int>, int> cache;
        
        int uniquePathsWithObstacles_private(vector<vector<int>>& obstacleGrid, int m, int n) {
            vector<int> key = {m, n};
            std::map<vector<int>, int>::iterator it = cache.find(key);
            // result already in the cache
            int result;
            if (it != cache.end()) {
                return it->second;
            }
            if (obstacleGrid[m][n] == 1) {
                cache[key] = 0;
                return 0;
            }
            if (m == 0 && n == 0) {
                cache[key] = 1;
                return 1;
            } else if (m == 0) {
                result = uniquePathsWithObstacles_private(obstacleGrid, m, n - 1);
                cache[key] = result;
                return result;
            } else if (n == 0) {
                result = uniquePathsWithObstacles_private(obstacleGrid, m - 1, n);
                cache[key] = result;
                return result;
            }
            
            int right = uniquePathsWithObstacles_private(obstacleGrid, m - 1, n);
            vector<int> right_key = {m - 1, n};
            cache[right_key] = right;
            
            int down = uniquePathsWithObstacles_private(obstacleGrid, m, n - 1);
            vector<int> down_key = {m, n - 1};
            cache[down_key] = down;
            result = right + down;
            cache[key] = result;
            return result;
        }
    public:
        int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
            cache.clear();
            int m = (int)obstacleGrid.size() - 1;
            int n = (int)obstacleGrid[0].size() - 1;
            return uniquePathsWithObstacles_private(obstacleGrid, m, n);
        }
    };
    
    // 64. Minimum Path Sum, use Uniform Cost Search
    struct minPathState {
        int x;
        int y;
        int currSum;
        minPathState(int _x, int _y, int sum) : x(_x), y(_y), currSum(sum) {}
    };
    
    struct ComparePathState {
        bool operator () (const minPathState* lhs, const minPathState* rhs) const {
            return (lhs->currSum > rhs->currSum);
        }
    };
    
    // get next state, return a vector contains pointer to the next state
    vector<minPathState*> getSuccessor(const minPathState* currState, const vector<vector<int>> &grid, const vector<vector<int>> &expanded) {
        vector<minPathState*> nextState;
        int m = (int)grid[0].size();
        int n = (int)grid.size();
        int currX = currState->x;
        int currY = currState->y;
        
        if (currX == n - 1) {
            int leftSum = 0;
            for (int i = currY + 1; i < m; i++) {
                leftSum += grid[currX][i];
            }
            minPathState* state = new minPathState(n - 1, m - 1, currState->currSum + leftSum);
            nextState.push_back(state);
            return nextState;
        } else if (currY == m - 1) {
            int leftSum = 0;
            for (int i = currX + 1; i < n; i++) {
                leftSum += grid[i][currY];
            }
            minPathState* state = new minPathState(n - 1, m - 1, currState->currSum + leftSum);
            nextState.push_back(state);
            return nextState;
        } else {
            if (expanded[currX + 1][currY] != -1) {
                minPathState* state_down = new minPathState(currX + 1, currY, currState->currSum + grid[currX + 1][currY]);
                nextState.push_back(state_down);
            }
            if (expanded[currX][currY + 1] != -1) {
                minPathState* state_right = new minPathState(currX, currY + 1, currState->currSum + grid[currX][currY + 1]);
                nextState.push_back(state_right);
            }
        }
        return nextState;
    }
    
    bool isGoalState(const minPathState* currState, const vector<vector<int>> &grid) {
        int m = (int)grid[0].size();
        int n = (int)grid.size();
        return currState->x == n - 1 && currState->y == m - 1;
    }
    
    int minPathSum(vector<vector<int>>& grid) {
        // remember to delete expanded state to release memory
        std::priority_queue<minPathState*, vector<minPathState*>, ComparePathState> helper_PQ;
        minPathState* initState = new minPathState(0, 0, grid[0][0]);
        helper_PQ.push(initState);
        int result = 0;
        // need to keep track of already expanded points
        vector<vector<int>> expanded(grid);
        
        while (!helper_PQ.empty()) {
            minPathState* topState = helper_PQ.top();
            helper_PQ.pop();
            expanded[topState->x][topState->y] = -1;  // mark as expanded
            if (isGoalState(topState, grid)) {
                result = topState->currSum;
                // clear PQ, prevent memory leakage
                while (!helper_PQ.empty()) {
                    minPathState* toDelete = helper_PQ.top();
                    helper_PQ.pop();
                    delete toDelete;
                }
                return result;
            }
            vector<minPathState*> nextStateVector = getSuccessor(topState, grid, expanded);
            for (minPathState* state : nextStateVector) {
                helper_PQ.push(state);
            }
            delete topState;
        }
        return result;
    }
    
    // 65. Valid Number
    // using FSM
    enum numState {NUM_IDLE, INT_P, INT, DEC_P, DEC, SCI, NUM_P, NUM, END};
    
    bool isNumber(string s) {
        numState curr_state = NUM_IDLE;
        for (int i = 0; i < s.size(); i++) {
            char curr_char = s[i];
            switch (curr_state) {
                case NUM_IDLE:
                    if (curr_char == ' ') {
                        continue;
                    } else if (curr_char == '+' || curr_char == '-') {
                        curr_state = INT_P;
                    } else if (isdigit(curr_char)) {
                        curr_state = INT;
                    } else if (curr_char == '.') {
                        curr_state = DEC_P;
                    } else {
                        return false;
                    }
                    break;
                    
                case INT_P:
                    if (curr_char == '.') {
                        curr_state = DEC_P;
                    } else if (isdigit(curr_char)) {
                        curr_state = INT;
                    } else {
                        return false;
                    }
                    break;
                    
                case INT:
                    if (isdigit(curr_char)) {
                        continue;
                    } else if (curr_char == ' ') {
                        curr_state = END;
                    } else if (curr_char == '.') {
                        curr_state = DEC;
                    } else if (curr_char == 'e') {
                        curr_state = SCI;
                    } else {
                        return false;
                    }
                    break;
                    
                case DEC_P:
                    if (isdigit(curr_char)) {
                        curr_state = DEC;
                    } else {
                        return false;
                    }
                    break;
                    
                case DEC:
                    if (curr_char == ' ') {
                        curr_state = END;
                    } else if (isdigit(curr_char)) {
                        continue;
                    } else if (curr_char == 'e') {
                        curr_state = SCI;
                    } else {
                        return false;
                    }
                    break;
                    
                case SCI:
                    if (curr_char == '+' || curr_char == '-') {
                        curr_state = NUM_P;
                    } else if (isdigit(curr_char)) {
                        curr_state = NUM;
                    } else {
                        return false;
                    }
                    break;
                    
                case NUM_P:
                    if (isdigit(curr_char)) {
                        curr_state = NUM;
                    } else {
                        return false;
                    }
                    break;
                    
                case NUM:
                    if (isdigit(curr_char)) {
                        continue;
                    } else if (curr_char == ' ') {
                        curr_state = END;
                    } else {
                        return false;
                    }
                    break;
                    
                case END:
                    if (curr_char != ' ') {
                        return false;
                    }
                    break;
                    
                default:
                    break;
            }
        }
        if (curr_state == NUM_IDLE || curr_state == INT_P || curr_state == DEC_P || curr_state == SCI || curr_state == NUM_P) {
            return false;
        }
        return true;
    }
    
    
    // 66. Plus One
    vector<int> plusOne(vector<int>& digits) {
        int overflow = 0;
        for (int i = (int)digits.size() - 1; i >= 0; i--) {
            overflow = (digits[i] + 1) / 10;
            digits[i] = (digits[i] + 1) % 10;
            if (overflow == 0) {
                break;
            }
        }
        if (overflow == 1) {
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
    
    
    // 67. Add Binary
    string addBinary(string a, string b) {
        return add(a, b, 2);
    }
    
    // 69. Sqrt(x)
    int mySqrt(int x) {
        if (x < 0) {
            return INT_MIN;
        } else if (x == 0) {
            return 0;
        } else if (x == 2147483647) {
            return 46340;
        }
        // include low, but exclude high
        int low = 1;
        int high = x + 1;
        // solve overflow issue
        if (high > 46341) {
            high = 46341;
        }
        int mid = (low + high) / 2;
        
        while (low < high - 1) {
            int mid_square = mid * mid;
            if (mid_square == x) {
                return mid;
            } else if (mid_square > x) {
                high = mid;
            } else {
                low = mid;
            }
            mid = (low + high) / 2;
        }
        return low;
    }
    
    
    // 88. Merge Sorted Array
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // resize nums1 if the space is not enough
        if (nums1.size() < m + n) {
            nums1.resize(m + n);
        }
        int nums1_ptr = m - 1;
        int nums2_ptr = n - 1;
        int result_ptr = m + n - 1;
        while (nums1_ptr >= 0 && nums2_ptr >= 0) {
            if (nums1[nums1_ptr] < nums2[nums2_ptr]) {
                nums1[result_ptr] = nums2[nums2_ptr];
                nums2_ptr -= 1;
            } else {
                nums1[result_ptr] = nums1[nums1_ptr];
                nums1_ptr -= 1;
            }
            result_ptr -= 1;
        }
        while (nums2_ptr >= 0) {
            nums1[result_ptr] = nums2[nums2_ptr];
            result_ptr -= 1;
            nums2_ptr -= 1;
        }
    }
    
    // 148. Sort List
    ListNode* sortList(ListNode* head) {
        return NULL;
    }
    
    // 191. Number of 1 Bits
    // actual, there is a crazy way of doing this with single CPU instruction
    int hammingWeight(uint32_t n) {
        int weight = 0;
        while (n > 0) {
            if (n % 2 == 1) {
                weight += 1;
            }
            n = n >> 1;
        }
        return weight;
    }
    
    // 338. Counting Bits
    vector<int> countBits(int num) {
        vector<int> result = {0};
        if (num == 0) {
            return result;
        }
        result.push_back(1);
        if (num == 1) {
            return result;
        }
        result.resize(num + 1);
        
        int curr_start = 2;
        int curr_end = 4;
        int curr_mid = (curr_start + curr_end) / 2;
        while (curr_end <= num) {
            /* calculate countBits [2^(n-1), 2^n) */
            for (int j = curr_start; j < curr_mid; j++) {
                result[j] = result[j - curr_start / 2];
            }
            for (int j = curr_mid; j < curr_end; j++) {
                result[j] = result[j - curr_start / 2] + 1;
            }
            curr_start *= 2;
            curr_end *= 2;
            curr_mid *= 2;
        }
        if (num < curr_mid) {
            for (int j = curr_start; j <= num; j++) {
                result[j] = result[j - curr_start / 2];
            }
        } else {
            for (int j = curr_start; j < curr_mid; j++) {
                result[j] = result[j - curr_start / 2];
            }
            for (int j = curr_mid; j <= num; j++) {
                result[j] = result[j - curr_start / 2] + 1;
            }
        }
        return result;
    }

}

#endif /* LeetCode_h */
