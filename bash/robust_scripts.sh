#!/usr/bin/env bash

#https://www.davidpashley.com/articles/writing-robust-shell-scripts/#id2382181

echo $?     # show previous exit code

###########################################################################################################################
#exit the script if any statement returns a non-true return value
set -e
#set -o errexit


#alternatives:
lsd 2>&1 >/dev/null
if [[ "$?" -ne 0 ]]; 
then 
    echo "command failed"; 
#    exit 1; 
fi


lsd 2>&1 >/dev/null || { 
    echo "command failed"; 
#    exit 1; 
}


###############
## || true - ignore error in subprocess
( echo "test"; exit -1; ) || true       # () - run in new suprocess
#{ echo "test"; exit -1; } || true       # {} - run in thread


###########################################################################################################################
#exit: if script try to use an uninitialised variable
set -u        
set -o nounset

#echo $TEST_AAAAAAAAAAAA

###########################################################################################################################
#On a slightly related note, by default bash takes the error status of the last item in a pipeline, which may not be what you want. 
#For example, 
#false | true 
#will be considered to have succeeded. 
#If you would like this to fail, then you can use set -o pipefail to make it fail.


#set -o pipefail
false | true



echo "OK"
