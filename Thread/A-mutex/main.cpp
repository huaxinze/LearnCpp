#include <iostream>
#include <thread>

using namespace std;

void print()
{
    cout << "this is a first thread" << endl;
}

class func {
public:
    func() = default;
    ~func() = default;
    void operator()(){
        cout << "this is a third thread" << endl;
        return;
    }
};

int main()
{
    // 普通函数
    thread thr1(print);
    // lambda函数，c++17以上的版本才能使用
    thread thr2([](){cout << "this is a second thread" << endl;});
    // 函数对象
    auto fun = func();
    thread thr3(fun);
    cout << "hello world" << endl;
    thr1.join();
    thr2.join();
    thr3.join();
    return 0;
}