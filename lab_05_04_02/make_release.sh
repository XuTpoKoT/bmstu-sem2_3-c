#!/bin/sh
gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -c product.c
gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -c main.c
gcc -o app.exe main.o product.o