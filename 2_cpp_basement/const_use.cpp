//
// Created by marquezzz on 2026/5/2.
//
#include<iostream>
#include<typeinfo>
using namespace std;

/*
 * const 指针 引用 在函数当中的引用
 * const怎么理解？
 * const修饰的变量不能够再作为左值！！！ 初始化完成后，值不能被修改！！！
 *
 * c和c++中的const区别是什么？
 * const的编译方式不同，c中，const就是当做一个变量来编译生成指令的。
 * c++中，所有出现const常量名字的地方，都被常量的初始化替换了！！！
 * c语言中的const:
 *      const修饰的量，可以不用初始化
 *      不叫常量，叫做常变量
 *
 *      void main(){
 *          const int a = 20;
 *          const int b;
 *
 *          int arary[a] ={} // 错误的，不能当做常量来用
 *
 *          int *p = (int *)&a;
 *          *p = 300;
 *
 *          printf("%d %d %d \n", a, *p, *(&a)); // 300 300 300
 *      }
 *
 * c++中的const:
 *      必须初始化
 *      叫做常量 因为初始值不是立即数，是一个变量
 *
 *      int main(){
 *          const int a = 20; // 后面的指针把这块内存的值已经改了
 *          int array[a] = {}; //正确
 *          int *p = (int *)&a;
 *          *p = 300;
 *          printf("%d %d %d \n", a, *p, *(&a)); // 20 300 20  *(&a)编译阶段被替换为20
 *          return 0；
 *      }
 *      要是 int b = 20;
 *      const int a = b; // 跟c中的一模一样了
 *      int array[a] = {}; // 此处a被替换为b 错误的
 *      此时叫做常变量了，因为初始值不是立即数，是一个变量
 *
 * const a = 10; a就不能再作为左值了
 */
int main() {
    int a = 10;
    a = 20;

    const int b = 20;
    b = 30;

    return 0;
}