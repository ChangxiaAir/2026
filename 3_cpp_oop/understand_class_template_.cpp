//
// Created by marquezzz on 2026/5/7.
//

#include <algorithm>
#include <iostream>
using namespace std;

/*
 * 类模板 => 实例化 => 模板类
 */

template <typename T>
class SeqStack {
// 模板名称 +类型参数列表 = 类名称
public:
    // 构造函数和析构函数名不用加<T>,其他出现模板的地方都加上类型参数列表
    SeqStack(int size=10)
        : _pstack(new T[size])
        , _top(-1)
        , _size(size) {}

    // 包含了外部的对象，需要手动实现析构
    ~SeqStack() {
        delete[] _pstack;
        _pstack = nullptr;
    }

    SeqStack(const SeqStack<T> &src)
        : _top(src._top)
        ,_size(src._size)
    {
        _pstack = new T[_size];
        for (int i = 0; i < _top; i++) {
            _pstack[i] = src._pstack[i];
        }
    }
    SeqStack<T> &operator=(const SeqStack<T> &src) {
        if (this == &src) {
            return *this;
        }
        delete[] _pstack;
        _top = src._top;
        _size = src._size;
        _pstack = new T[_size];
        for (int i = 0; i < _top; i++) {
            _pstack[i] = src._pstack[i];
        }
    }

    void push(const T &x);
    void pop(){
        if (empty()) return;
        _top--;
    }
    T top() const { // 常对象---常对象和普通对象都能调用， 但是写成普通方法，就只能普通对象调用了 跟this指针的类型有关系
        return _pstack[_top];
    }

    bool empty() const{
        return _top == -1;
    }
    bool full() const{
        return _top == _size-1;
    }

    // 类中定义的对象有指向外部的堆内存，要实现拷贝构造和赋值重载


private:
    T *_pstack;
    int _top;
    int _size;

    // 顺序栈底层数组按2倍的方式扩容
    void expand() {
        T *ptmp = new T[_size*2];
        for (int i = 0; i < _top; i++) {
            ptmp[i] = _pstack[i];
        }
        delete[] _pstack;
        _pstack = ptmp;
        _size *= 2;
    }

};

template <typename T>
void SeqStack<T>::push(const T &x)
{
    if (full()) {
        expand();
    }
    _pstack[++_top] = x;
}

int main() {

    // 能调用到的方法才会被实例化

    SeqStack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);
    s1.push(6);
    s1.pop();
    cout << s1.top() << endl;
    s1.pop();
    if (!s1.empty()) {
        cout << s1.top() << endl;
    }

    return 0;
}