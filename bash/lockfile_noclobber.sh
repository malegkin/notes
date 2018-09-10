#!/usr/bin/env bash
#https://stackoverflow.com/questions/1715137/what-is-the-best-way-to-ensure-only-one-instance-of-a-bash-script-is-running

 function lockfile_waithold()
 {
    declare -ir time_beg=$(date '+%s')
    declare -ir maxtime=7140  # 7140 s = 1 hour 59 min.

    # waiting up to ${maxtime}s for /tmp/global.lock ...
    while ! \
       (set -o noclobber ; \
        echo -e "DATE:$(date)\nUSER:$(whoami)\nPID:$$" > /tmp/global.lock \ 
       ) 2>/dev/null
    do
        if [ $(( $(date '+%s') - ${time_beg})) -gt ${maxtime} ] ; then
            echo "waited too long for /tmp/global.lock" 1>&2
            return 1
        fi
        sleep 1
    done

    return 0
 }

 function lockfile_release()
 {
    rm -f /tmp/global.lock
 }

 if ! lockfile_waithold ; then
      exit 1
 fi

    echo "go"
    sleep 100

 lockfile_release
