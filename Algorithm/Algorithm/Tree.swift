//
//  Tree.swift
//  Algorithm
//
//  Created by Chi Zhang on 3/14/17.
//  Copyright © 2017 Chi Zhang. All rights reserved.
//

import Foundation

class BinTreeNode<DType> {
    var data: DType
    var leftChild: BinTreeNode?
    var rightChild: BinTreeNode?
    
    init(data: DType, leftChild: BinTreeNode?, rightChild: BinTreeNode?) {
        self.data = data
        self.leftChild = leftChild
        self.rightChild = rightChild
    }
    
    convenience init(data: DType) {
        self.init(data: data, leftChild: nil, rightChild: nil)
    }
}

