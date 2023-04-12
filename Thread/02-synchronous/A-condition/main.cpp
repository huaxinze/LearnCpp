#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <unistd.h>

using namespace std;

std::mutex mut;
std::condition_variable data_cond;
std::queue<int> data_queue;

void data_preparation_thread()
{
    int i = 0;
    while (true)
    {
        {
            std::unique_lock<std::mutex> lk(mut);
            data_queue.push(i++);
        }
        data_cond.notify_one();
        sleep(1);
    }
}

void data_processing_thread()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, []{ return !data_queue.empty(); });
        int num = data_queue.front();
        data_queue.pop();
        lk.unlock();
        std::cout << "pop num " << num << endl;
    }
}

int main()
{
    std::thread thr1(data_preparation_thread);
    std::thread thr2(data_processing_thread);

    thr1.join();
    thr2.join();
    
    return 0;
}