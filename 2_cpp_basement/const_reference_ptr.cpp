//
// Created by marquezzz on 2026/5/3.
//

#include <iostream>
using namespace std;

/*
 * const, 一级指针，引用的结合使用
 */

int main () {
    const int &a = 20;
    int &&b = 40;

    // 写一句代码，在内存的0x0018ff44处写一个4字节的10
    int *&&p = (int *)0x0018ff44;
    int *const &p1 = (int *)0x0018ff44;

    int a1 = 10;
    int *p2 = &a1;;
    int **p3 = &p2; // 等价 int *&p3 = p2;
    const int *&p4 = p2; // 等价于 const int **p4 = &p2
}

// 一个非常经典的例子
/*
 * int a = 10;
 * int *const p = &a;
 * int *&q = p;(x)  等价于int **q = &p  即 int ** <= int *const * 也就是 * <= const* 这是错误的
 *
 */