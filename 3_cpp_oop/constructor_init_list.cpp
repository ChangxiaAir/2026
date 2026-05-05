//
// Created by marquezzz on 2026/5/5.
//
#include <cstring>
#include <iostream>
using namespace std;

#if 0
// 日期
class Date {
    public:
    Date(int year, int month, int day) { // 自定义了一个构造函数，编译器就不会再产生默认构造了
        _year = year;
        _month = month;
        _day = day;
    }
    void show() {
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
    }

    void show() {
        cout<<"name: "<<_name<<endl;
        cout<<"amount: "<<_amount<<endl;
        cout<<"price: "<<_price<<endl;
        _date.show();
    }

private:
    char _name[20];
    int _amount;
    double _price;
    Date _date; // 组合，成员对象 对象的生成有两部分 1.分配内存；2.调用构造函数
};
int main () {
    Goods g("apple",20,100,2026,05,05);
    g.show();
    return 0;
}

#endif

class Test {
public:
    Test(int data=10):mb(data), ma(mb){}
    void show() {
        cout<<"ma "<<ma<<" mb "<<mb<<endl;
    }

private:
    // 成员变量的初始化顺序是和他们的定义顺序有关，和构造函数初始化列表中出现的先后顺序无关
    int ma;
    int mb;
};

int main() {
    Test t; // 生成一个对象的时候，对象成员的初始化方式是按照定义的顺序去初始化的，即按照 int ma; int mb;的顺序去的
    t.show();
    return 0;
}