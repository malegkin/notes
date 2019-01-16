#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <functional>
#define LARGE (2097152); /* 8MB/sizeof(int) */

rlim_t check_max_value( rlim_t l, rlim_t r, const std::function<bool(rlim_t)> checker )
{
    rlim_t middle;

    while( l <= r){
        middle = (l+r)/2;

        if (checker(middle)){
            l = middle + 1;
        } else {
            r = middle - 1;
        }
    }

    return middle - 1;
}


int main(int argc, char **argv)
{

        struct rlimit lim;
    getrlimit( RLIMIT_STACK, &lim );
    std::cout << lim.rlim_cur << "\n";
    std::cout << lim.rlim_max << "\n";


    check_max_value( 0, lim.rlim_cur/4096, [](auto a) {
        int pid = fork();
        if( !pid ) {
            /* Child would crash with a segfault if stack overflows */
            int arr[a];
        }
        int status = 0;
        waitpid(pid, &status, WUNTRACED);
        if(WIFEXITED(status))
        {
            /* Child exited normally and not because of a segfault. */
            printf("Estimated stack size is %d\n", a * 4096);
            return true;
        }

        return false;
    });

   return 0;
}
