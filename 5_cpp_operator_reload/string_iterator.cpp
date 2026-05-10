//
// Created by marquezzz on 2026/5/10.
//

#include <cstring>
#include<iostream>

using namespace std;

/* 迭代器的功能是什么？ 提供一种统一的方式，来透明的遍历容器
 * 迭代器
 * 迭代器可以透明的访问容器内部的元素的值
 * 每种类型都有自己的迭代器
 * 所以迭代器设计成为了一个类的嵌套类型
 * begin() 首元素位置
 * end() 末尾元素的后一个位置
 *
 * C++ STL 的泛型算法 参数接收的都是迭代器！
 * 泛型算法 - 全局的函数 - 给所有容器用的，【不同的容器底部的数据结构不一样】
 * 泛型算法，有一套方式，能够统一的遍历所有的容器的元素 - 迭代器
 */

#if 0
#include<string>
int main() {
    string str1 = "hello world!"; // str1叫容器吗？ YES 底层存放了一组char类型的字符
    string::iterator it = str1.begin();
    for (; it != str1.end(); ++it) {
        cout<<*it<<" ";
    }
    cout<<endl;
}
#endif

class String {
public:
    String(const char *p=nullptr) {
        if (p != nullptr) {
            _pstr = new char[strlen(p) + 1];
            strcpy(_pstr, p);
        }else {
            _pstr = new char[1];
            _pstr[0] = '\0';
        }
    }

    ~String() {
        delete _pstr;
        _pstr = nullptr;
    }
    String(const String &rhs) {
        _pstr = new char[strlen(rhs._pstr)+1]; // 为什么要加一？？
        strcpy(_pstr, rhs._pstr);
    }

    String &operator=(const String &rhs) {
        if (this == &rhs) {
            return *this;
        }
        delete [] _pstr;
        _pstr = new char[strlen(rhs._pstr)+1];
        strcpy(_pstr, rhs._pstr);
        return *this;
    }

    bool operator>(const String &rhs) const {
        return strcmp(_pstr, rhs._pstr) > 0;
    }
    bool operator<(const String &rhs) const {
        return strcmp(_pstr, rhs._pstr) < 0;
    }

    bool operator==(const String &rhs) const {
        return strcmp(_pstr, rhs._pstr) == 0;
    }

    int length() const {
        return strlen(_pstr); // 有效字符的个数 不包括'/0'
    }
    // char ch = str6[6];  str6[6] = '7';
    char& operator[](int i) {
        return _pstr[i];
    }

    // char ch = str6[6]; 不允许修改
    const char& operator[](int i) const {
        return _pstr[i];
    }

    const char* c_str() const {
        return _pstr;
    }

    // 给字符串类型提供迭代器的实现
    class iterator {
    public:
        iterator(char *p=nullptr) :_p(p){}
        bool operator!=(const iterator &rhs) const {
            return _p != rhs._p;
        }
        // ++it
        void operator++() {
            ++_p;
        }

        // *it
        char& operator*() {
            return *_p;
        }
    private:
        char *_p;
    };

    // begin 和 end是容器的方法 而不是迭代器的方法
    // begin返回的是容器底层首元素的迭代器表示
    iterator begin() const{
        return iterator(_pstr);
    }
    // end返回的是容器末尾元素的后继位置的迭代器表示
    iterator end() const {
        return iterator(_pstr+length());
    }

private:
    char *_pstr;
    friend String operator+(const String &lhs, const String &rhs);
    friend ostream &operator<<(ostream &out, const String &rhs);
    friend istream &operator>>(istream &in, String &rhs);
};

String operator+(const String &lhs, const String &rhs) {
    // 在这里只new了对象，但是并没有释放 存在内存泄漏的问题
    // char *ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
    String tmp;
    tmp._pstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr)+1];
    strcpy(tmp._pstr,lhs._pstr);
    strcat(tmp._pstr,rhs._pstr);
    return tmp;

}
ostream &operator<<(ostream &out, const String &rhs) {
    out<< rhs._pstr <<endl; // out<<rhs<<endl 是无限递归
    return out;
}

istream &operator>>(istream &in, String &rhs) {
    in>>rhs._pstr;
    return in;
}


int main() {
    String str1 = "hello world!"; // str1叫容器吗？ YES 底层存放了一组char类型的字符
    String::iterator it = str1.begin(); //  嵌套类型 iterator
    for (; it != str1.end(); ++it) {
        cout<<*it<<" ";
    }
    cout<<endl;

    // C++11 foreach的方式来遍历容器的内部元素的值==》底层还是通过迭代器的方式来实现的
    for (char ch : str1) {
        cout<<ch<<" ";
    }
    cout<<endl;
}
