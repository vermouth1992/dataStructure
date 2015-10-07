//
//  BinTree.h
//  testProgram
//
//  Created by Chi Zhang on 8/4/15.
//  Copyright (c) 2015 Chi Zhang
/*
 This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 General Public License as published by the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 License for more details.
 You should have received a copy of the GNU General Public License along with this program; if not, write
 to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 If you have any questions, please email zhan527@usc.edu
*/

#ifndef __testProgram__BinTree__
#define __testProgram__BinTree__

#include <stdio.h>
#include <cassert>
#include "BinNode.h"

using namespace std;

template <typename T>
class BinTree {
protected:
    int size_;
    BinNode<T>* root_;
    virtual int updateHeight(BinNode<T>* x); //update height at node x
    void updateHeightAbove(BinNode<T>* x);    //更新x及其祖先高度
    int removeAt(BinNode<T>* x);
public:
    BinTree(): size_(0), root_(NULL) {}
    ~BinTree() { if (size_ > 0) remove(root_);}
    int size() { return size_;}
    int height() { return root_ ? root_->height : -1; }
    BinNode<T>* root() { return root_;}
    bool empty() const { return root_ == NULL;}  //如果根节点为空
    BinNode<T>* insertAsRoot(T const& e);
    BinNode<T>* insertAsLeftChild(BinNode<T>* x, T const& e);  //e作为x的左孩子插入
    BinNode<T>* insertAsRightChild(BinNode<T>* x, T const& e);  //e作为x的有孩子插入
    BinNode<T>* attachAsLeftSubTree(BinNode<T>* x, BinTree<T>* t); //t作为x的左子树插入
    BinNode<T>* attachAsRightSubTree(BinNode<T>* x, BinTree<T>* t); //t作为x的右子树插入
    int remove(BinNode<T>* x);  //删除以x为根的子树，返回其规模
    int removeTree();
    void traverse_inorder(BinNode<T>* node, void (*pFunc)(BinNode<T>* node));
    void showTree();
};

template <typename T>
int BinTree<T>::updateHeight(BinNode<T> *x)
{
    x->height = 1 + max(stature(x->left_child), stature(x->right_child));
    return x->height;
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNode<T> *x)
{
    while (x) {
        int x_old_height = x->height;
        int x_new_height = updateHeight(x);
        if (x_old_height == x_new_height) {
            break;
        } else {
            x = x->parent;
        }
    }
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e)
{
    size_ = 1;
    root_ = new BinNode<T>(e);  //height default is 0
    return root_;
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsLeftChild(BinNode<T> *x, const T &e)
{
    assert(x->left_child == NULL);
    x->insertAsLeftNode(e);
    updateHeightAbove(x);
    size_ += 1;
    return x->left_child;
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsRightChild(BinNode<T> *x, const T &e)
{
    assert(x->right_child == NULL);
    x->insertAsRightNode(e);
    updateHeightAbove(x);
    size_ += 1;
    return x->right_child;
}

template <typename T>
BinNode<T>* BinTree<T>::attachAsLeftSubTree(BinNode<T> *x, BinTree<T> *t)
{
    assert(x->left_child == NULL);
    size_ += t->size_;
    x->left_child = t->root_;
    t->root_->parent = x;
    updateHeightAbove(x);
    return x;
}

template <typename T>
BinNode<T>* BinTree<T>::attachAsRightSubTree(BinNode<T> *x, BinTree<T> *t)
{
    assert(x->right_child == NULL);
    size_ += t->size_;
    x->right_child = t->root_;
    t->root_->parent = x;
    updateHeightAbove(x);
    return x;
}

//delete a sub-tree
template <typename T>
int BinTree<T>::removeAt(BinNode<T>* x)
{
    if (!x) {
        return 0;
    }
    int n = 1 + removeAt(x->left_child) + removeAt(x->right_child);
    if (x->parent == NULL) {
        x = NULL;
    } else if (x->isLChild()) {
        x->parent->left_child = NULL;
    } else {
        x->parent->right_child = NULL;
    }
    delete x;
    return n;
}

//return the number of nodes that has been deleted
template <typename T>
int BinTree<T>::remove(BinNode<T>* x)
{
    if (x->isLChild()) {
        x->parent->left_child = NULL;
        updateHeightAbove(x->parent);
        x->parent = NULL;
    } else if (x->isRChild()){
        x->parent->right_child = NULL;
        updateHeightAbove(x->parent);
        x->parent = NULL;
    }
    int n = removeAt(x);
    size_ -= n;
    return n;
}

template <typename T>
int BinTree<T>::removeTree()
{
    if (size_ > 0) {
        return remove(root_);
    } else {
        return 0;
    }
}

//helper function
template <typename T>
void showTreeNode(BinNode<T> *x)
{
    cout << x->height << ":" << x->data << "  ";
}

//helper function
template <typename T>
void subHeightOne(BinNode<T> *x)
{
    x->height -= 1;
}

template <typename T>
void BinTree<T>::traverse_inorder(BinNode<T>* node, void (*pFunc)(BinNode<T> *node))
{
    if (node->hasLChild()) {
        traverse_inorder(node->left_child, pFunc);
    }
    pFunc(node);
    if (node->hasRChild()) {
        traverse_inorder(node->right_child, pFunc);
    }
}

template <typename T>
void BinTree<T>::showTree()
{
    traverse_inorder(root_, &showTreeNode);
}

#endif /* defined(__testProgram__BinTree__) */





