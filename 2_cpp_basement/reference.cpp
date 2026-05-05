//
// Created by marquezzz on 2026/5/2.
//

#include<iostream>
using namespace std;

/*
 * c++的引用 引用和指针的区别？
 *
 * 1、左值引用和右值引用
 * 2、引用的实例
 *
 * 引用是一种更安全的指针
 * 1、引用是必须初始化的，指针可以不初始化
 * 2、引用只有一级引用，没有多级引用
 * 3、定义一个引用变量和定义一个指针变量，其汇编指令是一模一样的；
 *      通过引用变量修改所引用内存的值，和通过指针解引用修改指针指向的内存的值，其底层指令也是一模一样的
 *
 * 右值引用
 * 1、int &&c = 20; 专门用来引用右值类型，指令上，可以自动产生临时量，然后直接引用临时量
 * 2、右值引用变量本身是一个左值，只能用左值来引用他
 * 3、不能用一个右值引用变量，来引用一个左值
 */

#if 0
int main0 () {


    int a = 10;
    int *p = &a;

    int &b = a;

    *p = 20;
    cout << a << " " << *p << " " << b << endl; // 20 20 20
    b = 30;
    cout << a << " " << *p << " " << b << endl; // 30 30 30

    return 0;
}

void swap (int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main1 () {
    int a = 10;
    int b = 20;
    swap(a, b);
    cout << a << " " << b << endl;

    return 0;
}

int main2 () {

    int array[5] = {};
    int *p = array;

    int (*p1)[5] = &array;
    int (&p2)[5] = array;

    cout << sizeof(array) << endl; // 20
    cout << sizeof(p) << endl;     // 8
    cout << sizeof(p1) << endl;     // 8
    cout << sizeof(p2) << endl;     // 20 引用就是个别名 用p2就相当于使用array

    return 0;

}
#endif

int main () {
    int a = 10; // 左值，它有内存，有名字，值可以修改的

    int &b = a;

    // c++11提供了右值引用
    int &&c = 20; // 20是右值，没内存，没名字  汇编上先将值存放在一个栈上的临时变量 再将这个临时变量的地址放在变量c中
    // 一个右值引用变量，本身是一个左值
    const int &d = 20; // 与右值引用的汇编语言一样
    return 0;
}