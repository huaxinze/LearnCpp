#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

using namespace std;

void swap(vector<int>& lhs, vector<int>& rhs)
{
    std::swap(lhs, rhs);
}

class X {
private:
    std::vector<int> some_detail;
    std::mutex m;

public:
    X(vector<int> const& sd) : some_detail(sd) {}
    friend void swap(X& lhs, X& rhs)
    {
        if (&lhs == &rhs) {
            return;
        }
        // 通过这种方式就可以一定程度上忽略了锁的顺序
        std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
        std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
        std::lock(lock_a, lock_b);
        swap(lhs.some_detail, rhs.some_detail);
        lhs.print();
        rhs.print();
    }
    void print()
    {
        for (auto el : some_detail) {
            cout << el << " ";
        }
        cout << std::this_thread::get_id() << endl;
    }
};

int main()
{
    X x1({1, 2, 3});
    X x2({4, 5, 6});
    std::thread thr1([](X& x1_, X& x2_){ swap(x1_, x2_);}, std::ref(x1), std::ref(x2));
    std::thread thr2([](X& x1_, X& x2_){ swap(x1_, x2_);}, std::ref(x1), std::ref(x2));

    thr1.join();
    thr2.join();

    return 0;
}