#include <iostream>
#include <map>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <unistd.h>

using namespace std;

struct dns_entry {
    int id = -1;    
    std::string entry; 
};

class dns_cache {
private:
    mutable std::shared_mutex m;
    std::map<std::string, dns_entry> entries{};

public:
    dns_entry find_entry(std::string const& domain) const
    {
        std::shared_lock<std::shared_mutex> lock(m);
        const auto it = entries.find(domain);
        return (it == entries.end()) ? dns_entry() : it->second;
    }

    void update_or_add_entry(std::string const& domain, dns_entry const& dns_details)
    {
        std::unique_lock<std::shared_mutex> lock(m);
        entries[domain] = dns_details;
    }
};

void write_fun(dns_cache& cache)
{
    for (int i = 0; i < 100; i++) {
        cache.update_or_add_entry(std::to_string(i), {i, ""});
    }
}

void read_fun1(dns_cache& cache)
{
    for (int i = 0; i < 100; i++) {
        const auto &entry = cache.find_entry(std::to_string(i));
        if (entry.id == -1) {
            i--;
            continue;
        }
        cout << "thread[" << std::this_thread::get_id() << "]:" << entry.id << " " << entry.entry << endl;
    }
}

void read_fun2(dns_cache& cache)
{
    for (int i = 0; i < 100; i++) {
        const auto &entry = cache.find_entry(std::to_string(i));
        if (entry.id == -1) {
            i--;
            continue;
        }
        cout << "thread[" << std::this_thread::get_id() << "]:" << entry.id << " " << entry.entry << endl;
    }
}

int main()
{
    dns_cache dns;
    std::thread thr1(write_fun, std::ref(dns));
    std::thread thr2(read_fun1, std::ref(dns));
    std::thread thr3(read_fun2, std::ref(dns));

    thr1.join();
    thr2.join();
    thr3.join();

    return 0;

}