//
// Created by marquezzz on 2026/5/3.
//

#include <iostream>
using namespace std;

/*
 * new和delete
 * new和malloc的区别？
 * delete和free的区别？
 *
 * malloc和free，称作c的库函数
 * new和delete，称作运算符
 *
 * new不仅可以做内存开辟，还可以做内存初始化操作
 *
 * malloc只负责开辟内存，开辟内存失败，是通过返回值和nullptr做比较；
 * 而new开辟内存失败，是通过抛出bad_alloc类型的异常来判断的
 */

int main () {
    int *p = (int*)malloc(sizeof(int));
    if (p == nullptr) {
        return -1;
    }
    *p = 10;
    free(p);

    int *p1 = new int(20);
    delete p1;


    // malloc为数组开辟空间
    int *q = (int *)malloc(sizeof(int)*20);
    if (q == nullptr) {
        return -1;
    }
    free(q);

    // int *q1 = new int[20]; // 只负责在堆上开辟内存，不会初始化
    int *q1 = new int[20]();  // 不仅开辟内存，还会初始化为0
    delete []q1;

    // new 有多少种？
    int *m = new int(20);
    int *m1 = new (nothrow) int;
    const int *m3 = new const int(50);

    // 定位new
    int data = 0;
    int *m4 = new (&data) int(50);

    return 0;
}