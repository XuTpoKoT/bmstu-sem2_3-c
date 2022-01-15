#!/bin/sh

cd func_tests || exit 1

./all_test.sh

cd ..

echo "Coverage report:"
gcov -f -r main.c films.c
