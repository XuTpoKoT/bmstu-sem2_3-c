#!/bin/bash
if [ -n "$1" ]
then
	valgrind --leak-check=full ../app.exe < neg_${1}_in.txt > console_out.txt
else
	echo "Not enough parameters."; exit 1
fi

rc=$?
if [ ${rc} -ne 0 ]
then
	echo -e "Test $1 \e[32mOK\e[0m"
    exit 0
else
	echo -e "Test $1 \e[31mFAILED\e[0m"
    exit 1
fi

