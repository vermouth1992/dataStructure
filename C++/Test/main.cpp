//
//  main.cpp
//  Test
//
//  Created by Chi Zhang on 12/29/15.
//  Copyright © 2015 University of Southern California. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <sys/time.h>
#include "gtest/gtest.h"


int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "arrayTest*";   //google test filter
    return RUN_ALL_TESTS();
}
