#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h>

using namespace std;

std::atomic<bool> b(false);

void fun()
{
    bool expected = false;
    // 在b == expected的情况下，更新b的值的时候失败，而返回false，这种成为佯败，从而导致下面的判断失误，不可取
    // if (!b.compare_exchange_weak(expected, true)) {
    //     cout << "b == expected, but store failed" << endl;
    // }
    
    // 采用这种方式的话，如果发生了佯败，b依然保留原来的值，expected的值也不变，下一轮循环继续compare exchange
    while (!b.compare_exchange_weak(expected, true) && expected == false) {
        cout << "b == expected, but store failed" << endl;
    }
}

std::atomic<bool> go(false);

class Task {
public:
    std::atomic<int> queue;

    Task()
    {
        queue = 0;
    }

    void get()
    {
        while (!go) {
            std::this_thread::yield();
        }
        int n = 0;
        while (!queue.compare_exchange_weak(n, n + 1)) { // 失败的可能性有两种
            // 1、佯败，queue == n，但在存储新值时失败，这个时候n == 0;
            if (n == 0) { 
                continue;
            }
            cout << "thread " << this_thread::get_id() << " " << queue << " " << n << endl;
            // 2、queue != n，此时n的值改变成了queue的值，而不等于原始的值了
            return;
        }
        cout << "thread " << std::this_thread::get_id() << " got the atomic add" << endl;
    }
};

int main()
{
    Task task;
    std::thread thr1(&Task::get, &task);
    std::thread thr2(&Task::get, &task);
    std::thread thr3(&Task::get, &task);

    go.store(true);

    thr1.join();
    thr2.join();
    thr3.join();

    cout << task.queue << endl;

    return 0;
}