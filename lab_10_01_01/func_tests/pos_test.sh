#!/bin/bash
if [ -n "$1" ]
then
	args=pos_${1}_args.txt
else
	echo "Not enough parameters."; exit 1
fi

valgrind ../app.exe $(cat "$args") > console_out.txt
rc=$?
if [ ${rc} -ne 0 ]
then
	echo -e "Test $1 \e[31mFAILED\e[0m rc = ${rc}"; exit 1
fi

file1="console_out.txt" && file2="pos_${1}_out.txt"
if cmp "$file1" "$file2"
then
	echo -e "Test $1 \e[32mOK\e[0m"; exit 0
else
	echo -e "Test $1 \e[31mFAILED\e[0m"
	diff -y "${file1}" "${file2}"
	exit 1
fi
