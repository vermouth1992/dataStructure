//
//  AVL.hpp
//  testProgram
//
//  Created by Chi Zhang on 10/6/15.
//  Copyright © 2015 University of Southern California. All rights reserved.
//

#ifndef AVL_hpp
#define AVL_hpp

#include <stdio.h>

#include "BinNode.h"
#include "BinSearchTree.hpp"

template <typename T>
class AVL: public BinSearchTree<T> {
protected:
    BinNode<T>* rebalance(BinNode<T>* z);
public:
    BinNode<T>* insert(const T &e);
    bool remove(const T &e);
};

#endif /* AVL_hpp */
