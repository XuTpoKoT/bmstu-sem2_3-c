#!/bin/sh
gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -g3 -c --coverage sequence.c
gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -g3 -c --coverage main.c
gcc -o app.exe --coverage main.o sequence.o