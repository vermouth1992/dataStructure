//
//  main.cpp
//  testProgram
//
//  Created by Chi Zhang on 7/13/15.
//  Copyright (c) 2015 University of Southern California. All rights reserved.
//

#include <iostream>
#include "Fibonacci.h"
#include "MyVector.h"
#include "math.h"
#include "stdafx.h"

void reverse(int*, int, int);
void reverse(int*, int);

long int square(long int a){ return a * a;}
long int powerOf2(long int);

int gcdEuclid(int, int);
int gcdChinese(int, int);

int main(int argc, const char * argv[]) {
    //reverse test
    int testArray[6] = {1,2,3,4,5,6};
    reverse(testArray, 6);
    std::cout << "test of reverse" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << testArray[i] << ' ';
    }
    std::cout << std::endl;
    
    //powerOf2 test
    std::cout << "test of powerOf2" << std::endl;
    std::cout << powerOf2(16) << std::endl;
    
    //Fibonacci test
    Fib myFib(55);
    std::cout << "test of Fibonacci" << std::endl;
    myFib.showValue();
    myFib.prev();
    myFib.showValue();
    myFib.next();
    myFib.showValue();
    
    //gcd test
    int a = 9862, b = 41414124;
    std::cout << "test of Euclid gcd" << std::endl;
    std::cout << gcdEuclid(a, b) << std::endl;
    std::cout << "test of Chinese gcd" << std::endl;
    std::cout << gcdChinese(a, b) << std::endl;
    
    //pointer test
    int A[5] = {1,2,3,4,5};
    int *B = A + 2;
    std::cout << B[1] << B[2] << B[3] << B[4] << B[5] << B[6] << A[10] << std::endl;
    //delete[] A; actually we can't do this since A is not allocated memory using new operation
    
    //MyVector test
    std::cout << "Here is MyVector class function test!" << std::endl;
    MyVector<int> testVector(A, 2, 4);
    //test constructor
//    void (*pFunction)(int &p);
    //test traverse and function pointer
//    testVector.traverse(pFunction);
    
        
    return 0;
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
        std::cout << "The " << pc << "th call of recursion" << std::endl;
        return 1;
    }
    else if (n & 1)
    {
        pc += 1;
        std::cout << "The " << pc << "th call of recursion" << std::endl;
        return square(powerOf2(n >> 1)) << 1;
    }
    else
    {
        pc += 1;
        std::cout << "The " << pc << "th call of recursion" << std::endl;
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
    std::cout << "The " << pc << "th call of gcd." << std::endl;
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
            std::cout << "Total " << pc << " times iterations." << std::endl;
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







