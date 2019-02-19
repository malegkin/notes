#!/usr/bin/env bash 
set -e
set -o pipefail
set -u

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
SRC="main.cpp"
TESTS_DIR="$DIR/tests"

if [ $# -gt 0 ] ; then
    SRC="$1"
fi

#compile
rm -f "$DIR/a.out" 
case $(echo "$SRC" | sed 's/^.*\.//') in
"cpp")
    echo "COMPILE"
#-stack_size size
#                 Specifies the maximum stack size for the main thread in a program.  Without this option a program has a 8MB stack.  The argu-
#                 ment size is a hexadecimal number with an optional leading 0x. The size should be a multiple of the architecture's page size (4KB or 16KB).
    g++ -fno-strict-aliasing -DONLINE_JUDGE -lm -x c++ -std=c++14 -Wl,-stack_size,0x600000 -O2 "$DIR/$SRC"
;;

"c")
    gcc -fno-strict-aliasing -DONLINE_JUDGE -lm -std=c11 -Wl,-stack_size,0x600000 -O2 "$DIR/$SRC" 
;;
esac

"$DIR/a.out"
