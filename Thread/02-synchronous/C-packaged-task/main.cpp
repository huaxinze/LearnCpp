#include <iostream>
#include <future>
#include <thread>
#include <deque>
#include <functional>

using namespace std;

std::mutex m;
std::deque<std::packaged_task<void()>> tasks;

void gui_thread()
{
    while (1)
    {
        std::packaged_task<void()> task;
        {
            std::lock_guard<std::mutex> lg(m);
            if (tasks.empty()) {
                continue;
            }
            task = std::move(tasks.front());
            tasks.pop_front();
        }
        task();
    }
}

template<typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
    std::packaged_task<void()> task(f);
    std::future<void> res = task.get_future();
    std::lock_guard<std::mutex> lk(m);
    tasks.push_back(std::move(task));
    return res;
}

void print()
{
    std::cout << "enter print" << std::endl;
}

void printArg(int a, std::string b)
{
    std::cout << a << " " << b << std::endl;
}

int main()
{
    std::cout << "hello packaged task" << std::endl;

    std::thread thr(gui_thread);

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        post_task_for_gui_thread<void()>(print);
        post_task_for_gui_thread<function<void()>>(std::bind(printArg, 1, "huaxinze"));
    }

    thr.join();

    return 0;
}