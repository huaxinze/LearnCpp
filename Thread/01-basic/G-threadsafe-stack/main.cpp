#include <iostream>
#include <memory>
#include <stack>
#include <mutex>
#include <thread>

using namespace std;

struct empty_stack : std::exception {
    const char* what() const throw()
    {
        return "empty stack";
    }
};

template<typename T>
class threadsafe_stack {
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }

    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
    }

    /*
     * 通过引用或者指针的形式来取出值，而不是通过函数返回的方式取出值的原因是通过返回值的话需要先pop，然后再拷贝到返回值，但是拷贝的过程有可能异常，导致值没成功，而数据又已经pop掉了
     */
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) {
            throw empty_stack();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }

    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) {
            throw empty_stack();
        }
        value = data.top();
        data.pop();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

threadsafe_stack<int> stk;

void fun1()
{
    stk.push(100);
}

void fun2()
{
    try {
        auto p = stk.pop();
        cout << *p << endl;
    } catch (const empty_stack& e) {
        cout << e.what() << endl;
    }
}

int main()
{
    std::thread thr2(fun2);
    std::thread thr1(fun1);
    thr1.join();
    thr2.join();
    return 0;
}