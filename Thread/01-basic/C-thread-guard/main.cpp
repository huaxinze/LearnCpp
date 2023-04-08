#include <iostream>
#include <thread>

using namespace std;

class thread_guard {
private:
    std::thread& t; // 用引用的原因是，thread复制函数会引发析构

public:
    explicit thread_guard(std::thread& t_)
        : t(t_)
    {}
    ~thread_guard()
    {
        if (t.joinable())
        {
            t.join();
            cout << "thread join" << endl;
        }
    }
    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard& ) = delete;
};

void run()
{
    cout << "enter run " << endl;
}

int main()
{
    std::thread thr(run);
    thread_guard g(thr);
    return 0;
}