//
//  HeapTest.cpp
//  testProgram
//
//  Created by Chi Zhang on 1/20/16.
//  Copyright © 2016 University of Southern California. All rights reserved.
//

#include <stdio.h>
#include "Heap.hpp"
#include "gtest/gtest.h"


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

