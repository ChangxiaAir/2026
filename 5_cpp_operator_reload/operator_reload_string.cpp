//
// Created by marquezzz on 2026/5/10.
//

#include <cstring>
#include<iostream>

using namespace std;
/*
 *
 */


#if 0
#include<string>
int main() {
    string str1 = "aaa";
    string str2 = "bbb";
    string str3 = str1+str2;
    string str4 = "ccc"+str1;
    string str5 = str2+"ccc";
    // string str6 = "ddd"+"eee";

    cout<<"str5: "<<str5<<endl;
    if (str5>str4) {
        cout<<str5<< " > " << str4<<endl;
    }else {
        cout<<str5<< " < " << str4<<endl;
    }

    int len = str5.length();
    for (int i = 0; i < len; i++) {
        cout<<str5[i]<<" ";
    }
    cout<<endl;

    // string -> char*
    char buf[1024] = {0};
    strcpy(buf, str5.c_str()); // c_str()可以将string对象返回成const char *对象
    cout<<"buf: "<<buf<<endl;
    return 0;

}
#endif

/*
 * 自己实现一个字符串对象
 *
 */

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
    String str1 = "aaa";
    String str2 = "bbb";
    String str3 = str1+str2;
    String str4 = "ccc"+str1;
    String str5 = str2+"ccc";
    // string str6 = "ddd"+"eee";

    cout<<"str5: "<<str5<<endl;
    if (str5>str4) {
        cout<<str5<< " > " << str4<<endl;
    }else {
        cout<<str5<< " < " << str4<<endl;
    }

    int len = str5.length();
    for (int i = 0; i < len; i++) {
        cout<<str5[i]<<" ";
    }
    cout<<endl;

    // string -> char*
    char buf[1024] = {0};
    strcpy(buf, str5.c_str()); // c_str()可以将string对象返回成const char *对象
    cout<<"buf: "<<buf<<endl;
    return 0;
}