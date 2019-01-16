// otool -lV ./a.out | grep stack
// g++ -std=c++14 -Wl,-stack_size,0x200000 ./stack_test.cpp && ./a.out
#include <iostream>
#include <functional>
#include <unistd.h>


rlim_t check_max_value( rlim_t l, rlim_t r, const std::function<bool(rlim_t)> checker )
{
    rlim_t middle;

    while( l <= r ){
        middle = (l + r)/2;

        if (checker(middle)){
            l = middle + 1;
        } else {
            r = middle - 1;
        }
    }

    return checker(middle)? middle : middle - 1;
}


int main(int argc, char **argv)
{
    struct rlimit lim;
    getrlimit( RLIMIT_STACK, &lim );

    rlim_t rlim_real =  check_max_value( 0, lim.rlim_cur, [&](auto a) {
        std::cout << "check: " << a ;
        int pid = fork();
        if( !pid ) {
            // Child would crash with a segfault if stack overflows 
            uint8_t arr[a];
            exit(0);
        }
        int status;
        waitpid(pid, &status, WUNTRACED);
        if( !status )
        {
            // Child exited normally and not because of a segfault. 
            std::cout << " - OK"<< std::endl;
            return true;
        }

        std::cout << " - FAIL"<< std::endl;
        return false;
    });

    std::cout << "Current: " << lim.rlim_cur << std::endl;
    std::cout << "Maximal: " << lim.rlim_max << std::endl;
    std::cout << "Real:    " << rlim_real << std::endl;


    return 0;
}
