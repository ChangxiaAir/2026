//
// Created by marquezzz on 2026/5/5.
//

#include <iostream>
#include <cstring>
using namespace std;

/*
 * 类的各种成员 成员方法/成员变量
 * 普通的成员方法 void show(); ====》编译器会添加一个this形参变量
 * 1、属于类的作用域
 * 2、调用该方法时，需要依赖一个对象（常对象无法调用 相当于把const Goods*实参传递给 Goods *this形参，这是非法的
 * 3、可以任意访问对象的私有成员变量   不考虑protected(只在继承的时候考虑
 *
 * 静态成员变量是所有对象共享的，在计算对象大小的时候静态成员变量的大小是不纳入的
 * 对象g1、g2、g3在栈上面，而静态成员变量int Goods::_count = 0; 初始化为0，是在.bss段
 *
 * 要对所有对象的共有的信息_count进行访问，需要以 类名::方法名();来调用
 * 要将该方法定义为静态成员方法 static void showGoodsCount(){}
 *
 * 静态成员方法 static void showGoodsCount(); ===》不会生成this形参
 * 1、属于类的作用域
 * 2、用类名作用域来调用方法
 * 3、可以任意访问对象的私有成员，仅限于不依赖对象的成员（只能调用static 静态成员
 *
 * const 常成员方法 void show() const {} ===>const Goods *this
 * 1、属于类的作用域
 * 2、调用依赖一个对象，普通对象或者常对象都可以
 * 3、可以任意访问对象的私有成员，但是只能读，而不能写
 */

class Date {
public:
    Date(int year, int month, int day) { // 自定义了一个构造函数，编译器就不会再产生默认构造了
        _year = year;
        _month = month;
        _day = day;
    }
    void show() const{
        cout<<_year<<"/"<<_month<<"/"<<_day<<endl;
    }
private:
    int _year;
    int _month;
    int _day;
};

/*
 * 构造函数的初始化列表:可以指定当前对象成员变量的初始化方式
 *
 * Date信息是Goods商品信息的一部分 a part of ... 组合的关系； 继承是 a kind of ...
 */
class Goods {
public:
    // 不对成员对象Date的变量做初始化的话，会报错error: no matching function for call to ‘Date::Date()’，需要用构造函数的初始化列表来解决
    Goods(const char *name, int amount, double price, int y, int m, int d)
        :_date(y,m,d)   // Date _date(y,m,d);直接指定日期对象的构造方式
        // ,_amount(amount) // 在初始化列表里面相当于int _amount = amount;在定义的时候直接初始化
        // ,_price(price)
        // 先执行#1构造函数的初始化列表
    {
        // 在执行 #2 当前类类型构造函数体
        strcpy(_name, name);
        _amount = amount; // 函数体中相当于 int _amount; _amount = a; 先定义再赋值
        _price = price;
        /*
         * 要是在函数体中初始化_date，先Date　_date;（会用默认构造,但是Date对象没默认构造） _data = Date(y,m,d);
         */
        _count++; // 记录所有产生的新对象的数量
    }

    void show() { // 普通成员方法 有Goods *this指针
        cout<<"name: "<<_name<<endl;
        cout<<"amount: "<<_amount<<endl;
        cout<<"price: "<<_price<<endl;
        cout<<"no cont count" << _count<<endl;
        _date.show();
    }

    // 只要是只读操作的成员方法，一律实现成const常成员方法 常对象和非常对象都能调用
    // 常成员方法 与void show(){}属于重载，两者的形参类型不同
    void show() const { // 编译器生成this形参的类型 const Goods *this  const右边有指针的时候const要参与类型
        cout<<"name: "<<_name<<endl;
        cout<<"amount: "<<_amount<<endl;
        cout<<"price: "<<_price<<endl;
        cout<<"-count" << _count<<endl;
        _date.show(); // 这里传进来的this指针类型是 const
    }

    // 静态成员方法 没有this指针 调用时不需要对象
    static void showGoodsCount() { // 所有对象共享的信息
        cout<<"all goods count: "<<_count<<endl;
    }

private:
    char _name[20];
    int _amount;
    double _price;
    Date _date; // 组合，成员对象 对象的生成有两部分 1.分配内存；2.调用构造函数
    static int _count; // 不属于对象，而是属于类级别的 声明 用来记录商品对象的总数量
};


// static成员变量一定要在类外进行定义并且初始化
int Goods::_count  = 0;

int main () {
    Goods g1("apple",20,100,2026,05,05);
    g1.show();

    Goods g2("banana",20,100,2026,05,05);
    g2.show();

    Goods g3("pear",20,100,2026,05,05);
    g3.show();

    /*
     * 如何统计所有商品的数量？
     * 1、全局变量？可以，但不够OOP
     * 2、在Goods中定义一个 int _count变量来统计可以吗？不可以
     * 3、在Goods类中声明一个静态成员变量 static int _count可以吗？ 可以！声明完之后需要在类外定义
     */
    // g3.showGoodsCount(); // 访问的是所有对象共享的信息，从语义上来看该方法属于g3对象

    // 要访问所有对象共享的信息，应该使用类名来访问 Goods::showGoodsCount(); 此时我们应该将该方法改为static
    Goods::showGoodsCount();

    const Goods g4("orange",20,100,2026,05,05);
    g4.show(); // error: passing ‘const Goods’ as ‘this’ argument discards qualifiers [-fpermissive]
    // 相当于Goods::show(&g4) const Goods* 但是show的this形参类型是 Goods *this

    Goods::showGoodsCount();
    return 0;
}