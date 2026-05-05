//
// Created by marquezzz on 2026/5/2.
//
#include<iostream>

using namespace std;

/*
 *形参带默认值的函数
 *1、给默认值得时候，从右往左给
 *2、有默认形参的时候，会少一次mov指令，效率高
 *3、定义的时候给默认值可以，声明的时候行不行？ 可以的，不过声明处给了默认参数，定义时就不能给了
 *4、形参给默认值得时候，不管是定义处给，还是声明处给，形参默认值只能出现一次
 *
 */

int sum(int a=10, int b=20);

int main() {
    int a = 10;
    int b = 20;

    int ret = sum(a,b);
    /*
     * mov eax, dword ptr[ebp-8]
     * push eax
     * mov ecx, dword ptr[ebp-4]
     * push ecx
     * call sum
     *
     */

    cout<<"ret:"<<ret<<endl;

    ret = sum(a);
    /*
     * push 14H
     * mov ecx, dword ptr[ebp-4]
     * call sum
     */

    ret = sum();

    /*
     * push 14H
     * push 0AH
     * call sum
     */

    ret = sum(a,40);

    /*
     * push 28H
     * mov ecx, dword ptr[ebp-4]
     * call sum
     */
    return 0;
}

int sum(int a, int b) {
    return a+b;
}