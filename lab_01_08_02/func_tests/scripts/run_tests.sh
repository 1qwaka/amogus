#!/bin/bash

cd "$(dirname "$0")" && cd .. || exit

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -o ../main.exe ../main.c -lm

if [ ! -f ../main.exe ]; then
    echo -e "executable 'main.exe' doesn't exists, please compile code first"
    exit
fi

i=1
while true
do
    if [ $i -lt 10 ]; then
        i=0$i
    #     input_file="pos_0${i}_in.txt"
    #     output_file="pos_0${i}_out.txt"
    # else 
    #     input_file="pos_${i}_in.txt"
    #     output_file="pos_${i}_out.txt"
    fi
    input_file=data/pos_${i}_in.txt
    output_file=data/pos_${i}_out.txt
    # input_file=data/$input_file
    # output_file=data/$output_file

    if [ ! -f $input_file ]; then
        i=$((i-1))
        echo total positive tests: ${i#0}
        break
    fi

    if [ ! -f "$output_file" ]; then
        echo "$(tput setaf 1)no output for test $i$(tput sgr0)"
        continue
    fi

    ../main.exe < $input_file > out.txt
    
    if cmp -s out.txt "$output_file"; then
        echo "POS $i $(tput setaf 2)(PASSED)$(tput sgr0)"
    else
        echo "POS $i $(tput setaf 1)(FAILED)$(tput sgr0)"
    fi

    i=$((i+1))
done


i=1
while true
do
    if [ $i -lt 10 ]; then
        i=0$i
    fi
    input_file=data/neg_${i}_in.txt
    output_file=data/neg_${i}_out.txt

    if [ ! -f $input_file ]; then
        i=$((i-1))
        echo total negative tests: ${i#0}
        break
    fi

    if [ ! -f "$output_file" ]; then
        echo "$(tput setaf 1)no output for test $i$(tput sgr0)"
        continue
    fi

    ../main.exe < $input_file > out.txt
    
    if cmp -s out.txt "$output_file"; then
        echo "NEG $i $(tput setaf 2)(PASSED)$(tput sgr0)"
    else
        echo "NEG $i $(tput setaf 1)(FAILED)$(tput sgr0)"
    fi
    
    i=$((i+1))
done

rm -f out.txt ../main.exe