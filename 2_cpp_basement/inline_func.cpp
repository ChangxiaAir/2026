//
// Created by marquezzz on 2026/5/2.
//

#include<iostream>

using namespace std;

/*
 * inline函数和普通函数的区别？
 * inline函数：在编译过程中，就没有函数的调用开小了，在函数的调用点直接把函数的代码进行展开处理了
 * inline函数不再生成相应的函数符号
 *
 * inline只是建议编译器把这个函数处理成内联函数
 * 但是不是所有的inline都会被编译器处理成内联函数 比如递归，编译器不执行代码，只是生成代码，无法知道执行多少次
 * debug版本上，inline是不起作用的；inline只有在release版本下才能出现
 * g++ -c inline_func.cpp -O2 之后 objdump -t inline_func.o没有add_int的符号了
 */

int sum(int x, int y) {
    return x+y;
}

inline int add_int(int a, int b) {
    return a+b;
}

int main() {
    int a = 10;
    int b = 20;

    int ret = sum(a,b);
    // 对于普通函数的调用过程，此处有标准的函数调用过程 参数压栈， 函数栈帧的开辟和回退过程
    // 有函数调用的开销
    // x+y 只有三条指令，mov add mov 但是一个函数调用引进的指令条数远远大于函数本身要完成的功能的指令数目

    int r = add_int(a,b);

    return 0;
}