#include <atomic>
#include <thread>
#include <assert.h>

using namespace std;

std::atomic<bool> x, y;

std::atomic<int> z;

void write_x()
{
    x.store(true, std::memory_order_seq_cst);
}

void write_y()
{
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y()
{
    while (!x.load(std::memory_order_seq_cst));
    if (y.load(std::memory_order_seq_cst)) z++;
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst));
    if (x.load(std::memory_order_seq_cst)) z++;
}

// x和y的载入存储服从先后一致次序，则所见即所得，变量的可见性与操作顺序一致，不同处理器之间会为了这种一致性去作同步，这也会导致性能开销比较大

int main()
{
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();
    assert(z.load() != 0); // 断言肯定不会触发
    return 0;
}