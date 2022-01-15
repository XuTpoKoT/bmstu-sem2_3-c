#!/bin/sh
gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -g3 -c --coverage product.c
gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion -Wvla -g3 -c --coverage main.c
gcc -o app.exe --coverage main.o product.o