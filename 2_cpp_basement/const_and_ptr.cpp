//
// Created by marquezzz on 2026/5/2.
//

#include<iostream>
#include<typeinfo>
using namespace std;

/*
 * const和一级指针的结合
 * const和二级（多级）指针的结合
 *
 * const 修饰的量 叫常量
 * 和普通变量的区别是什么？ c++有两点区别 1、编译方式不同，对于常量，编译过程中出现的常量都会被替换
 *                                  2、初始化完成后不能作为左值了
 *
 * const修饰的量常出现的错误是：
 * 1、常量不能再作为左值 《= 直接修改常量的值
 * 2、不能把常量的地址泄露给一个普通的指针或者普通的引用变量 《= 可以间接修改常量的值
 *
 * const 和一级指针的结合
 * c++语言规范：const修饰的是离他最近的类型
 *
 * const int *p = &a;  => *p = 20(x) p = &b(v)
 * 可以任意指向不同的int类型的内存，但是不能通过指针间接修改指向的内存的值
 * int const *p; 同上
 *
 * int *const p = &a;
 * 这个指针p现在是常量，不能再指向其他内存，但是可以通过指针解引用修改指向的内存的值
 *
 * const int *const p = &a;
 * 这个指针不能再指向其他内存，也不能通过指针间接修改指向的内存的值
 *
 *
 * 总结：
 * const和指针的类型转换公式
 * int* <= const int*   (x)
 * const int* <= int*   (v)
 *
 * int** <= const int ** (x)
 * const int ** <= int ** (x)
 *
 * int** <= int *const* 等价于 * <= const* (x)
 *
 * int *const* <= int** 等价于 const * <= * (v)
 */

int main01() {

    int h = 100;
    const int *hp = &h; // hp存放的是整型常量的地址
    // int *hq = hp; // int* <= const int* (x)
    cout << typeid(hp).name() << endl;

    int *q1 = nullptr;
    int *const q2 = nullptr;
    cout << typeid(q1).name() << endl;
    cout << typeid(q2).name() << endl;
    // const如果右边没有指针*的话，const是不参与类型的
    // 只是表示当前的q2是个常量，不能作为左值


    int ah = 10;
    int *ap = &ah;
    const int *ap1 = &ah; // const int * <= int *
    int *const ap2 = &ah; // int * <= int *  const如果右边没有指针*的话，const是不参与类型的
    int *ap3 = ap2; // int * <= int * (v)

    const int a = 10;
    // int *p = &a; // int * <= const int* error

    int const *p = &a;
    const int *p1 = &a; // 内容不可变

    // int *const p2 = &a; // 指向不可变 错误的

    return 0;
}


/*
 *
 * const和二级指针的结合
 *
 * 0x100  a  10        **pp *p a = 10
 * 0x200  p  0x100     *pp p = 0x100
 * 0x400  pp 0x200     pp  = 0x200
 *
 * 二级指针的三种表示方式：
 * const int **pp;  // **pp 不能被赋值
 * int *const* pp;  // *pp 不能被赋值
 * int **const pp;  // pp 不能被赋值
 */

int main() {
    int a = 10;

    int *p = &a;
    // const int **pp = &p; //  const int ** <= int ** (x) 不能使用 int ** 初始化 const int ** 类型的局部变量 'pp'

    return 0;
}
