//
//  TestForBinTree.hpp
//  testProgram
//
//  Created by Chi Zhang on 10/3/15.
//  Copyright © 2015 University of Southern California. All rights reserved.
//

#ifndef TestForBinTree_hpp
#define TestForBinTree_hpp

#include <iostream>

#include "BinNode.h"

void testBinNode()
{
    //start with an empty tree
    BinTree<int>testTree = BinTree<int>();
    testTree.insertAsRoot(10);
    testTree.insertAsLeftChild(testTree.root(), 5);
    testTree.insertAsRightChild(testTree.root(), 20);
}

#endif /* TestForBinTree_hpp */
