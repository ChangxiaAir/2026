//
// Created by marquezzz on 2026/5/6.
//
#include <iostream>
using namespace std;

/*
 * 指向类成员（成员变量和成员方法）的指针
 *
 * 指向类成员的指针和之前的普通指针有什么不一样
 */

class Test {
public:
    void func() { cout << "call Test::func"<<endl; }
    static void static_func() { cout << "call Test::static_func"<<endl; }
    int ma;
    static int mb;
};

int Test::mb = 0;
int main () {

#if 0
    // #1 指向成员变量的指针 ①普通成员 ②静态成员
    Test t1; // 栈上的对象
    Test *t2 = new Test(); // 堆上的对象
    // error: cannot convert ‘int Test::*’ to ‘int*’
    // int *p = &Test::ma;  // 当我们谈论普通成员的时候，一定要指定对象，没有对象是没有意义的

    int Test::*p = &Test::ma; // 定义指针指向类的普通成员变量，需要加一个类的作用域
    // *p = 20;
    t1.*p = 20;
    cout << t1.*p << endl;

    t2->*p = 30;
    cout << t2->*p << endl;

    int *p1 = &Test::mb; // 静态成员变量
    *p1 = 42;
    cout << *p1 << endl;

    delete t2;
#endif

    // #2 指向成员方法的指针 ①普通方法 ②静态方法
    Test t3; // 栈上的对象
    Test *t4 = new Test(); // 堆上的对象

    // error: cannot convert ‘void (Test::*)()’ to ‘void (*)()’ in initialization
    // void (*pfunc)() = &Test::func;
    // (*pfunc)();
    void (Test::*pfunc)() = &Test::func;
    (t3.*pfunc)();
    (t4->*pfunc)();

    void (*pfunc1)() = &Test::static_func;
    (*pfunc1)();

    delete t4;
    return 0;
}