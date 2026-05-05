//
// Created by marquezzz on 2026/5/1.
//
#include <iostream>


/*
 * Q1:main函数调用sum函数，sum执行完以后，怎么知道回到那个函数中
 *
 * Q2:sum函数执行完，回到main以后，怎么知道从哪行指令继续运行？
 *
 */
int sum(int a, int b)
{
    int temp = 0;
    temp = a+b;
    return temp;
}

int main(){
    int a = 10;
    int b = 20;

    int ret = sum(a,b);
    std::cout<<"ret: " << ret << std::endl;

    return 0;
}