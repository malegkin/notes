/////////////////
// $ cc -g t_mtrace.c -o t_mtrace
// $ export MALLOC_TRACE=/tmp/t
// $ ./t_mtrace
// $ mtrace ./t_mtrace $MALLOC_TRACE
// Memory not freed:
// -----------------
//    Address     Size     Caller
// 0x084c9378     0x64  at /home/cecilia/t_mtrace.c:12
// 0x084c93e0     0x64  at /home/cecilia/t_mtrace.c:12
// 0x084c9448    0x100  at /home/cecilia/t_mtrace.c:16


#include <mcheck.h>
#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    int j;

   mtrace();

   for (j = 0; j < 2; j++)
        malloc(100);            /* Never freed--a memory leak */

   calloc(16, 16);             /* Never freed--a memory leak */
    exit(EXIT_SUCCESS);
}
