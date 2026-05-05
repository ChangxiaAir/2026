//
// Created by marquezzz on 2026/5/3.
//

#include <cstring>
#include <iostream>
using namespace std;

/*
 * c++类 => 实体的抽象类型
 * 实体（属性、行为） -> ADT(抽象数据类型)
 *
 * 对象    <- （实例化）     类（属性->成员变量  行为->成员方法)
 *
 * OOP语言的四大特征是什么？
 * 抽象
 * 封装/隐藏：访问限定符号来实现 public private protected
 * 继承
 * 多态
 *
 */

const int NAME_LEN = 20;

class Goods {

public:  // 给外部提供公有的方法，来访问私有的属性
    void init(const char *name, double price, int amount);
    void show(); // 打印商品信息

    // getXXX或者setXXX的方法，类体内部实现的方法，自动处理成inline内联函数
    void setName(char *name) { strcpy(_name, name);};
    void setPrice(double price) {_price = price;};
    void setAmount(int amount) { _amount = amount; };

    const char *getName() { return _name; };
    double getPrice() { return _price; };
    int getAmount() { return _amount; };


private:    // 属性一般都是私有的
    char _name[NAME_LEN]; // 20个字节+4字节对齐
    double _price; // 8个字节（按照最长的来对齐）
    int _amount; // 4个字节+4字节对齐

    // 共占40个字节，其中8字节被用来占位 内存对齐减少了内存访问的次数
};

inline void Goods::init(const char *name, double price, int amount) {
    strcpy(_name, name);
    _price = price;
    _amount = amount;
}
inline void Goods::show() {
    cout<<"name:"<<_name<<endl;
    cout<<"price:"<<_price<<endl;
    cout<<"amount:"<<_amount<<endl;
}

int main () {

    // Goods可以定义无数的对象
    Goods good;  // 类实例化了一个对象，每个对象都有自己的成员变量 但是他们共享一套成员方法

    //show() 怎么知道处理哪个对象的信息？
    //init() 怎么知道把信息初始化给哪一个对象的
    good.init("apple", 0.5, 10); // 常字符串“apple”需要用常字符指针const char *接收
    // good.init()等价于 init(&good,...)
    // 类的成员方法经过编译，所有的方法参数，都会加一个this指针，接收调用该方法的对象的地址
    good.show();
    good.setPrice(20);
    good.setAmount(100);good.show();


    return 0;
}