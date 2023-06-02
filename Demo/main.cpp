#include "ifly.h"
#include <dlfcn.h> 
#include <iostream>

typedef void (*FuncType)();

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        std::cout << "please input: ./ifly_test [type 0:default 1:ifly1 2:ifly2]" << std::endl;
        return -1;
    }
    FuncType print_hook;
    int type = atoi(argv[1]);
    if (type == 1) {
        void *handle = dlopen("/speech/ifly1/libifly_library.so", RTLD_LAZY);
        if (handle == nullptr) {
            std::cout << "open failed" << std::endl;
        }
        print_hook = (FuncType)dlsym(handle, "print");
    } else if (type == 2) {
        void *handle = dlopen("/speech/ifly2/libifly_library.so", RTLD_LAZY);
        if (handle == nullptr) {
            std::cout << "open failed" << std::endl;
        }
        print_hook = (FuncType)dlsym(handle, "print");
    } else {
        print_hook = print;
    }
    
    print_hook();
    return 0;
}
