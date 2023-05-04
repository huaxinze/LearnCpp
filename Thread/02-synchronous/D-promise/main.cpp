#include <iostream>
#include <future>
#include <thread>
#include <deque>
#include <vector>

using namespace std;

class Message {
public:
    int type;
    std::vector<int> data;
    std::promise<bool> p;

public:
    Message() = default;
    
    Message(Message& msg) = delete;
    Message& operator=(const Message& msg) = delete;
    
    Message(Message&& msg) {
        type = msg.type;
        data = std::move(msg.data);
        p = std::move(msg.p);
    }
    Message& operator=(Message&& msg)
    {
        type = msg.type;
        data = std::move(msg.data);
        p = std::move(msg.p);
        return *this;
    }
};

std::mutex m;
std::deque<Message> list;

void process_message()
{
    while (1) {
        Message msg;
        {
            std::lock_guard<std::mutex> lg(m);
            if (list.empty()) {
                continue;
            }
            msg = std::move(list.front());
            list.pop_front();
        }
        msg.p.set_value(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main()
{
    std::cout << "enter promise demo" << std::endl;
    std::thread thr(process_message);

    std::vector<std::future<bool>> res;
    for (int i = 0; i < 10; i++) {
        {
            std::lock_guard<std::mutex> lg(m);
            Message msg;
            msg.type = i;
            msg.data = {};
            res.push_back(msg.p.get_future());            
            list.push_back(std::move(msg));
        }
    }
    for (int i = 0; i < res.size(); i++) {
        if (res[i].get()) {
            cout << "message " << i << " process done " << endl;
        }
    }
    thr.join();
    return 0;
}