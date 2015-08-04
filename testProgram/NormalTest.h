//
//  NormalTest.h
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

#ifndef __testProgram__NormalTest__
#define __testProgram__NormalTest__

#include <stdio.h>
#include <vector>

typedef vector<vector<int> > vec2_int;

void reverse(int*, int, int);
void reverse(int*, int);

long int square(long int a){ return a * a;}
long int powerOf2(long int);

int gcdEuclid(int, int);
int gcdChinese(int, int);



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

void testForVector2()
{
    int m = 9;
    int n = 9;
    vec2_int test_array(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            test_array[i][j] = 0;
            cout << test_array[i][j] << ',';
        }
        cout << endl;
    }
}

void testForReadFile()
{
    ifstream readFile;
    readFile.open("labyrinth.txt");
    int size = 5;
    vec2_int laby(size, vector<int>(size));
    if (readFile.is_open()) {
        int i = 0;
        int j = 0;
        while (!readFile.eof()) {
            readFile >> laby[i][j];
            if (i == 4) {
                i = 0;
                j += 1;
            } else {
                i += 1;
            }
        }
    } else {
        cout << "Can't open file!" << endl;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << laby[i][j] << ' ';
        }
        cout << endl;
    }

}


#endif /* defined(__testProgram__NormalTest__) */
