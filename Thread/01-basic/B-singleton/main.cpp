#include <iostream>
#include <thread>

using namespace std;

// thread safe
class Singleton {
public:
    ~Singleton() = default;

    static Singleton& GetInstance()
    {
        pthread_once(&ponce_, &Singleton::Init);
        return *instance;
    }

    void Print() const
    {
        cout << "enter singleton" << endl;
    }

private:
    Singleton() = default;
    Singleton(const Singleton &) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    
    static void Init()
    {
        cout << "init once" << endl;
        instance = new Singleton();
    }

    static Singleton* instance;
    static pthread_once_t ponce_;
};

Singleton* Singleton::instance = nullptr;
pthread_once_t Singleton::ponce_ = PTHREAD_ONCE_INIT;

int main()
{
    std::thread thr1([](){ Singleton::GetInstance().Print();});
    Singleton::GetInstance().Print();
    thr1.join();
    return 0;
}