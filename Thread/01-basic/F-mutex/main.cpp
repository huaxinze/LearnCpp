#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

using namespace std;

class some_data {
    int a;
    std::string b;

public:
    void do_something()
    {
        cout << a << " " << b << endl;
    }
};

class data_wrapper {
private:
    some_data data;
    std::mutex m;

public:
    template<typename Function>
    void process_data(Function func)
    {
        std::lock_guard<std::mutex> l(m);
        func(data); // 泄漏了受保护数据
        // do some thing for data in thr1 thread;
        // ...
    }
};

some_data* unprotected;

void malicious_function(some_data& data)
{
    unprotected = &data;
}

data_wrapper x;

void foo()
{
    x.process_data(malicious_function);
}

int main()
{
    std::thread thr1(foo);
    sleep(1);
    // do some thing for data in main thread;
    // ...
    // 数据data将在不同的线程中不受保护的被使用
    if (unprotected) {
        unprotected->do_something();
    }
    thr1.join();
    return 0;
}