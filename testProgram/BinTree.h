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
#include "BinNode.h"

template <typename T>
class BinTree {
protected:
    int size_;
    BinNode<T>* root_;
    //void updateHeightAbove(BinNode<T>* x);    //更新x及其祖先高度
    int removeAt(BinNode<T>* x);
public:
    BinTree(): size_(0), root_(NULL) {}
    ~BinTree() { if (size_ > 0) remove(root_);}
    int size() { return size_;}
    BinNode<T>* root() { return root_;}
    bool empty() const { return root_ == NULL;}  //如果根节点为空
    BinNode<T>* insertAsRoot(T const& e);
    BinNode<T>* insertAsLeftChild(BinNode<T>* x, T const& e);  //e作为x的左孩子插入
    BinNode<T>* insertAsRightChild(BinNode<T>* x, T const& e);  //e作为x的有孩子插入
    BinNode<T>* attachAsLeftSubTree(BinNode<T>* x, BinTree<T>*& t); //t作为x的左子树插入
    BinNode<T>* attachAsRightSubTree(BinNode<T>* x, BinTree<T>*& t); //t作为x的右子树插入
    int remove(BinNode<T>* x);  //删除以x为根的子树，返回其规模
    int removeTree();
    void traverse_inorder(BinNode<T>* node, void (*pFunc)(T &));
};

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
    size_ += 1;
    return x->left_child;
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsRightChild(BinNode<T> *x, const T &e)
{
    assert(x->right_child == NULL);
    x->insertAsRightNode(e);
    size_ += 1;
    return x->right_child;
}

//return the number of nodes that has been deleted
template <typename T>
int BinTree<T>::remove(BinNode<T>* x)
{
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

template <typename T>
int BinTree<T>::removeAt(BinNode<T>* x)
{
    if (!x) {
        return 0;
    }
    int n = 1 + removeAt(x->left_child) + removeAt(x->right_child);
    if (x->isRoot()) {
        root_ = NULL;
    } else if (x->isLChild()) {
        x->parent->left_child = NULL;
    } else {
        x->parent->right_child = NULL;
    }
    delete x;
    return n;
}

template <typename T>
void showTreeNode(T &x)
{
    cout << x << ' ';
}

template <typename T>
void addOneTreeNode(T &x)
{
    x = x + 1;
}

template <typename T>
void BinTree<T>::traverse_inorder(BinNode<T>* node, void (*pFunc)(T &))
{
    if (node->hasLChild()) {
        traverse_inorder(node->left_child, pFunc);
    }
    pFunc(node->data);
    if (node->hasRChild()) {
        traverse_inorder(node->right_child, pFunc);
    }
}

#endif /* defined(__testProgram__BinTree__) */





