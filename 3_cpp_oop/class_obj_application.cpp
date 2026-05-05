//
// Created by marquezzz on 2026/5/3.
//

#include <cstring>
#include<iostream>
using namespace std;

/*
 * 浅拷贝=>自定义拷贝构造函数和赋值重载函数
 * String类型
 * 循环队列Queue
 */

#if 0
class String {
public:
    String(const char* str=nullptr) {
        if (str != nullptr) {
            m_data = new char[strlen(str)+1];
            strcpy(m_data, str);
        }else {
            // 无论传进来的是不是nullptr，都设置为大小为1的字符串
            m_data = new char[1]; // 为什么是一个数组，而不是new char;???????
            *m_data = '\0';
        }
    }
    String(const String &other) {
        m_data = new char[strlen(other.m_data)+1];
        strcpy(m_data, other.m_data);
    }

    // String& 和return this*是为了支持连续的operator=赋值操作
    String& operator=(const String &other) {
        cout<<other.m_data<<endl;

        // 防止自赋值
        if (this == &other) {
            return *this;
        }

        delete [] m_data;
        m_data = new char[strlen(other.m_data)+1];
        strcpy(m_data, other.m_data);
        return *this;
    }
    ~String() {
        delete [] m_data;
        m_data = nullptr; // 防止野指针的出现
    }
private:
    char *m_data; //
};

int main() {
    // 调用String(const char* str=nullptr){} 构造函数
    String s1;
    String s2("heloo");
    String s3 = "world";


    // 拷贝 调用String(const String &other){} 拷贝构造函数
    String s4 = s3;
    String s5(s3);

    // 赋值 调用String& operator=(const String &other){} 赋值重载函数
    s3 = s2; // 赋值 左边已经存在
    // 赋值构造函数 return *this;的目的是为了支持 s3 = s1 = s2;连续赋值
    return 0;
}
#endif


// 循环队列

class Queue {
public:
    Queue(int size=5) {
        _pQue = new int[size];
        _front = 0;
        _rear = 0;
        _size = size;
    }
    // Queue(const Queue &other) = delete; 禁止用户使用拷贝构造
    Queue(const Queue &other) {
        _front = other._front;
        _rear = other._rear;
        _size = other._size;

        _pQue = new int[other._size];
        for (int i=_front; i!=_rear; i = (i+1)%_size) {
            _pQue[i] = other._pQue[i];
        }

    }

    // Queue& operator=(const Queue &other) = delete; 禁止用户使用 赋值重载
    Queue& operator=(const Queue &other) {
        if (this == &other) {
            return *this;
        }
        delete [] _pQue;
        _front = other._front;
        _rear = other._rear;
        _size = other._size;
        _pQue = new int[other._size];
        for (int i=_front; i!=_rear; i = (i+1)%_size) {
            _pQue[i] = other._pQue[i];
        }
        return *this;
    }

    ~Queue() {
        delete [] _pQue;
        _pQue = nullptr;
    }

    void enqueue(int val) {
        if (full()) {
            resize();
        }
        _pQue[_rear] = val;
        _rear = (_rear + 1) % _size;
    }
    void dequeue() {
        if (empty()) return;
        _front = (_front + 1) % _size;
    }

    int front() { // 获取队头元素
        return _pQue[_front];
    }

    bool full() {
        return (_rear + 1) % _size == _front;
    }

    bool empty() {
        return (_front == _rear);
    }
private:
    int *_pQue; // 申请队列的数组空间
    int _front; // 指示队头位置
    int _rear;  // 指示队尾位置
    int _size; // 队列扩容的总大小

    void resize() {
        // 扩容的时候 front和rear的位置不对，照搬下来依旧是个空的操作,从front到rear搬下来
        int *ptmp = new int[2*_size];
        int index = 0;
        for (int i=_front; i != _rear; i=(i + 1) % _size) {
            ptmp[index++] = _pQue[i];
        }
        delete [] _pQue;
        _pQue = ptmp;
        _front = 0;
        _rear = index;
        _size *= 2;
    }
};

int main() {
    Queue q;
    for (int i=0; i<8; i++) {
        q.enqueue(rand()%100);
    }
    /**
    * 只使用 rand() → 永远输出相同序列
    * 必须配合 srand((unsigned)time(NULL)) 才能真随机
    * srand 整个程序只需要调用一次，放在 main 开头
    */
#if 0
    while (!q.empty()) {
        cout<<q.front()<<" space";
        q.dequeue();
    }

    cout<<endl;
#endif

    Queue q2 = q;
#if 0
    while (!q2.empty()) {
        cout<<q2.front()<<" q2 ";
        q2.dequeue();
    }
    cout<<endl;
#endif

    Queue q3;
    q3 = q2;
    q3 = q3;
    return 0;
}