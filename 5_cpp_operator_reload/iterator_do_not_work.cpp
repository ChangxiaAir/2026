//
// Created by marquezzz on 2026/5/10.
//

#include <iostream>
using namespace std;

/*
 * 迭代器的失效问题？
 * 1、迭代器为什么会失效？
 * a、当容器调用erase方法后，当前位置到容器末尾元素的所有的迭代器全部失效了
 * b、当容器调用insert方法后，当前位置到容器末尾元素的所有的迭代器全部失效了
 *
 * 首元素 -> 插入点/删除点 -> 末尾元素
 *
 * c、insert来说，如果引起容器内存扩容
 *  原来容器的所有的迭代器就全部失效了
 * d、buto不同容器的迭代器是不能进行比较运算的
 *
 * 2、迭代器失效了以后，问题该怎么解决？
 * 对插入/删除点的迭代器进行更新操作
 *
 *
 */

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

        // erase(it); verify(it._p, last);
        // insert(it,val); verify(it._p, last);
        verify(_last -1, _last);
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

    T& operator[](int i) {
        if (i<0 || i>size()) {
            throw "index out of range";
        }
        return *(_first + i);
    }

    class iterator {
    public:
        friend class vector<T,Alloc>;

        // 新生成当前容器某一个位置元素的迭代器
        iterator(vector<T,Alloc> *pvec, T* p=nullptr):_p(p),_pVec(pvec) {
            Iterator_Base *itb = new Iterator_Base(this, _pVec->_head._next);
            _pVec->_head._next = itb;
        }

        void operator++() {
            // 检查迭代器的有效性
            if (_pVec == nullptr) {
                throw "iterator invalid";
            }
            ++_p;
        }

        bool operator!=(const iterator &rhs) const {
            // 检查迭代器的有效性
            if (_pVec == nullptr || _pVec != rhs._pVec) {
                cout<<"1、here"<<endl;
                throw "iterator incompatable!"; // 异常也是程序结束的一种方式，就不需要return false了
            }
            cout<<"2、here"<<endl;
            return _p != rhs._p;
        }

        T& operator*() { // 不实现为T& operator*() const{}是因为 不仅int data = *it; 还要*it=20;
            // 检查迭代器的有效性
            if (_pVec == nullptr) {
                throw "iterator invalid";
            }
            return *_p;
        }
        const T& operator*() const {
            // 检查迭代器的有效性
            if (_pVec == nullptr) {
                throw "iterator invalid";
            }
            return *_p;
        }
    private:
        T *_p;

        // 当前迭代器迭代的是哪个容器对象
        vector<T, Alloc> *_pVec;
    };

    // 需要给容器提供begin和end方法
    iterator begin() {
        return iterator(this, _first);
    }
    iterator end() {
        return iterator(this, _last);
    }

    // 检查迭代器失效
    void verify(T *first, T *last) {
        Iterator_Base *pre = &this->_head;
        Iterator_Base *it = this->_head._next;
        while (it != nullptr) {
            if (it->_cur->_p > first && it->_cur->_p <= last) {
                // 迭代器失效，把iterator持有的容器指针置为nullptr
                it->_cur->_pVec = nullptr;
                // 删除当前迭代器节点，继续判断后面的迭代器节点是否失效
                pre->_next = it->_next;
                delete it;
                it = pre->_next;
            }else {
                pre = it;
                it = it->_next;
            }
        }
    }
private:
    T *_first; // 指向数组起始地址的位置
    T *_last; // 指向数组中有效元素后继的位置
    T *_end;   // 指向数组空间的后继位置
    Alloc _allocator; // 定义容器的空间配置器对象

    // 容器迭代器失效增加代码
    class Iterator_Base {
        public:
            Iterator_Base(iterator *c=nullptr, Iterator_Base *n=nullptr)
                :_cur(c), _next(n){}

            iterator *_cur;
            Iterator_Base *_next;
    };
    Iterator_Base _head;

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
    vector<int> vec;
    for (int i=0;i<20;i++) {
        vec.push_back(rand()%100+1);
    }
    vector<int>::iterator it=vec.end();
    vec.pop_back();
    vector<int>::iterator it1=vec.end();
    cout<< "aaa"<<(it!=it1) <<endl;
    return 0;
}

#if 0
// 利用stl 的vector看什么情况下迭代器失效，失效后怎么解决
int main() {
    vector<int> vec;
    for (int i=0;i<20;i++) {
        vec.push_back(rand()%100);
        cout<<vec[i]<<" ";
    }
    cout<<endl;


    // 把vec容器中所有的偶数全部删除 有问题#1
    vector<int>::iterator it=vec.begin();
    for (;it!=vec.end();) {
        if (*it % 2 == 0) {
            // #1、迭代器失效的问题，第一次调用erase以后，迭代器it就失效了
            it = vec.erase(it); // 删除之后返回当前位置新的迭代器
            // 删除当前位置的元素之后，后面的元素向前移动，此时迭代器不需要+1
        }else {
            ++it;
        }
    }


    for (int i=0;i<vec.size();i++) {
        cout<<vec[i]<<" ";
    }
    cout<<endl;

    // 给vec容器中所有的偶数前面添加一个小于偶数值1的数字 问题#2
    vector<int>::iterator it1=vec.begin();
    for (;it1!=vec.end();++it1) {
        if (*it1%2 != 0) {
            // #2、迭代器在第一次调用insert之后，iterator就失效了
            it1 = vec.insert(it1,*it1-1);
            ++it1;
            // break;
        }
    }


    for (int i=0;i<vec.size();i++) {
        cout<<vec[i]<<" ";
    }
    cout<<endl;



    cout<<"run success!"<<endl;
    return 0;

}
#endif