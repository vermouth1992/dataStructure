//
//  BinNode.h
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

#ifndef __testProgram__BinNode__
#define __testProgram__BinNode__

#include <iostream>

#define stature(p) ((p) ? (p)->height : -1)

template <typename T>
class BinNode {
public:
    T data;
    BinNode<T>* parent;
    BinNode<T>* left_child;
    BinNode<T>* right_child;
    int height;   //当前节点的高度
    
    BinNode(T e): data(e), parent(NULL), left_child(NULL), right_child(NULL), height(0) {}
    BinNode(T e, BinNode<T>* parent, BinNode<T>* lChild, BinNode<T>* rChild, int height)
    : data(e), parent(parent), left_child(lChild), right_child(rChild), height(height) {}
    int size(); //统计以其为根的子树的规模
    BinNode<T>* insertAsLeftNode(T const&);
    BinNode<T>* insertAsRightNode(T const&);
    //BinNode<T>* succ();
    bool isRoot() { return parent == NULL;}
    bool isLChild() { return !isRoot() && (this == parent->left_child);}
    bool isRChild() { return !isRoot() && (this == parent->right_child);}
    bool hasParent() { return !isRoot();}
    bool hasLChild() { return left_child != NULL;}
    bool hasRChild() { return right_child != NULL;}
    bool hasChild() { return hasLChild() || hasRChild();}
    bool hasBothChild() { return hasLChild() && hasRChild();}
    bool isLeaf() {return !hasChild();}
    int getBalanceFactor() { return stature(right_child) - stature(left_child); }
};

template <typename T>
BinNode<T>* BinNode<T>::insertAsLeftNode(const T & e)
{
    return left_child = new BinNode<T>(e, this, NULL, NULL, 0);  //自己作为父节点并且插入左子女
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsRightNode(const T & e)
{
    return right_child = new BinNode<T>(e, this, NULL, NULL, 0);
}

#endif /* defined(__testProgram__BinNode__) */
