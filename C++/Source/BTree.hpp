//
//  BTree.hpp
//  testProgram
//
//  Created by Chi Zhang on 10/8/15.
//  Copyright © 2015 University of Southern California. All rights reserved.
//

#ifndef BTree_hpp
#define BTree_hpp

#include <stdio.h>
#include <vector>

using namespace std;

template <typename T>
class BTNode {
public:
    BTNode<T>* parent;
    vector<T> data;
    vector<BTNode<T>*> child;  //the lenght of child is always one more than length of data
    BTNode() { parent = NULL; child.insert(0, NULL); }
    BTNode(T e, BTNode<T>* left_child, BTNode<T>* right_child) {
        parent = NULL;
        data.insert(0, e);
        child.push_back(left_child);
        child.push_back(right_child);
        if (left_child) {
            left_child->parent = this;
        }
        if (right_child) {
            right_child->parent = this;
        }
    }
};

template <typename T>
class BTree {
protected:
    int size_;
    int order_;
    BTNode<T> root_;
public:
    BTree(int order = 3) : size_(0), order_(order) { root_ = new BTNode<T>(); }
    
};







#endif /* BTree_hpp */
