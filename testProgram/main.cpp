//  main.cpp
//  testProgram
//
//  Created by Chi Zhang on 7/13/15.
//  This is a self-paced data structure exercises described in C++
/* Copyright (C) <2015> <Chi Zhang>
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

#include <iostream>
#include "Fibonacci.h"
#include "MyVector.h"
#include "List.h"
#include "ListNode.h"
#include "Stack.h"
#include "math.h"

using namespace std;

void reverse(int*, int, int);
void reverse(int*, int);

long int square(long int a){ return a * a;}
long int powerOf2(long int);

int gcdEuclid(int, int);
int gcdChinese(int, int);

void addOne(int& x) {  //used for function pointer
    x += 1;
}

void testForReverse()
{
    //reverse test
    int testArray[6] = {1,2,3,4,5,6};
    reverse(testArray, 6);
    cout << "test of reverse" << endl;
    for (int i = 0; i < 6; i++) {
        cout << testArray[i] << ' ';
    }
    cout << endl;
}

void testForPowerOf2()
{
    //powerOf2 test
    cout << "test of powerOf2" << endl;
    cout << powerOf2(16) << endl;
}

void testForFib()
{
    //Fibonacci test
    Fib myFib(55);
    cout << "test of Fibonacci" << endl;
    myFib.showValue();
    myFib.prev();
    myFib.showValue();
    myFib.next();
    myFib.showValue();
}

void testForGcd()
{
    //gcd test
    int a = 9862, b = 41414124;
    cout << "test of Euclid gcd" << endl;
    cout << gcdEuclid(a, b) << endl;
    cout << "test of Chinese gcd" << endl;
    cout << gcdChinese(a, b) << endl;
}

void testForVector();
void testForList();
void testForStack();


int main(int argc, const char * argv[]) {
    srand(time(NULL)); //this line should be global, but not in any function
    testForStack();
    return 0;
}

void testForStack()
{
    MyStack<int> testStack;
    testStack.push(10);
    testStack.push(20);
    testStack.show();
}


void testForList()
{
    //test constructor
    List<int> L;
    L.insertAsFirst(10);
    L.insertAsFirst(5);
    L.insertAsLast(20);
    ListNode<int> *p = L.first();
    L.insertBefore(p, 15);
    p = p->succ;
    L.insertBefore(p, 12); //p can't self repoint to L.first()
    L.insertAfter(p, 15);
    List<int> L1(L);   //copy entire List
    L1.showList();
    List<int> L2(L1, 2, 3); //copy from particular rank
    L2.showList();
    List<int> L3(p, 3);     //copy from particular ListNode
    L3.showList();
    cout << L.size() << ' ' << L.empty() << endl;
    cout << L.disordered() << endl;
    //test find
    L.showList();
    ListNode<int>* q;
    q = L.find(10);
    cout << q->succ->data << endl;
    q = L.find(15, 3, q);  //start find 15 from 10
    cout << q->succ->data << endl;
    List<int> L4(L);
    L.deduplicate();  //test 无序去重
    L.showList();
    //test sort
    L.sort();
    L.showList();
    cout << "List4 test" << endl;
    L4.sort();
    L4.showList();
    L4.uniquify();
    L4.showList();
    //test for search
    q = L4.search(9);
    cout << q->data << endl;
    cout << L4.selectMax()->data << endl;
}

void reverse(int* A, int low, int high) //assist function
{
    if (low < high) {
        int temp;
        temp = A[low];
        A[low] = A[high];
        A[high] = temp;
        reverse(A, low + 1, high - 1);
    }
}

void reverse(int* A, int n) //overload to make function more general
{
    reverse(A, 0, n - 1);
}

//To compute some actual function, sometimes it may gain a lot if you look in binary way.
long int powerOf2(long int n) //time complexity is log2(n)
{
    static int pc = 0; //program counter
    if (n == 0) {
        pc += 1;
        cout << "The " << pc << "th call of recursion" << endl;
        return 1;
    }
    else if (n & 1)
    {
        pc += 1;
        cout << "The " << pc << "th call of recursion" << endl;
        return square(powerOf2(n >> 1)) << 1;
    }
    else
    {
        pc += 1;
        cout << "The " << pc << "th call of recursion" << endl;
        return square(powerOf2(n >> 1));
    }
}

int gcdEuclid(int a, int b)
{
    static int pc = 0;
    if (a <= b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (b == 0) {
        return a;
    }
    if (b == 1) {
        return 1;
    }
    pc += 1;
    cout << "The " << pc << "th call of gcd." << endl;
    return gcdEuclid(b, a % b);
}

int gcdChinese(int a, int b)
{
    static int pc = 0;
    int p = 1;
    while (a % 2 == 0 && b % 2 == 0) {
        pc += 1;
        a /= 2;
        b /= 2;
        p *= 2;
    }
    int t = abs(a - b);
    while (1) {
        if (t == 0) {
            cout << "Total " << pc << " times iterations." << endl;
            return a * p;
        }
        while (t % 2 == 0) {
            t /= 2;
        }
        if (a >= b) a = t;
        else b = t;
        t = abs(a - b);
        pc += 1;
    }
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




