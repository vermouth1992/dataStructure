//
//  Graph.h
//  testProgram
//
//  Created by Chi Zhang on 8/6/15.
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

#ifndef __testProgram__Graph__
#define __testProgram__Graph__

#include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;  //the status of vertex
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EStatus;  //the status of edge

template <typename Tv, typename Te>  //the type of vertex and edge
class Graph {
private:
    void BFS(int, int&);  //广度优先搜索
    void DFS(int, int&);  //深度优先搜索
    void BCC(int, int&, stack<int>&); //基于DFS的双连通分量分解算法
    bool TSort(int, int&, stack<Tv>*);  //基于DFS的拓扑排序算法
public:
    //vertex
    int n;  //顶点总数
    virtual int insert(Tv const&) = 0;  //插入顶点，返回编号
    virtual Tv remove(int) = 0;  //删除顶点及其关联边，返回顶点信息
    virtual Tv vertex(int) = 0;  //顶点v的数据
    virtual int inDegree(int) = 0;
    virtual int outDegree(int) = 0;
    virtual int firstNeighbor(int) = 0;
    virtual int nextNeighbor(int, int) = 0;
    virtual VStatus& status(int) = 0;
    virtual int& dTime(int) = 0;
    virtual int& fTime(int) = 0;
    virtual int& parent(int) = 0;  //顶点在遍历树中的父节点
    virtual int& priority(int) = 0;
    //edge
    int e;
    virtual bool exist(int, int) = 0;
    virtual void insert(Te const&, int, int, int) = 0;   //在两个顶点直接插入权重位w的边
    virtual Te remove(int, int) = 0;
    virtual EStatus& status(int, int) = 0;
    virtual Te edge(int, int) = 0;
    virtual int& weight(int, int) = 0;
    //algorithm
    
};


#endif /* defined(__testProgram__Graph__) */
