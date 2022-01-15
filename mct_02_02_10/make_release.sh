#!/bin/sh
gcc -std=c99 -Werror -Wall -Wextra -Wpedantic -Wvla -c main.c
gcc -std=c99 -Werror -Wall -Wextra -Wpedantic -Wvla -c students.c
gcc -o app.exe main.o students.o