#!/usr/bin/env bash

############
# env       -- set environment and execute command, or print environment
# export    -- builtin
# set       -- builtin 


#local
echo "$TEST_ENV_1"
TEST_ENV_1="TEST_ENV_1"
echo "$TEST_ENV_1"

#Promote a local variable to an environment variable:
echo  "$TEST_ENV_2"
export TEST_ENV_2="TEST_ENV_2"
echo "$TEST_ENV_2"

echo  "$TEST_ENV_3"
TEST_ENV_3="TEST_ENV_3"
echo "$TEST_ENV_3"



if [[ $@ -eq 0 ]]; then
    echo ""
    echo "Test env from child process:"
    env TEST_ENV_3="TEST_ENV_3" "$0" 1
fi

