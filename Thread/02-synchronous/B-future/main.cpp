#include <iostream>
#include <future>
#include <thread>

using namespace std;

int find_the_answer_to_ltuae()
{
    std::cout << "enter find the answer to ltuae and thread id = " << std::this_thread::get_id() << endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "loop again" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 99;
}

int main()
{
    std::cout << "main thread id = " << std::this_thread::get_id() << endl;
    // std::launch::async 表示任务是异步执行的，由另外的线程来完成
    std::future<int> the_answer = std::async(std::launch::async, find_the_answer_to_ltuae);
    // wait是用来定时判断任务的状态，我觉得最主要的作用还是为了防止阻塞，当异步的任务长时间得不到响应，理应终止获取结果
    while (the_answer.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) {
        // std::cout << "the task is not ready" << std::endl;
        continue;
    }
    // get则是阻塞住以获得结果
    the_answer.get();
    std::cout << "got the answer" << std::endl;

    // std::launch::deferred 表示推迟获取结果，由调用get的线程来执行
    std::future<int> the_answer2 = std::async(std::launch::deferred, find_the_answer_to_ltuae);
    the_answer2.get();
    return 0;
}