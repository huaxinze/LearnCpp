#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    // high_resolution_clock
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    auto end = std::chrono::high_resolution_clock::now();
    double took = std::chrono::duration<double, std::ratio<1, 1000>>(end - start).count();
    std::cout << "[high_resolution_clock]:do something took " << took << std::endl;

    start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    end = std::chrono::system_clock::now();
    took = std::chrono::duration<double, std::ratio<1, 1000>>(end - start).count();
    std::cout << "[system_clock]:do something took " << took << std::endl;
    return 0;
}