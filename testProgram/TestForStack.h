//
//  TestForStack.h
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

#ifndef __testProgram__TestForStack__
#define __testProgram__TestForStack__

#include <stdio.h>
#include <vector>
#include <string>

typedef vector<vector<char> > vec2_char;

//stack applications
//the output is little-endian
void numConvertRecur(MyStack<char>& S, int n, int base)  //十进制数n转化为base进制数
{
    static char digit[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };
    if (n > 0) {
        numConvertRecur(S, n / base, base);
        S.push(digit[n % base]);
    }
}

//the output is reverse sequence
void numConvertIter(MyStack<char>& S, int n, int base)
{
    static char digit[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };
    while (n > 0) {
        int remainder = n % base;
        S.push(digit[remainder]);
        n /= base;
    }
}

//calculator
//判断表达式是否合法
bool paren(string exp)
{
    MyStack<char> S;
    int i = 0;
    while (exp[i] != '\0') {
        switch (exp[i]) {
            case '{':
            case '[':
            case '(':
                S.push(exp[i]); break;
            case ')':
                if (S.empty() || S.pop() != '(') {
                    return false;
                }
                break;
            case ']':
                if (S.empty() || S.pop() != '[') {
                    return false;
                }
                break;
            case '}':
                if (S.empty() || S.pop() != '{') {
                    return false;
                }
                break;
            default:
                break;
        }
        i += 1;
    }
    if (!S.empty()) {
        return false;
    }
    return true;
}

//定义优先级二维数组
typedef enum {ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE} Operator;  //转化为数字
const int m = 9;
const char pri[m][m] = {  //[栈顶][当前]
    '>', '>', '<', '<', '<', '<', '<', '>', '>' // +
    , '>', '>', '<', '<', '<', '<', '<', '>', '>' // -
    , '>', '>', '>', '>', '<', '<', '<', '>', '>' // *
    , '>', '>', '>', '>', '<', '<', '<', '>', '>' // /
    , '>', '>', '>', '>', '>', '<', '<', '>', '>' // ^
    , '>', '>', '>', '>', '>', '>', ' ', '>', '>' // !
    , '<', '<', '<', '<', '<', '<', '<', '=', ' ' // (
    , ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' // )
    , '<', '<', '<', '<', '<', '<', '<', ' ', '=' // \0
};

Operator optr2rank(char op)
{
    switch (op) {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '^': return POW;
        case '!': return FAC;
        case '(': return L_P;
        case ')': return R_P;
        case '\0': return EOE;
        default: exit(-1);
    }
}

char orderBetween(char op1, char op2) {
    return pri[optr2rank(op1)][optr2rank(op2)];
}

void readNumber(string::iterator& p, MyStack<float>& opnd)
{
    opnd.push((float)(*p - '0'));
    p += 1;
    while (*p<='9' && *p>='0') {
        opnd.push(10 * opnd.pop() + (float)(*p - '0'));
        p += 1;
    }
    if (*p != '.') {
        return;
    }
    float frac = 0.1;
    p += 1;
    while (*p<='9' && *p>='0') {
        opnd.push(opnd.pop() + (float)(*p - '0') * frac);
        frac /= 10;
        p += 1;
    }
}

void append(string& rpn, float num)
{
    string temp = to_string(num);
    rpn.append(temp);
    rpn.insert(rpn.end(), ' ');
}

void append(string& rpn, char op)
{
    rpn.insert(rpn.end(), op);
}

float calc(char op, float operand)
{
    if (op != '!') {
        exit(-1);
    }
    int num = (int)(operand);
    float result = 1.0;
    for (int i = 0; i < num; i++) {
        result *= (float)(i+1);
    }
    return result;
}

float calc(char op, float operand1, float operand2)
{
    float result = 1.0;
    switch (op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand2 / operand1;
        case '^': {
            int iterator = (int)(operand1);
            for (int i = 0; i < iterator; i++) {
                result *= operand2;
            }
            return result;
        }
        default: exit(-1);
    }
}

float calculate(string exp, string& rpn)  //calculate value of expression and return rpn expression
{
    if (!paren(exp)) {
        exit(-1);
    }
    MyStack<float> opnd;  //结果栈
    MyStack<char> optr;   //操作数栈
    string::iterator p = exp.begin();
    optr.push('\0');
    while (!optr.empty()) {
        while (*p == ' ' || *p == '\t') {  //跳过空格
            p += 1;
        }
        if (*p>='0' && *p<='9') {
            readNumber(p, opnd);   //如果是数字的话，直接入栈并且接在RPN表达式之后
            append(rpn, opnd.top());
        } else {
            switch (orderBetween(optr.top(), *p)) {
                case '<':
                    optr.push(*p);
                    p += 1;
                    break;
                case '=':
                    optr.pop();
                    p += 1;
                    break;
                case '>': {
                    char op = optr.pop();
                    append(rpn, op);
                    if (op == '!') {
                        float operand = opnd.pop();
                        opnd.push(calc(op, operand));
                    } else {
                        float operand1 = opnd.pop();
                        float operand2 = opnd.pop();
                        opnd.push(calc(op, operand1, operand2));
                    }
                    break;
                }
                default: exit(-1);
            }
        }
    }
    return opnd.pop();
}

float rpnCalculate(string rpnExpression)  //后缀表达式
{
    MyStack<float> opnd;  //结果栈
    string::iterator p = rpnExpression.begin();
    while (p != rpnExpression.end()) {
        if (*p>='0' && *p<='9') {
            readNumber(p, opnd);   //如果是数字的话，直接入栈并且接在RPN表达式之后
            p += 1;
        } else {
            char op = *p;
            if (op == '!') {
                float operand1 = opnd.pop();
                opnd.push(calc(op, operand1));
            } else {
                float operand1 = opnd.pop();
                float operand2 = opnd.pop();
                opnd.push(calc(op, operand1, operand2));
            }
            p += 1;
        }
    }
    return opnd.pop();
}

void testForStack()
{
    MyStack<int> testStack;
    testStack.push(10);
    testStack.push(20);
    testStack.push(200);
    testStack.show();
    testStack.pop();
    testStack.show();
    //test number converter
    MyStack<char> numStackRecur;
    numConvertRecur(numStackRecur, 134234, 16);
    numStackRecur.show();
    MyStack<char> numStackIter;
    numConvertIter(numStackIter, 134234, 16);
    numStackIter.show();
    //test read number
    string num = "10.32";
    string::iterator num_start = num.begin();
    MyStack<float> numStack;
    readNumber(num_start, numStack);
    numStack.show();
    //test calc;
    cout << calc('!', 4.0) << endl;
    cout << calc('+', 4.5, 2.3) << endl;
    cout << calc('^', 4.5, 2.0) << endl;
    cout << calc('/', 4.0, 2.3) << endl;
    //test calculator
    string expression = "(4+5+3.5)^2";
    string rpn;
    cout << calculate(expression, rpn) << endl;
    cout << rpn << endl;
    cout << rpnCalculate(rpn) << endl;
}



#endif /* defined(__testProgram__TestForStack__) */
