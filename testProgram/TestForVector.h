//
//  TestForVector.h
//  testProgram
//
//  Created by Chi Zhang on 8/1/15.
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

#ifndef __testProgram__TestForVector__
#define __testProgram__TestForVector__

#include <stdio.h>
#include "MyVector.h"

void addOne(int& x) {  //used for function pointer
    x += 1;
}

void testForVector()
{
    //pointer test
    int A[5] = {1,2,3,4,5};
    //delete[] A; actually we can't do this since A is not allocated memory using new operation
    //要分清是否只是指针还是确实定义了空间
    
    //MyVector test
    cout << "Here is MyVector class function test!" << endl;
    //test constructor
    MyVector<int> testVector(A, 2, 4); //注意是左开右闭区间
    testVector.show();
    //test insert and expand
    testVector.insert(5);
    testVector.show();
    testVector.insert(2, 10);
    testVector.show();
    testVector.insert(10, 20);
    testVector.show();
    testVector.capacity();
    testVector.insert(10);
    testVector.show();
    testVector.capacity();
    testVector.insert(20);
    testVector.show();
    testVector.capacity();
    testVector.size();
    //拷贝构造函数测试
    MyVector<int> vector1(testVector, 2, 5);
    vector1.show();
    MyVector<int> vector2(vector1);
    vector2.show();
    //test for [] operation
    cout << testVector[5] << endl;
    //test disordered
    testVector.insert(-1);
    cout << testVector.disordered() << endl;  //print how many pairs of elements in the vector are disordered
    //test find
    bool testFind = testVector[testVector.find(-1)] == -1;
    cout << testFind << endl;
    //test for = operation
    testVector.capacity();
    testVector.size();
    MyVector<int> vector3 = testVector;
    vector3.size();
    vector3.capacity();
    vector3.show();
    //test remove
    vector3.remove(3);
    vector3.show();
    vector3.remove(2, 5);
    vector3.show();
    vector3.capacity();
    //test for sort
    testVector.sort();
    testVector.show();
    //有序去重测试
    testVector.uniquify();
    testVector.show();
    //test for search
    cout << testVector.search(5) << endl;
    //test for unsort
    testVector.unsort();
    testVector.insert(10);
    testVector.show();
    //无序去重测试
    testVector.deduplicate();
    testVector.show();
    //test for traverse
    void (*pFunction)(int&);   //the data parameter has to be & for this application
    pFunction = &addOne;
    testVector.traverse(pFunction);
}




#endif /* defined(__testProgram__TestForVector__) */
