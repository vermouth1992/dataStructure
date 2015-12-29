//
//  main.cpp
//  Test
//
//  Created by Chi Zhang on 12/29/15.
//  Copyright © 2015 University of Southern California. All rights reserved.
//

#include <iostream>
#include "NormalTest.h"
#include "gtest/gtest.h"

TEST (testProgram, Addition)
{
    // equal to 20
    EXPECT_EQ(addition(10, 10), 20);
    
    EXPECT_EQ(addition(20, 10), 30);
    
    // not equal to 20
    EXPECT_NE(addition(10, 10), -20);
}

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}