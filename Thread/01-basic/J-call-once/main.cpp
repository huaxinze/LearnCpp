#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

class X {
public:
    ~X() = default;
    static X& GetInstance()
    {
        std::call_once(once, X::Init);
        return *instance;
    }

    void Print() const
    {
        cout << "thread = " << std::this_thread::get_id() << endl;
    }

private:
    X() = default;
    X(const X&) = delete;
    X& operator=(X& ) = delete;
    X(const X&&) = delete;
    X& operator=(X&& ) = delete;

    static X* instance;
    static std::once_flag once;
    
    static void Init()
    {
        cout << "init for X instance in thread " << std::this_thread::get_id() << endl;
        if (instance != nullptr) {
            delete instance;
        }
        instance = new X();
    }
};

X* X::instance = nullptr;

std::once_flag X::once;

void fun1()
{
    X::GetInstance().Print();
}

void fun2()
{
    X::GetInstance().Print();
}

int main()
{
    std::thread thr1(fun1);
    std::thread thr2(fun2);

    thr1.join();
    thr2.join();

    return 0;
}