#!/usr/bin/env bash

#https://www.davidpashley.com/articles/writing-robust-shell-scripts/#id2382181

echo $?     # show previous exit code

#exit: if script try to use an uninitialised variable
set -u        
set -o nounset




set -e
set -o errexit


###########################################################################################################################
#On a slightly related note, by default bash takes the error status of the last item in a pipeline, which may not be what you want. 
#For example, 
#false | true 
#will be considered to have succeeded. 
#If you would like this to fail, then you can use set -o pipefail to make it fail.


#set -o pipefail
false | true



echo "OK"
