#!/bin/bash
ARG1="$1"

if [ "$ARG1" = "loop" ]; then
	for i in {1..5}
		do
   			 echo $ARG1
    			echo $i >> count.log
   			ps > processes.log
		done
fi

