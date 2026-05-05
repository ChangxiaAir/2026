//
// Created by marquezzz on 2026/5/3.
//

#include <iostream>
using namespace std;

/*
 * 构造函数和析构函数
 * OOP实现一个顺序栈
 *
 */
#if 0
class SeqStack {
public:
    void init(int size=10) {
        _pstack = new int[size];
        _top = -1;
        _size=size;
    }

    void release() {
        delete [] _pstack;
        _pstack = nullptr;
    }

    void push(int val) {
        if (full()) {
            resize();
        }

        _pstack[++_top] = val;
    }

    void pop() {
        if (empty()) return;
        --_top;
    }

    int top() {
        return _pstack[_top];
    }
    bool empty() { return _top == -1; }
    bool full() { return _top == _size-1; }


private:
    int *_pstack; // 方便空间的增长
    int _top; // 记录栈顶位置
    int _size; // 栈的总的大小

    void resize() {
        int *ptmp = new int[_size*2];
        for (int i=0; i<_size; i++) {
            ptmp[i] = _pstack[i];
        } // 为什么不用memcpy(ptmp, _pstack, sizeof(int)*_size); 代替for循环？？？ realloc 两者都是对内存的拷贝，对对象来说会有问题？
        delete [] _pstack;
        _pstack = ptmp;
        _size *=2;
    }
};


int main () {
    SeqStack s;
    s.init(5);
    for (int i=0; i<15; i++) {
        s.push(rand() % 100);
    }

    while (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }

    s.release();
    return 0;
}
#endif

/*
 *
 * 构造函数和析构函数
 * 函数的名字和类名一样
 * 没有返回值
 */

class SeqStack {
public:
    // 构造函数是可以带参数的，因此可以提供多个构造参数，叫做构造函数的重载
    SeqStack(int size=10) {
        cout<< this << " SeqStack()" <<endl;
        _pstack = new int[size];
        _top = -1;
        _size=size;
    }

    /*
    void init(int size=10) {
        _pstack = new int[size];
        _top = -1;
        _size=size;
    }

    */
    // 析构函数是不带参数的，所以析构函数只能有一个
    ~SeqStack() {
        cout<< this << " ~SeqStack()" <<endl;
        delete [] _pstack;
        _pstack = nullptr;
    }

    /*
    void release() {
        delete [] _pstack;
        _pstack = nullptr;
    }
    */

    void push(int val) {
        if (full()) {
            resize();
        }

        _pstack[++_top] = val;
    }

    void pop() {
        if (empty()) return;
        --_top;
    }

    int top() {
        return _pstack[_top];
    }
    bool empty() { return _top == -1; }
    bool full() { return _top == _size-1; }


private:
    int *_pstack; // 方便空间的增长
    int _top; // 记录栈顶位置
    int _size; // 栈的总的大小

    void resize() {
        int *ptmp = new int[_size*2];
        for (int i=0; i<_size; i++) {
            ptmp[i] = _pstack[i];
        } // 为什么不用memcpy(ptmp, _pstack, sizeof(int)*_size); 代替for循环？？？ realloc 两者都是对内存的拷贝，对对象来说会有问题？
        delete [] _pstack;
        _pstack = ptmp;
        _size *=2;
    }
};

int main () {
    SeqStack s(5);

    for (int i=0; i<15; i++) {
        s.push(rand() % 100);
    }

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }

    cout << "&s==" << &s << endl;

    // s.~SeqStack();
    // s.push(333);    // 堆内存的非法访问
    // 析构函数调用之后 再去访问s的成员函数 就会出错

    return 0;


}

// main 函数中的对象s定义在stack栈上
// 如果在main函数外面定义一个对象s,那么它就属于全局变量 在数据段
// SeqStack *sq = new SeqStack(10); sq 在堆上面 sq->push(90); 堆上面的对象一定要手动释放 delete sq;
//          delete会先调用对象的析构函数sq->~SeqStack()+然后再free(sq)
//          new SeqStack(10) 先是malloc内存开辟+SeqStack(10)对象构造