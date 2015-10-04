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

void generate_search_tree(BinTree<int>* testTree)
{
    BinNode<int>* work_node = testTree->insertAsRoot(16);
    work_node = testTree->insertAsLeftChild(work_node, 10);
    work_node = testTree->insertAsLeftChild(work_node, 5);
    work_node = testTree->insertAsLeftChild(work_node, 2);
    testTree->insertAsRightChild(work_node, 4);
    work_node = work_node->parent;
    testTree->insertAsRightChild(work_node, 8);
    work_node = work_node->parent;
    work_node = testTree->insertAsRightChild(work_node, 11);
    work_node = testTree->insertAsRightChild(work_node, 15);
    testTree->insertAsLeftChild(work_node, 13);
    work_node = testTree->root();
    work_node = testTree->insertAsRightChild(work_node, 25);
    work_node = testTree->insertAsLeftChild(work_node, 19);
    testTree->insertAsLeftChild(work_node, 17);
    testTree->insertAsRightChild(work_node, 22);
    work_node = work_node->parent;
    work_node = testTree->insertAsRightChild(work_node, 28);
    testTree->insertAsLeftChild(work_node, 27);
    work_node = testTree->insertAsRightChild(work_node, 37);
    testTree->insertAsLeftChild(work_node, 33);
}

void testBinNode()
{
    //start with an empty tree
    BinTree<int> testTree = BinTree<int>();
    BinNode<int>* root = testTree.insertAsRoot(10);
    testTree.insertAsLeftChild(testTree.root(), 5);
    testTree.insertAsRightChild(testTree.root(), 20);
    
    //test has child
    cout << root->left_child->isLChild() << ' ' << root->right_child->isRChild() << endl;
    
    //test traverse
    testTree.traverse_inorder(root, &showTreeNode);
    cout << endl;
    testTree.traverse_inorder(root, addOneTreeNode);
    testTree.traverse_inorder(root, &showTreeNode);
    cout << endl;
    
    //test remove
    cout << testTree.remove(root) << endl;
    
    //Binary Search tree
    BinTree<int>* testBinTree = new BinTree<int>();
    generate_search_tree(testBinTree);
    testBinTree->traverse_inorder(testBinTree->root(), &showTreeNode);
    cout << endl << testBinTree->removeTree() << endl;
}

#endif /* TestForBinTree_hpp */
