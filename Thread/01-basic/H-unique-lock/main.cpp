#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int num1 = 0;
std::mutex m_none;

//      策略 	     std::lock_guard 	     std::unique_lock 	   std::shared_lock
//     (默认) 	             √ 	                     √ 	                 √(共享)
// std::defer_lock 	        × 	                    √                	√
// std::try_to_lock 	    × 	                    √                	√
// std::adopt_lock        	√ 	                    √               	√

/*
 阻塞上锁，构造时进行阻塞上锁，离开作用域时释放锁
 */
void fun_with_none()
{
    std::unique_lock<std::mutex> lock(m_none);
    num1++;
}

/*
 互斥量以上锁，收养互斥量，离开作用域时释放锁，但是还可以转移所属权，来延长锁的寿命
 */
std::mutex m_adopt;
int num2 = 0;
void fun_with_adopt()
{
    m_adopt.lock();
    std::unique_lock<std::mutex> lock(m_adopt, std::adopt_lock);
    num2++;
    // auto unlock when leave
}

/*
 延时加锁，构造过程中不会上锁，需要主动调用lock来进行加锁，离开作用域时释放锁
 */
std::mutex m_defer;
int num3 = 0;
void fun_with_defer()
{
    std::unique_lock<std::mutex> lock(m_defer, std::defer_lock);
    // do some other thing, then lock
    lock.lock();
    num3++;
    // auto unlock when leave
}

/*
 尝试加锁，没有成功的情况下不会阻塞，通过owns_lock()判断是否加锁成功，如果成功了，离开作用域会自动释放锁
 */
std::mutex m_try;
int num4 = 0;
void fun_with_try()
{
    std::unique_lock<std::mutex> lock(m_try, std::try_to_lock);
    if (lock.owns_lock()) 
    {
        num4++;
        cout << "have lock" << endl;
    } else
    {
        cout << "not have lock" << endl;
    }
    // lock.unlock(); 没有获取锁的情况下不能释放锁，不然会出现异常
}

int main()
{
    std::thread thr1(fun_with_none);
    std::thread thr2(fun_with_none);

    std::thread thr3(fun_with_adopt);
    std::thread thr4(fun_with_adopt);

    std::thread thr5(fun_with_defer);
    std::thread thr6(fun_with_defer);

    std::thread thr7(fun_with_try);
    std::thread thr8(fun_with_try);

    thr1.join();
    thr2.join();

    thr3.join();
    thr4.join();

    thr5.join();
    thr6.join();

    thr7.join();
    thr8.join();

    cout << num1 << " " << num2 <<  " " << num3 << " " << num4 << endl;
    return 0;
}