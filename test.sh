#!/bin/bash

count=100

gcc ./快排转非递归.c -o test_sort
for((i = 0; $i < count; i = $i + 1));do
    python test.py
    ./test_sort < input > new_output
    a=$(diff output new_output | wc -l)
    if [ $a -eq 0 ];then
        echo "$i pass"
    else 
        echo "$i failed"
        exit
    fi
done
