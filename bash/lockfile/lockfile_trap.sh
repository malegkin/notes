#!/usr/bin/env bash

lockfile=/tmp/lock123


# ALLERT!!! must trap of signals ::
#INT	Interrupt – This signal is sent when someone kills the script by pressing ctrl-c.
#TERM	Terminate – this signal is sent when someone sends the TERM signal using the kill command.
#EXIT	Exit – this is a pseudo-signal and is triggered when your script exits, either through reaching the end of the script, an exit command or by a command failing when usingset -e.


if [ ! -e $lockfile ]; then
   trap "rm -f $lockfile; exit" INT TERM EXIT
   touch $lockfile
   
        #critical section
        sleep 100
        #end

   rm $lockfile
   trap - INT TERM EXIT
else
   echo "critical-section is already running"
fi
