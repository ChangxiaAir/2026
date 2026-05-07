//
// Created by marquezzz on 2026/5/7.
//

#include <iostream>
using namespace std;

/*
 * 类模板 ===> 实现一个C++ STL里面的一个顺序容器vector 向量容器
 * 容器：
 * 相较于STL中的vector，目前缺少 空间配置器 allocator
 */

/*
*   template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class vector : protected _Vector_base<_Tp, _Alloc>
    {}
 */

template <typename T>
class vector {
public:
    vector(int size = 5) {
        _first = new T[size];
        _last = _first;
        _end = _first + size;
    }

    ~vector() {
        delete [] _first;
        _first = _last = _end = nullptr;
    }

    vector(const vector<T> &rhs) {
        int size = rhs._end - rhs._first;
        _first = new T[size];
        int len = rhs._last - rhs._first;
        for (int i = 0; i<len ; i++) {
            _first[i] = rhs._first[i];
        }
        _last = _first + len;
        _end = _first + size;
    }

    vector<T>& operator=(const vector<T>& rhs) {
        if (this == &rhs) {
            return *this;
        }
        delete [] _first;
        _first = _last = _end = nullptr;

        int size = rhs._end - rhs._first;
        _first = new T[size];
        int len = rhs._last - rhs._first;
        for (int i = 0; i<len ; i++) {
            _first[i] = rhs._first[i];
        }
        _last = _first + len;
        _end = _first + size;

        return *this;
    }

    void push_back(const T &element) { // 向容器末尾添加元素
        if (full()) {
            expand();
        }
        *_last = element;
        _last = _last + 1;
    }

    void pop_back() {
        //从容器末尾删除元素
        if (empty()) {
            return;
        }
        --_last;
    }

    T back() const {
        // 返回容器末尾的元素
        return *(_last - 1);
    }

    bool empty() const {
        return _first == _last;
    }

    bool full() const {
        return _last == _end;
    }

    int size() const {
        return _last - _first;
    }

private:
    T *_first; // 指向数组起始地址的位置
    T *_last; // 指向数组中有效元素后继的位置
    T *_end;   // 指向数组空间的后继位置
    void expand() {
        int len = _end - _first;
        int *ptmp = new T[2*len];

        for (int i = 0; i<len; i++) {
            ptmp[i] = _first[i];
        }
        delete [] _first;
        _first = ptmp;
        _last = _first + len;
        _end = _first + len + len;
    }
};

int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);
    v.push_back(10);
    v.push_back(11);
    v.push_back(12);
    cout << v.size() << endl;
    cout << v.back() << endl;
    v.pop_back();
    v.pop_back();
    cout << v.size() << endl;
    cout << v.back() << endl;
    return 0;
}