#!/bin/sh
gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla --coverage -c my_string.c
gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla --coverage -c main.c
gcc -o app.exe --coverage main.o my_string.o

./app.exe

rc=$?
echo "rc = ${rc}"
echo
echo "Coverage report:"
gcov -f -r main.c my_string.c