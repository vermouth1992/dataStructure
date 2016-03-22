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
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// common interfaces
// singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};



// #1, two sum
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


// 67. Add Binary
string addBinary(string a, string b) {
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
        overflow = unit / 2;
        digit = unit % 2;
        result.insert(result.begin(), digit + '0');
        ptr_a -= 1;
        ptr_b -= 1;
    }
    if (ptr_a == -1) {
        if (ptr_b != -1) {
            while (ptr_b >= 0) {
                unit = (b[ptr_b] - '0') + overflow;
                overflow = unit / 2;
                digit = unit % 2;
                result.insert(result.begin(), digit + '0');
                ptr_b -= 1;
            }
        }
    } else {
        if (ptr_a != -1) {
            while (ptr_a >= 0) {
                unit = (a[ptr_a] - '0') + overflow;
                overflow = unit / 2;
                digit = unit % 2;
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



#endif /* LeetCode_h */
