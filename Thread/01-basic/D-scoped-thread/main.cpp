#include <iostream>
#include <thread>

using namespace std;

class scoped_thread {
public:
    scoped_thread(std::thread t_)
        : t(std::move(t_))
    {
        if (!t.joinable()) {
            throw std::logic_error("No thread");
        }
    }

    ~scoped_thread()
    {
        t.join();
    }

    scoped_thread(const scoped_thread&) = delete;
    scoped_thread operator=(const scoped_thread&) = delete;

private:
    std::thread t;
};

void fun()
{
    std::cout << "hello scoped thread" << std::endl;
}

void some_function()
{
    std::cout << "enter some function" << std::endl;
}

void some_other_function()
{
    std::cout << "enter some other function" << std::endl;
}

int main()
{
    scoped_thread t{std::thread(fun)};
    
    std::thread thr1(some_function);
    // 现实调用移动复制
    std::thread thr2 = std::move(thr1);
    // 隐式调用移动复制
    thr1 = std::thread(some_other_function);

    thr1.join();
    thr2.join();

    return 0;
}