#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void print(int a)
{
    cout << "this is a first thread a = " << a << endl;
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

void f(int i, std::string const& s)
{
    cout << i << " " << s << endl;
}

void update(int a, std::string& b)
{
    b += "huaxinze";
    cout << a << " " << b << endl;
}

int main()
{
    int num = 12;
    /*
     * 1.使用普通函数作为线程运行函数 
     */
    thread thr1(print, num);
    /*
     * 2.使用lambda函数作为线程运行函数，c++17以上的版本才能使用
     */
    thread thr2([](){cout << "this is a second thread" << endl;});
    /*
     * 3.使用函数对象作为线程运行函数，但是不能使用临时构造的方式来传递函数对象，C++会把它解析成一个函数声明
     *   thread thr3(func()); C++'s most vexing parse, thread thr3(func{}); or thread thr3((func())) are ok;
     */
    auto fun = func();
    thread thr3(func{});
    /*
     * 4.使用join来进行线程回收，主线程阻塞等待子线程运行结束
     */
    thr1.join();
    thr2.join();
    /*
     * 5.使用detach来进行线程分离，子线程在后台运行，其归属权和控制权转移给C++ runtime
     */
    thr3.detach();
    /*
     * 6.普通参数传递，每个线程都有内部存储空间，参数会按照默认方式复制到改处，然后这些副本被当成临时变量以右值的形式传给新线程上的函数或可调用对象
     */
    std::thread thr4(f, 1, "hello world");
    thr4.join();
    /*
     * 7.指针参数传递，指针buffer，指向一个局部数组变量，原本设想，buffer会在新线程内转换成std::string对象，但在此完成之前主函数极有可能已经退出，
     *   导致局部数组被销毁而引发未定义行为，原因是std::thread的构造函数原样复制所提供的值，并未令其转换为预期的参数类型。
     */
    int cnt = 1000000;
    char buffer[1024];
    sprintf(buffer, "%i", cnt);
    std::thread thr5(f, 2, buffer); // 正确的做法是sprintf(buffer, "%i", std::string(buffer)); 
    thr5.detach();
    /*
     * 8.引用参数传递，针对的是那种需要传入到子线程中进行修改的情况，需要使用std::ref来显示的传递引用，否则参考6，拷贝的是对象本身，并且按照右值传递给函数
     */
    string str = "jiamo ai ";
    std::thread thr6(update, 3, std::ref(str));
    thr6.join();

    return 0;
}