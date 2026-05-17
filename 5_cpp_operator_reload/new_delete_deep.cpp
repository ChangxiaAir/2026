//
// Created by marquezzz on 2026/5/16.
//
#include<iostream>
using namespace std;

/*
 * new和delete运算符的重载
 *
 * 1、new和malloc的区别？
 * a. malloc是按字节开辟内存的；new开辟内存时需要指定类型 new int[10]
 *      所以malloc开辟内存返回的都是void*  new-> int*
 * b. malloc只负责开辟空间，new不仅仅有malloc的功能，可以进行数据的初始化
 *  new int(20);    new int[10]();
 * c. malloc开辟内存失败返回nullptr指针; new抛出的是bad_alloc类型的异常
 * 2、free和delete的区别？
 * delete:调用析构函数；再free
 *
 * new -> operator new 的调用
 * delete -> operator delete 的调用
 * echo "_ZdlPvm@plt" | c++filt
 *
 *
 * new type[int] 会多开辟一块内存 delete []和delete开始释放的位置不对
 *
 *
 * 自定义的类类型 有析构函数，为了调用正确的析构函数，那么开辟对象数组的时候就会多开辟8个字节，记录对象的个数
 */

// 先调用operator new开辟内存空间，然后调用对象的构造函数（初始化）
void* operator new(size_t size) {
    void* p = malloc(size);
    if (p == nullptr) {
        throw bad_alloc();
    }
    cout << "operator new addr: "<< p << endl;
    return p;
}

// delete p; 调用p指向对象的析构函数、再调用operator delete释放内存空间
void operator delete(void* p) {
    cout << "operator delete addr: "<< p << endl;
    free(p);
}

void* operator new[](size_t size) {
    cout<<"size= "<<size<<endl;
    void* p = malloc(size);
    if (p == nullptr) {
        throw bad_alloc();
    }
    cout << "operator new[] addr: "<< p << endl;
    return p;
}

// delete p; 调用p指向对象的析构函数、再调用operator delete释放内存空间
void operator delete[](void* p) {
    cout << "operator delete[] addr: "<< p << endl;
    free(p);
}

#if 0
int main() {
    try {
        int *p = new int;
        delete p;

        int *q = new int[10];
        delete [] q;
    }
    catch (const bad_alloc &err) {
        cout << err.what() << endl;
    }

    return 0;
}
#endif

class Test {
    public:
    Test(int data=10):ptr(new int(data)){cout<<"Test()"<<endl;}
    ~Test(){ delete ptr; cout<<"~Test()"<<endl;}
private:
    int *ptr;
};

int main() {

    // Test *t = new Test();
    // delete []t; // 错误了 原因在于他不像new []多开辟了一块内存用来存放开辟内存块的数量
    // new []和 delete p; 搭配会段错误，重复释放同一块地址的内存


    Test *p2 = new Test[5]; // 开辟的内存块大小为48=8*5+8 其中的一个8是用来描述存储的对象的个数
    //operator new[] addr: 0x5f482a58f6c0
    // p2: 0x5f482a58f6c8
    cout<<"p2: "<<p2<<endl;

    // operator delete[] addr: 0x6538458cb6c0
    delete []p2;
    // 如果此时调用delete p2; // 直接析构Test[0]对象，free(p2)
    return 0;
}

// 如何实现一个检测内存是否泄漏的工具？