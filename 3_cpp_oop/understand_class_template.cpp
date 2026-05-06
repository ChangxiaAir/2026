//
// Created by marquezzz on 2026/5/6.
//

#include <cstring>
#include <iostream>
using namespace std;

/*
 * c++函数模板
 * 模板的意义：对类型也可以进行参数化了
 *
 * 函数模板 ===>编译器不编译，因为类型不知道
 * 模板的实例化===>函数调用点进行实例化
 * 模板函数 ===> 才是要被编译器编译的代码
 *
 * 模板类型参数
 * 模板非类型参数
 *
 * 模板的实参推演 ===》 可以根据用户传入的实参的类型，来推导出模板的具体类型
 * 模板的特例化
 * 函数模板、模板的特例化、非模板函数的重载关系
 *
 * 模板代码是不能在一个文件中定义，在另一个文件中使用的
 * 模板代码调用之前，一定要看到模板定义的地方，这样的话，模板才能够进行正常的实例化，产生能够被编译器编译的代码
 * 所以，模板代码都是放在头文件中的，然后再源文件中直接进行#include包含
 *
 */

template <typename T> // 定义一个模板参数列表 类型参数typename
bool compare(T a, T b) { // compare是一个函数模板
    cout << "compare template " << endl;
    return a > b;
}

/*
 * 在函数调用点，编译器用用户指定的类型，从原模板实例化一份函数代码出来
 *
 * 下面的函数是真真正正需要编译的代码，叫做模板函数
 * bool compare<int>(int a , int b){ return a>b;}
 * bool compare<double>(double a , double b){ return a>b;}
 * bool compare<const char*>(const char* a , const char* b)
 * {
 *      return a>b; // 两个const char*比较的是两者的地址的大小，这样比较是没有意义的
 *                  // 目的是为了比较"aaa"和"bbb"的ASCII的字典顺序
 *                  // 实际上需要的是return strcmp(a,b);
 * }
 */

// 针对compare函数模板，提供const char*类型的特例化版本
template<>
bool compare<const char*>(const char* a, const char* b) { // #1
    cout << "compare<const char*> " << endl;
    return strcmp(a, b)>0;
}

// 非模板函数 - 普通函数
// #1 和 #2 的函数名完全不一样，谈不上重载
bool compare(const char* a, const char* b) { // #2
    cout << "normal compare<const char*> " << endl;
    return strcmp(a, b)>0;
}
int main() {

    // 函数的调用点
    compare<int>(10 ,20); // 函数模板名 参数列表
    compare<double>(10.5 ,20.5);

    // 调用第一次函数的调用点的函数即可，不用产生新的模板函数
    compare(20,5); // 此处也可以正常运行，原因在于模板的实参推演，可以根据用户传入的实参的类型，来推导出模板的具体类型

    // compare(20,20.5); 错误用法
    compare<int>(20,20.5); // 正确 将20.5转换为整型

    // 编译器优先把compare处理成函数名字，若没有该函数，才去找compare模板
    compare("aaa", "bbb"); // T是 const char *

    compare<const char*>("aaa", "bbb");

    // 对于某些类型来说，依赖编译器默认实例化的模板代码，代码处理逻辑是有错误的
    // 在这里进一步引出了模板的特例化 特殊在哪？（不是编译器提供的，而是用户提供的）
    return 0;
}

/*
 *
 * 能否分文件声明、定义、使用模板函数代码
 *
 * // 模板的声明
 * template<typename T>
 * bool compare(T a, T b); // 等价于 compare<const char*> *UND*
 * bool compare(const char* a, const char* b) // 等价于 compare *UND*
 * 别的函数中定义上面这两个函数
 *     可以正常调用 compare("aaa", "bbb"); // T是 const char *
 *     可以正常调用 compare<const char*>("aaa", "bbb");
 *     无法正常调用 compare<int>(20,20.5);
 * 在定义函数模板的地方
 * 告诉编译器，进行指定类型的模板实例化
 * template bool compare<int>(int,int);
 * template bool compare<double>(double,double);
 */