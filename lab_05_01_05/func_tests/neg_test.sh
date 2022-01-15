#!/bin/bash
if [ -n "$1" ]
then
	../app.exe < neg_"${1}"_in.txt > my_out.txt
else
	echo "No parameters."; exit 1
fi

rc=$?
if [ ${rc} -ne 0 ]
then
	echo -e "Test $1 \e[32mOK\e[0m"
else
	echo -e "Test $1 \e[31mFAILED\e[0m"
fi

rm my_out.txt
exit 0
