//
//  HeapTest.cpp
//  testProgram
//
//  Created by Chi Zhang on 1/20/16.
//  Copyright © 2016 University of Southern California. All rights reserved.
//

#include <stdio.h>
#include <time.h>

#include "Heap.hpp"
#include "gtest/gtest.h"

using namespace std;

TEST (HeapTest, insertTest)
{
    CompleteBinaryHeap<int> test_heap;
    ASSERT_EQ(test_heap.size(), 0);
    test_heap.insert(6);
    EXPECT_EQ(test_heap.getMax(), 6);
    test_heap.insert(5);
    EXPECT_EQ(test_heap.getMax(), 6);
    test_heap.insert(10);
    EXPECT_EQ(test_heap.getMax(), 10);
}

TEST (HeapTest, deleteTest)
{
    CompleteBinaryHeap<double> test_heap;
    test_heap.insert(2.34);
    test_heap.insert(2.34);
    test_heap.insert(5.67);
    test_heap.insert(1.23);
    EXPECT_EQ(5.67, test_heap.delMax());
    EXPECT_EQ(2.34, test_heap.delMax());
    EXPECT_EQ(2.34, test_heap.getMax());
    EXPECT_EQ(2.34, test_heap.delMax());
    EXPECT_EQ(1.23, test_heap.delMax());
    // delete more would throw exceptions
    //EXPECT_EQ(0, test_heap.delMax());
}

TEST (HeapTest, heapification)
{
    // use fixed test vector
    int a[] = {3, 4, 2, 90, 3, 2, 5, 3, 1, 5, 7, 23, 2, 0};
    vector<int> test_vector (a, a + sizeof(a) / sizeof(int));
    vector<int> test_vector_copy(test_vector);
    CompleteBinaryHeap<int> test_heap(test_vector);
    ASSERT_EQ(test_heap.size(), test_vector_copy.size());
    EXPECT_EQ(90, test_heap.delMax());
    EXPECT_EQ(23, test_heap.delMax());
    EXPECT_EQ(7, test_heap.delMax());
    EXPECT_EQ(5, test_heap.delMax());
    for (int i = 0; i < test_vector.size(); i++) {
        // the original vector remains unchanged
        EXPECT_TRUE(test_vector[i] == test_vector_copy[i]);
    }
    // use random generate vector
    srand((uint)time(NULL));
    int test_num = 100;
    vector<int> random_test_vector;
    for (int i = 0; i < test_num; i++) {
        random_test_vector.push_back(rand() % 10000);
    }
    CompleteBinaryHeap<int> random_test_heap(random_test_vector);
    EXPECT_TRUE(random_test_heap.isMaxHeap());
}

TEST (HeapTest, heapSort)
{
    srand((uint)time(NULL));
    int test_num = 100;
    vector<int> random_test_vector;
    for (int i = 0; i < test_num; i++) {
        random_test_vector.push_back(rand() % 10000);
    }
    heapSort(random_test_vector);
    for (int i = 0; i < test_num - 1; i++) {
        EXPECT_TRUE(random_test_vector[i] >= random_test_vector[i+1]);
    }
}

