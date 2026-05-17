//
// Created by marquezzz on 2026/5/17.
//
#include <iostream>
using namespace std;

/*
 * 运算符重载 成员方法 全局方法
 * 内存池 进程池 线程池 连接池 对象池
 *
* for (int i = 0; i < 1000000; i++) {
        q.push(i);
        q.pop();
    }
    频繁的创建和销毁对象
 */

template <typename T>
class Queue {
public:
    Queue() {
        _front = _rear = new QueueItem();
    }

    ~Queue() {
        QueueItem *cur = _front;
        while (cur != nullptr) {
            _front = _front->_next;
            delete cur;
            cur = _front;
        }

    }
    void push(const T &val) {
        QueueItem *item = new QueueItem(val);
        _rear->_next = item;
        _rear = item;
    }

    void pop() {
        // 出队操作 从队头出
        if (empty()) {
            return;
        }
        QueueItem *first = _front->_next;
        _front->_next = first->_next;

        if (_front->_next == nullptr) {
            _rear = _front;
        }

        delete first;
    }

    T front() {
        return _front->_next->_data;
    }

    bool empty() {
        return _front == _rear;
    }


private:
    struct QueueItem {
        QueueItem(T data=T()):_data(data),_next(nullptr){}

        // 给QueueItem提供自定义的内存管理
        // 调用的时候对象不存在
        void* operator new(size_t size) {
            if (_itemPool == nullptr) {
                _itemPool =(QueueItem*) new char[POOL_ITEM_SIZE*sizeof(QueueItem)];
                QueueItem *p = _itemPool;
                for (; p!= _itemPool + POOL_ITEM_SIZE -1; ++p) {
                    p->_next = p+1;
                }
                p->_next = nullptr;
            }
            QueueItem *p = _itemPool;
            _itemPool = _itemPool->_next;
            return p;
        }
        void operator delete(void* ptr) {
            QueueItem *p = (QueueItem*) ptr;
            p->_next = _itemPool;
            _itemPool = p;
        }

        T _data;
        QueueItem* _next;
        static QueueItem* _itemPool;
        static const int POOL_ITEM_SIZE = 100000;
    };

    QueueItem *_front;
    QueueItem *_rear;
};

template <typename T>
typename Queue<T>::QueueItem *Queue<T>::QueueItem::_itemPool = nullptr;

int main() {
    Queue<int> q;
    for (int i = 0; i < 1000000; i++) {
        q.push(i);
        q.pop();
    }
    if (!q.empty()) {
        cout << q.front() << endl;
    }

    q.pop();
    cout << q.empty() << endl;
    if (!q.empty()) {
        cout << q.front() << endl;
    }
    return 0;
}

// 此处并未释放掉对象池 后面的智能指针？