#!/bin/bash
if [ -n "$1" ]
then
	args=pos_${1}_args.txt
	arg=$(cat "$args")
else
	echo "Not enough parameters."; exit 1
fi

if [ "${arg:0:1}" = "p" ]
then
	../app.exe t_to_b shared/pos_"${1}"_in.txt shared/pos_"${1}"_in.bin
	rc=$?
	if [ ${rc} -ne 0 ]
	then
		echo "Test $1 t_to_b error!"; exit 1
	fi
	
	../app.exe $(cat "$args") > my_out.txt	
	rc=$?
	if [ ${rc} -ne 0 ]
	then
		echo -e "Test $1 \e[31mFAILED\e[0m rc = ${rc}"; exit 1
	fi

	file1="my_out.txt" && file2="pos_${1}_out.txt"
	if cmp "$file1" "$file2"
	then
		echo -e "Test $1 \e[32mOK\e[0m"; exit 0
	else
		echo -e "Test $1 \e[31mFAILED\e[0m"
		diff -y "${file1}" "${file2}"; exit 1		
	fi
fi

if [ "${arg:0:1}" = "s" ]
then
	../app.exe t_to_b shared/pos_"${1}"_in.txt shared/pos_"${1}"_in.bin
	rc=$?
	if [ ${rc} -ne 0 ]
	then
		echo "Test $1 t_to_b error!"; exit 1
	fi
	
	../app.exe $(cat "$args")	
	rc=$?
	if [ ${rc} -ne 0 ]
	then
		echo -e "Test $1 \e[31mFAILED\e[0m rc = ${rc}"; exit 1
	fi
	
	../app.exe b_to_t shared/pos_"${1}"_in.bin my_out.txt
	rc=$?
	if [ ${rc} -ne 0 ]
	then
		echo "Test $1 b_to_t error!"; exit 1
	fi

	file1="my_out.txt" && file2="shared/pos_${1}_out.txt"
	if cmp "$file1" "$file2"
	then
		echo -e "Test $1 \e[32mOK\e[0m"; exit 0
	else
		echo -e "Test $1 \e[31mFAILED\e[0m"
		diff -y "${file1}" "${file2}"; exit 1		
	fi
fi


echo "Test $1 unknown key!"; exit 1
