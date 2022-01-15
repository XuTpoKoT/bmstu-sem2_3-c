#!/bin/bash
if [ -n "$1" ]
then
	args=neg_${1}_args.txt
else
	echo "Not enough parameters."; exit 1
fi

../app.exe $(cat "$args") > my_out.txt
rc=$?
if [ ${rc} -ne 0 ]
then
	echo -e "Test $1 \e[32mOK\e[0m"
else
	echo -e "Test $1 \e[31mFAILED\e[0m"
fi

rm my_out.txt
exit 0
