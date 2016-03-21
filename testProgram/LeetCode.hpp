//
//  LeetCode.hpp
//  testProgram
//
//  Created by Chi Zhang on 3/21/16.
//  Copyright © 2016 University of Southern California. All rights reserved.
//

#ifndef LeetCode_h
#define LeetCode_h

#include <vector>
#include <map>

using namespace std;

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

// #15, 3Sum
// helper function, the output two-d vector should be a set
vector<vector<int> > twoSumAll(int starting, vector<int>& nums, int target) {
    std::map<int, int> nums_map;
    vector<vector<int> > result;
    // O(n) to iterate
    std::map<int, int>::iterator map_it;
    bool sameNumAdd = false;
    for (int i = starting; i < nums.size(); i++) {
        if (i != starting && nums[i] == nums[i-1]) {
            if (sameNumAdd == false && nums[i] + nums[i-1] == target) {
                sameNumAdd = true;
            } else {
                continue;
            }
        }
        map_it = nums_map.find(target - nums[i]);
        if (map_it != nums_map.end()) {
            result.push_back({map_it->second, i});
        }
        nums_map[nums[i]] = i;
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
            result.push_back({nums[i], nums[singleTwoResult[0]], nums[singleTwoResult[1]]});
        }
    }
    return result;
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
            result.push_back({nums[i], nums[singleTwoResult[0]], nums[singleTwoResult[1]]});
        }
    }
    return result;
}

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    // sort the array
    std::sort(nums.begin(), nums.end());
    vector<vector<int> > result;
    vector<vector<int> > threeSumResult;
    for (int i = 0; i < nums.size(); i++) {
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

#endif /* LeetCode_h */
