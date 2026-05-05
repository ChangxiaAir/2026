//
// Created by marquezzz on 2026/5/3.
//

#include <iostream>
using namespace std;

/*
 * 对象的深拷贝和浅拷贝
 *
 * 对象默认的拷贝构造是做内存的数据拷贝
 * 关键是对象如果占用外部资源，那么浅拷贝就出现问题了
 */

class SeqStack {
public:
    // 构造函数
    SeqStack(int size=10) {
        cout << "SeqStack()" << endl;
        _pstack = new int[size];
        _size = size;
        _top = -1;
    }

    // 自定义拷贝构造函数？ <= 因为对象的浅拷贝现在有问题了
    SeqStack(const SeqStack &src) {
        cout << "SeqStack(const SeqStack &src)" << endl;
        _pstack = new int[src._size];
        for (int i=0; i<= src._top; i++) {
            _pstack[i] = src._pstack[i];
        }
        _size = src._size;
        _top = src._top;
    }

    // 赋值重载函数
    void operator=( const SeqStack &src ) {
        // 赋值意味着原来的两个对象都已经存在了，要先把左边的对象的内存释放掉
        cout << "operator=" << endl;
        delete [] _pstack;

        _pstack = new int[src._size];
        for (int i=0; i<= src._top; i++) {
            _pstack[i] = src._pstack[i];
        }
        _size = src._size;
        _top = src._top;
    }

    ~SeqStack() {
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
        _top--;
    }

    int top() {
        return _pstack[_top];
    }

    bool full() {
        return _top == _size-1;
    }

    bool empty() {
        return _top == -1;
    }

private:
    int *_pstack;
    int _size;
    int _top;

    void resize() {
        int *ptmp = new int[_size*2];
        for (int i=0; i<_size; i++) {
            ptmp[i] = _pstack[i]; // 此处为什么不memcpy(dest, src, size); 和realloc ???
        }
        delete [] _pstack;
        _pstack = ptmp;
        _size*=2;
    }
};

int main() {

    SeqStack s; // 没有提供任何构造函数的时候，会为你生成默认构造和默认析构，是空函数
    SeqStack s1(5);

    // 拷贝构造函数
    // SeqStack s2(s1);  // 等同于SeqStack s3 = s1;
    SeqStack s3 = s1; // 等同于SeqStack s2(s1);

    // s3 = s1; 是有问题的，会把s3指向的内存丢了，转而指向s1的那块内存 在定义operator=后就没问题了
    s3 = s1;
    return 0;
}

// free(): double free detected in tcache 2
// 拷贝构造
// SeqStack s1(5);
// SeqStack s2 = s1;

// 赋值重载
// SeqStack s1, s2;
// s2 = s1;
