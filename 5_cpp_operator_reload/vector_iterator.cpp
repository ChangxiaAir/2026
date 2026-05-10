//
// Created by marquezzz on 2026/5/10.
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

/*
 * 容器的空间配置器allocator 做4件事
 * 内存开辟/内存释放
 * 对象构造/对象析构
 *
 */
// 定义容器的空间配置器，和C++标准库的allocator实现一样
template<typename T>
class Allocator {
    public:
    // 负责内存开辟
    T *allocate(size_t size) {
        return (T*)malloc(sizeof(T) * size);
    }

    // 负责内存释放
    void deallocate(T *p) {
        free(p);
    }

    // 负责构造对象 指定的地址里面构造一个值为value的对象
    void construct(T *p, const T &val) {
        // 定位new
        new (p) T(val); // T(val)会调用T类型对象的一个拷贝构造
    }

    // 负责对象析构
    void destroy(T *p) {
        p->~T(); // ~T()代表了T类型的析构函数
    }

};

// 容器底层内存开辟、内存释放、对象构造和析构，都通过allocator空间配置器来实现
template <typename T, typename Alloc= Allocator<T> > // 模板名称+参数列表=类型名
class vector {
public:
    vector(int size = 5, const Alloc &alloc = Allocator<T>())
        :_allocator(alloc)
    {
        // 存在的问题：需要把内存开辟和对象构造分开处理

        // _first = new T[size];
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }

    ~vector() {
        // delete [] _first;
        for (T *p = _first; p != _last; ++p) {
            _allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构操作
        }
        _allocator.deallocate(_first); // 释放堆上的数组内存
        _first = _last = _end = nullptr;
    }

    vector(const vector<T> &rhs) {
        int size = rhs._end - rhs._first;
        // _first = new T[size];
        _first = _allocator.allocate(size);
        int len = rhs._last - rhs._first;
        for (int i = 0; i<len ; i++) {
            // _first[i] = rhs._first[i];
            _allocator.construct(_first+i, rhs._first[i]);
        }

        _last = _first + len;
        _end = _first + size;
    }

    vector<T>& operator=(const vector<T>& rhs) {
        if (this == &rhs) {
            return *this;
        }
        // delete [] _first;
        for (T *p = _first; p != _last; ++p) {
            _allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构操作
        }
        _allocator.deallocate(_first); // 释放堆上的数组内存
        int size = rhs._end - rhs._first;
        // _first = new T[size];
        _first = _allocator.allocate(size);
        int len = rhs._last - rhs._first;
        for (int i = 0; i<len ; i++) {
            // _first[i] = rhs._first[i];
            _allocator.construct(_first+i, rhs._first[i]);
        }

        _last = _first + len;
        _end = _first + size;

        return *this;
    }

    void push_back(const T &element) { // 向容器末尾添加元素
        // 存在的问题：需要把对象的析构和内存释放分离开来
        if (full()) {
            expand();
        }
        // *_last = element;
        // _last = _last + 1;
        _allocator.construct(_last, element);
        _last++;
    }

    void pop_back() {
        //从容器末尾删除元素
        if (empty()) {
            return;
        }
        --_last; // 不仅要把_last--,还需要析构删除的元素
        _allocator.destroy(_last);
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

    class iterator {
    public:
        iterator(T* p=nullptr):_p(p){}
        void operator++() {
            ++_p;
        }
        bool operator!=(const iterator &rhs) const {
            return _p != rhs._p;
        }
        T& operator*() const {
            return *_p;
        }
    private:
        T *_p;
    };
    iterator begin() const {
        return iterator(_first);
    }
    iterator end() const {
        return iterator(_last);
    }

private:
    T *_first; // 指向数组起始地址的位置
    T *_last; // 指向数组中有效元素后继的位置
    T *_end;   // 指向数组空间的后继位置
    Alloc _allocator; // 定义容器的空间配置器对象

    void expand() {
        int len = _end - _first;
        // T *ptmp = new T[2*len];
        T *ptmp = _allocator.allocate(2*len);
        for (int i = 0; i<len; i++) {
            _allocator.construct(ptmp+i, _first[i]);
            // ptmp[i] = _first[i];
        }
        // delete [] _first;
        for (T *p = _first; p != _last; ++p) {
            _allocator.destroy(p);
        }
        _allocator.deallocate(_first);

        _first = ptmp;
        _last = _first + len;
        _end = _first + len + len;
    }
};

class Test {
    public:
    Test() { cout << "Test constructor" << endl; }
    ~Test() { cout << "Test destructor" << endl; }
    Test(const Test &) { cout << "Test copy constructor" << endl; }
};
int main() {
#if 0
    vector<Test> v; // 构造默认的size个Test对象  原因在于vector的构造函数 new 开辟空间+构造对象
    /*
    *g++ -o implement_vector_allocator implement_vector_allocator.cpp  && ./implement_vector_allocator
    Test constructor
    Test constructor
    Test constructor
    Test constructor
    Test constructor
    Test destructor
    Test destructor
    Test destructor
    Test destructor
    Test destructor
    */

    // 默认构造size个对象，new的时候空间开辟+对象构造
    // 遇到上面的问题的时候 我们如何解决？
    // 需要把内存开辟和对象构造分开处理

    // 默认size次对象析构
    // delete 会把_first指针指向数组的元素都当做一个Test对象析构一下
    // 现实情况是_first指向的数组里面可能只有几个有效的元素，在不需要容器的时候，把这些有效元素析构掉
    // 析构容器有效的元素，然后释放_first指向的堆内存空间

    Test t1, t2, t3, t4;
    cout<<"1、------------------------"<<endl;
    v.push_back(t1);
    v.push_back(t2);
    v.push_back(t3);
    v.push_back(t4);
    cout<<"2、------------------------"<<endl;
    v.pop_back();
    cout<<"3、------------------------"<<endl;
#endif

    vector<double> v;
    v.push_back(0.0);
    v.push_back(1.0);
    v.push_back(2.0);
    vector<double>::iterator it = v.begin();
    for (; it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}

/*
 *
在 vector<Test> v;
此时的v中有默认值size个Test对象
Test t1;
v.push_back(t1); 相当于给已有的Test对象赋值
我们的期望是在v中逐个添加Test1对象

当我们pop_back对象的时候，对象可能占用了外部资源，并不只是--_last
delete 对象可以吗？
不可以 我们只是想析构这个对象，并不释放这个对象占有的堆内存
而delete 析构对象+free内存

pop_back 只需要析构对象，要把对象的析构和内存释放分离开来
 */