//
//  BinSearchTree.hpp
//  testProgram
//
//  Created by Chi Zhang on 10/4/15.
//  Copyright © 2015 University of Southern California. All rights reserved.
//

#ifndef BinSearchTree_hpp
#define BinSearchTree_hpp

#include <stdio.h>
#include "BinNode.h"
#include "BinTree.h"

enum BinSearchInsertDirection { LEFT, RIGHT, NONE };

template <typename T>
class BinSearchTree: public BinTree<T> {
protected:
    //find the next value in BST
    BinNode<T>* succ(BinNode<T>*);
    bool removeAt(BinNode<T>* node, BinSearchInsertDirection dir);
    void updateHeight(BinNode<T>* curr_node);
public:
    bool search(const T &e, BinNode<T>*& curr_node, BinSearchInsertDirection &dir);
    BinNode<T>* insert(const T &e);
    bool remove(const T &e);
};

template <typename T>
bool BinSearchTree<T>::search(const T &e, BinNode<T>*& curr_node, BinSearchInsertDirection &dir)
{
    while (1) {
        if (curr_node->data == e) {
            dir = NONE;
            return true;
        } else if (curr_node->data > e) {
            if (curr_node->left_child) {
                curr_node = curr_node->left_child;
            } else {
                dir = LEFT;
                break;
            }
        } else {
            if (curr_node->right_child) {
                curr_node = curr_node->right_child;
            } else {
                dir = RIGHT;
                break;
            }
        }
    }
    return false;
}

template <typename T>
BinNode<T>* BinSearchTree<T>::insert(const T &e)
{
    BinNode<int>* binSearchCurrentNode = this->root_;
    BinSearchInsertDirection dir = NONE;
    bool v = search(e, binSearchCurrentNode, dir);
    //we have to make sure that the node is not in the tree
    if (!v) {
        if (dir == LEFT) {
            binSearchCurrentNode = this->insertAsLeftChild(binSearchCurrentNode, e);
        } else if (dir == RIGHT) {
            binSearchCurrentNode = this->insertAsRightChild(binSearchCurrentNode, e);
        }
    }
    return binSearchCurrentNode;
}

//helper function succ, find the smallest number which is bigger than current node
template <typename T>
BinNode<T>* BinSearchTree<T>::succ(BinNode<T> *start)
{
    //must have right child
    assert(start->hasRChild());
    start = start->right_child;
    while (start->hasLChild()) {
        start = start->left_child;
    }
    return start;
}

template <typename T>
void BinSearchTree<T>::updateHeight(BinNode<T>* curr_node)
{
    this->traverse_inorder(curr_node, &subHeightOne);
}

template <typename T>
bool BinSearchTree<T>::remove(const T &e)
{
    BinNode<T> *curr_node = this->root_;
    BinSearchInsertDirection dir = NONE;
    bool isExist = search(e, curr_node, dir);
    if (!isExist) {
        return false;
    }
    //if the node doesn't have child
    if (!curr_node->hasChild()) {
        return removeAt(curr_node, NONE);
    } else if (!curr_node->hasLChild()) { //if the node doesn't have left child
        return removeAt(curr_node, RIGHT);
    } else if (!curr_node->hasRChild()) {
        return removeAt(curr_node, LEFT);
    } else {
        //find the node to swap
        BinNode<T>* next_node = succ(curr_node);
        //copy the value
        curr_node->data = next_node->data;
        if (next_node->hasRChild()) {
            return removeAt(next_node, RIGHT);
        } else {
            return removeAt(next_node, NONE);
        }
    }
}

//only delete node which doesn't have both children
template <typename T>
bool BinSearchTree<T>::removeAt(BinNode<T>* curr_node, BinSearchInsertDirection dir)
{
    assert(curr_node);
    switch (dir) {
        case NONE:
            if (curr_node->isLChild()) {
                curr_node->parent->left_child = NULL;
            } else {
                curr_node->parent->right_child = NULL;
            }
            delete curr_node;
            return true;
        //has left child
        case LEFT:
            curr_node->left_child->parent = curr_node->parent;
            if (curr_node->isLChild()) {
                curr_node->parent->left_child = curr_node->left_child;
            } else {
                curr_node->parent->right_child = curr_node->left_child;
            }
            //update height
            updateHeight(curr_node->left_child);
            delete curr_node;
            return true;
        //has right child
        case RIGHT:
            curr_node->right_child->parent = curr_node->parent;
            if (curr_node->isLChild()) {
                curr_node->parent->left_child = curr_node->right_child;
            } else {
                curr_node->parent->right_child = curr_node->right_child;
            }
            //update height
            updateHeight(curr_node->right_child);
            delete curr_node;
            return true;
        default:
            return false;
    }
}

#endif /* BinSearchTree_hpp */
