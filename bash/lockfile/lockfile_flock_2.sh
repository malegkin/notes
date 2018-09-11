#/usr/bin/env bash

#for i in 1 2 3 ; do ./tstlocks ~ & done


exec < "${1}"
flock 0
echo locked by ${$}

sleep 5

flock -u 0
echo unlocked by ${$}

echo ${$} ended

exit

