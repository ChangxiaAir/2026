//
// Created by marquezzz on 2026/5/9.
//
#include<iostream>
using namespace std;

/*
 * c++的运算符重载：使对象的运算表现得和编译器内置类型一样
 */
// template<typename T>
// T sum(T a, T b) {
//     return a + b; // a.+(b)
// }

// 复数类

class Complex {
public:
    // Complex() Complex(20) Complex(30,30)
    Complex(int r=0,int i=0)
        :real(r),imag(i) {}
    // 指导编译器怎么做Complex类对象的加法操作
    Complex operator+(const Complex &rhs) {
        // Complex com;
        // com.real=this->real+rhs.real;
        // com.imag=this->imag+rhs.imag;
        // return com;
        return Complex(real+rhs.real,imag+rhs.imag); // 相比上面的 少了一个临时对象的构造和析构，效率++
    }

    Complex operator++(int) {
        // Complex comp = *this;
        // real += 1;
        // imag += 1;
        // return comp;

        return Complex(real++,imag++); // 少了一个对象的构造和析构的过程
    }

    Complex& operator++() { // Complex& 不用产生临时对象
        real += 1;
        imag += 1;
        return *this;
    }

    void operator+=(const Complex &rhs) {
        real += rhs.real;
        imag += rhs.imag;
    }

    void show() const {
        cout<<real<<" + "<<imag<<endl;
    }

private:
    int real;
    int imag;
    friend Complex operator+(const Complex &lhs,const Complex &rhs);
    friend ostream& operator<<(ostream &out, const Complex &rhs);
    friend istream& operator>>(istream &in, Complex &rhs);
};

// 全局定义使得
// 1、comp3 = comp1 + comp2;
// 2、Complex comp4 = comp1 + 20;
// 3、Complex comp5 = 30 + comp1;
// 上述三种形式都能运算，此时Complex内部的实现可以去掉
Complex operator+(const Complex &lhs, const Complex &rhs) {
    // 全局函数无法访问类里面的私有变量 如何解决？ -> 1、添加get_real() get_imag()方法 2、友元函数
    return Complex(lhs.real + rhs.real,lhs.imag + rhs.imag);
}
ostream& operator<<(ostream &out, const Complex &rhs) {
    out<<"real: " << rhs.real << " imag: " << rhs.imag << endl;
    return out;
}

istream& operator>>(istream &in, Complex &rhs) {
    in>>rhs.real;
    in>>rhs.imag;
    return in;
}
int main() {
    Complex comp1(10,10);
    Complex comp2(20,20);
    // comp1.operator+(comp2) 加法运算符的重载
    Complex comp3 = comp1 + comp2;
    comp3.show();

    // comp1.operator+(20) int->Complex Complex(int)
    Complex comp4 = comp1 + 20; // 相当于构造了一个临时对象
    comp4.show();

    // 编译器不会将30主动转换为Complex 否则int a = 10+10;都无法正确运算
    // 编译器做对象运算的时候，会调用对象的运算符重载函数（优先调用成员方法）；
    //   如果没有成员方法，就在全局作用域找合适的运算符重载函数
    //   ::operator+(30,comp1)
    // 全局函数是不需要对象来调用的，除了运算符+，30和comp1都当做实参传进去
    Complex comp5 = 30 + comp1;
    comp5.show();

    // operator++() 不带参数 前置++
    // operator++(int) 带一个整型参数 后置++
    cout<<"1、=================="<<endl;
    // Complex operator++(int)
    Complex comp6 = comp1++;
    comp6.show();
    comp1.show();

    // Complex operator++()
    comp6 = ++comp1;
    comp6.show();
    comp1.show();

    comp6+=comp1;
    comp6.show();
    // 对于单目运算符  直接在对象里面实现 调用相应的成员方法来实现

    // 对象信息的输出
    // 输出运算符重载函数该怎么提供呢？
    // 1、输出运算符重载函数 对象不在运算符左边 不能提供成员方法
    // 2、将出书运算符重载函数提供成全局方法 不需要什么对象来调用  ::operator(cout,comp1)
    // 返回值ostream& operator<<(ostream &out, const Complex &rhs)
    cout << comp1<<endl;

    cout<<"2、=================="<<endl;
    Complex comp7;
    cout << comp7<<endl;
    cin >> comp7;
    cout << comp7<<endl;
    return 0;

}