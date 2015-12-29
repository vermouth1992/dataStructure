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
#include "BinTree.h"
#include "BinSearchTree.hpp"

void generate_search_tree(BinSearchTree<int>* testTree)
{
    BinNode<int>* work_node = testTree->insertAsRoot(16);
    work_node = testTree->insertAsLeftChild(work_node, 10);
    work_node = testTree->insertAsLeftChild(work_node, 5);
    work_node = testTree->insertAsLeftChild(work_node, 2);
    testTree->insertAsRightChild(work_node, 4);
    work_node = work_node->parent;
    testTree->insertAsRightChild(work_node, 8);
    work_node = work_node->parent;
    work_node = testTree->insertAsRightChild(work_node, 12);
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
    cout << "Test isChild function\n";
    cout << root->left_child->isLChild() << ' ' << root->right_child->isRChild() << endl;
    
    //test traverse
    cout << "Test inorder traverse\n";
    testTree.traverse_inorder(root, &showTreeNode);
    cout << endl;
    
    //test remove
    cout << "Test remove a tree\n" << testTree.remove(root) << endl;
    
    //Binary Search tree
    BinSearchTree<int>* testBinSearchTree = new BinSearchTree<int>();
    generate_search_tree(testBinSearchTree);
    cout << "Test inorder traverse show BinSearchTree\n";
    testBinSearchTree->showTree_inorder();
    cout << endl;
    
    //search
    BinNode<int>* binSearchCurrentNode = testBinSearchTree->root();
    BinSearchInsertDirection dir = NONE;
    int searchValue = 34;
    bool result = testBinSearchTree->search(searchValue, binSearchCurrentNode, dir);
    cout << "Test BST search\n";
    cout << binSearchCurrentNode->data << ' ' << dir << endl;
    if (result) {
        cout << binSearchCurrentNode->data << " is in the search tree." << endl;
    } else {
        cout << searchValue << " is not in the search tree." << endl;
    }
    
    //insert
    cout << "Test BST insert\n";
    testBinSearchTree->insert(searchValue);
    testBinSearchTree->showTree_levelbylevel();
    cout << endl;
    
    //test for remove
    int removeValue = 13;
    cout << "Test BST remove\n";
    if (testBinSearchTree->remove(removeValue)) {
        cout << removeValue << " has been removed successfully." << endl;
    }
    testBinSearchTree->showTree_levelbylevel();
    cout << endl;
    cout << testBinSearchTree->removeTree() << endl;
}

#endif /* TestForBinTree_hpp */
