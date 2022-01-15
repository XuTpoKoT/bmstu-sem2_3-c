#!/bin/bash

count_pos=$(find . -maxdepth 1 -name "pos_*_in.txt" | wc -l)
count_neg=$(find . -maxdepth 1 -name "neg_*_in.txt" | wc -l)

echo "Positive tests:"
for ((i = 1; i <= count_pos; i++))
do
    if [ "$i" -le 9 ]
	then ./pos_test.sh "0${i}"
	else ./pos_test.sh "${i}"
	fi
done

echo
echo "Negative tests:"
for ((i = 1; i <= count_neg; i++))
do
    if [ "$i" -le 9 ]
	then ./neg_test.sh "0${i}"
	else ./neg_test.sh "${i}"
	fi
done

rm console_out.txt
