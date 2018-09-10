#!/usr/bin/env bash
#https://mnorin.com/razlichie-skobok-v-bash.html


#If you want the side-effects of the command list to affect your current shell, use {...}
#If you want to discard any side-effects, use (...)
    # want to alter $IFS for a few commands, but I don't want to alter $IFS globally for the current shell
    # cd somewhere, but I don't want to change the $PWD for the current shell


#() eq for old ``



#() vs {} benchmark

echo "using ():"
/usr/bin/time ( for i in {1..1000}
    do
        ls | (
            ls > /dev/null
        )
    done 
)

echo "using {}:"

/usr/bin/time ( for i in {1..1000}
    do
        ls | {
            ls > /dev/null
        }
    done 
)

