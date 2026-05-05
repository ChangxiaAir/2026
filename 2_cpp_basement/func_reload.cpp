//
// Created by marquezzz on 2026/5/2.
//



/*
 * 函数重载
 * 1、c++为什么支持函数重载，C语言不支持函数重载
 * 因为c++代码产生函数符号的时候，函数名+参数列表类型组成的；而c代码产生函数符号的时候，函数名来决定
 * 2、函数重载需要注意些什么？
 * 3、c++和c语言代码之间如何相互调用
 *
 * 什么是函数重载？
 * 1、一组函数，其中函数名相同，参数列表的个数或者类型不同，那么这一组函数就称作函数重载
 * 2、一组函数要称得上函数重载，一定先是处在同一个作用域当中的；局部有相同的声明，会都先去匹配，导致错误
 * 3、const或者volatile的时候，是怎么影响形参类型的？
 * 4、一组函数，函数名相同，参数列表也相同，仅仅是返回值不同，不叫重载
 *
 * 什么是多态？
 * 静态（编译时期）的多态：函数重载
 * 动态（运行时期）的多态：
 *
 * 什么是函数重载？函数名相同、参数类型不同、处在同一作用域下的一组函数；
 *      c++支持函数重载是因为c++代码在产生函数符号的时候，是通过函数名和参数列表类型来完成的
 *
 * c调用c++: 无法直接调用了，怎么办？把C++源码扩在extern "C"里面
 * c++调用c：无法直接调用了，怎么办？把c函数的声明扩在extern "C"里面
 * 用extern "C"来解决 .c文件要用gcc -c test1.c g++ func_reload.cpp test1.o -o test
 * c中的符号是sum .text;但c++中的符号是sum_int_int .text 会显示*UND*
 */

#include<iostream>
#include<typeinfo> // 查看类型
using namespace std;


/*
 * 只要是c++编译器，都内置了__cplusplus这个宏名字
 */
#ifdef __cplusplus
extern "C" {
#endif
    int sum(int a, int b) {
        return a + b;
    }
#ifdef __cplusplus
}
#endif

#if 0
extern "C" // c++使用c的代码实现
{
    int sum(int a, int b);
}

int main_() {
    int ret = sum(10,20);
    cout << "cpp_file_sum:"<< ret << endl;
    return 0;
}

extern "C" { // c中调用c++代码，将c++的源码包围在extern “C“中
    int add_int(int a, int b) {
        int ret = sum(10,20);
        cout << "cpp_file_sum:"<< ret << endl;
        return a + b;
    }
}
#endif

#if 0
void func(int a) {}
// void func(const int a) {}  // 带const的时候和不带const是一样的
int main() {
    int a = 10;
    const int b = 10;
    cout << typeid(a).name() << endl; // int
    cout << typeid(b).name() << endl; // int
    return 0;
}
#endif


#if 0
bool compare(int a, int b) {
    cout <<"compare_init_int"<< endl;
    return a > b;
}

bool compare(double a, double b) {
    cout <<"compare_init_double"<< endl;
    return a > b;
}

bool compare(const char *a, const char *b) {
    cout <<"compare_char*_char*"<< endl;
    return strcmp(a,b) > 0;
}

int main() {

    bool compare(int a, int b); // 函数的声明 全局有三个函数的定义；后面的compare会先使用局部的声明，导致冲突
    compare(10,20);
    compare(10.0, 20.0);
    compare("aaa", "bbb");

    return 0;

}
#endif

