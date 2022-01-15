#!/bin/bash

CFLAGS="-std=c99 -Wall -Werror -Wextra -pedantic"

INC_DIR=../inc/

gcc $CFLAGS -I$INC_DIR -c main.c ../src/arr.c
gcc -o app.exe main.o arr.o

for ((i = 1; i <= 10; i++))
do
	python3 datagen.py 10 >data_10_1.txt
	python3 datagen.py 30 >data_30_1.txt
	python3 datagen.py 100 >data_100_1.txt
	python3 datagen.py 300 >data_300_1.txt
	python3 datagen.py 1000 >data_1000_1.txt
	python3 datagen.py 1500 >data_1500_1.txt
	python3 datagen.py 2000 >data_2000_1.txt
	python3 datagen.py 2500 >data_2500_1.txt
	python3 datagen.py 3000 >data_3000_1.txt
	./app.exe data_10_1.txt >> time_10_1.txt
	./app.exe data_30_1.txt >> time_30_1.txt
	./app.exe data_100_1.txt >> time_100_1.txt
	./app.exe data_300_1.txt >> time_300_1.txt
	./app.exe data_1000_1.txt >> time_1000_1.txt
	./app.exe data_1500_1.txt >> time_1500_1.txt
	./app.exe data_2000_1.txt >> time_2000_1.txt
	./app.exe data_2500_1.txt >> time_2500_1.txt
	./app.exe data_3000_1.txt >> time_3000_1.txt
done

gcc $CFLAGS -I$INC_DIR -c main2.c ../src/arr.c
gcc -o app.exe main2.o arr.o

for ((i = 1; i <= 10; i++))
do
	python3 datagen.py 10 >data_10_2.txt
	python3 datagen.py 30 >data_30_2.txt
	python3 datagen.py 100 >data_100_2.txt
	python3 datagen.py 300 >data_300_2.txt
	python3 datagen.py 1000 >data_1000_2.txt
	python3 datagen.py 1500 >data_1500_2.txt
	python3 datagen.py 2000 >data_2000_2.txt
	python3 datagen.py 2500 >data_2500_2.txt
	python3 datagen.py 3000 >data_3000_2.txt
	./app.exe data_10_2.txt >> time_10_2.txt
	./app.exe data_30_2.txt >> time_30_2.txt
	./app.exe data_100_2.txt >> time_100_2.txt
	./app.exe data_300_2.txt >> time_300_2.txt
	./app.exe data_1000_2.txt >> time_1000_2.txt
	./app.exe data_1500_2.txt >> time_1500_2.txt
	./app.exe data_2000_2.txt >> time_2000_2.txt
	./app.exe data_2500_2.txt >> time_2500_2.txt
	./app.exe data_3000_2.txt >> time_3000_2.txt
done

python3 time_avg.py 10
python3 time_avg.py 30
python3 time_avg.py 100
python3 time_avg.py 300
python3 time_avg.py 1000
python3 time_avg.py 1500
python3 time_avg.py 2000
python3 time_avg.py 2500
python3 time_avg.py 3000

python3 table_md.py

rm -r -f *.o *.exe data*.txt time*.txt 

