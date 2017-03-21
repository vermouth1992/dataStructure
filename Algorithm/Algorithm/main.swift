//
//  main.swift
//  Algorithm
//
//  Created by Chi Zhang on 3/14/17.
//  Copyright © 2017 Chi Zhang. All rights reserved.
//

import Foundation

print("Hello, World!")

var result = 1 + 2
print("1 + 2 = \(result)")

func arithmeticMean(_ numbers: [Double]) -> Double {
    var total = 0.0
    for number in numbers {
        total += number
    }
    return total / Double(numbers.count)
}

print(arithmeticMean([1.0, 2, 3, 5]))

func arithmeticMean(_ numbers: Double...) -> Double {
    var total = 0.0
    for number in numbers {
        total += number
    }
    return total / Double(numbers.count)
}

print(arithmeticMean(1.0, 2, 3, 5))

func swapTwoValues<T>(_ a: inout T, _ b: inout T) {
    let tempA = a
    a = b
    b = tempA
}

var someInt = 3
var anotherInt = 7
swapTwoValues(&someInt, &anotherInt)
print("After swap, someInt is \(someInt), anotherInt is \(anotherInt)")

var someString = "hello"
var anotherString = "world"
swapTwoValues(&someString, &anotherString)
print("After swap, someString is \(someString), anotherString is \(anotherString)")



var node = BinTreeNode(data: 3.0)
print(node)


func hanoi(_ n: Int, _ A: String, _ B: String, _ C: String) {
    if n == 1 {
        print("Move from \(A) to \(C)")
    } else {
        hanoi(n - 1, A, C, B)
        print("Move from \(A) to \(C)")
        hanoi(n - 1, B, A, C)
    }
}

hanoi(3, "A", "B", "C")





