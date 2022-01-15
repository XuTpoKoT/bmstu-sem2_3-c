#!/bin/sh
gcc -std=c99 -Werror -Wall -Wextra -Wpedantic -Wvla --coverage -g3 -c main.c
gcc -std=c99 -Werror -Wall -Wextra -Wpedantic -Wvla --coverage -g3 -c str.c
gcc -o app.exe --coverage main.o str.o