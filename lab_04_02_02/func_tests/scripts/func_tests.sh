#!/bin/bash

dir=$(dirname "$0")
# 0 is flase; 1 is true; пока что не задается через аргументы
silent=0

total=0
pos_failed=0
neg_failed=0

i=1
while true
do
    if [ $i -lt 10 ]; then
        i=0$i
    fi

    input_file="$dir"/../data/pos_${i}_in.txt
    output_file="$dir"/../data/pos_${i}_out.txt
    args_file="$dir"/../data/pos_${i}_args.txt

    if [ ! -f "$input_file" ]; then
        i=$((i-1))
        total=$((total+i))
        if [ "$silent" -eq 0 ]; then
            if [ "$i" -ne 0 ]; then
                i="${i#0}"
            fi
            echo "total positive tests: $i"
        fi
        break
    fi

    if [ ! -f "$output_file" ]; then

        if [ "$silent" -eq 0 ]; then
            echo "$(tput setaf 1)no output for test $i$(tput sgr0)"
        fi

        continue
    fi
    
    if "$dir"/pos_case.sh "$input_file" "$output_file" "$args_file"; then
        if [ "$silent" -eq 0 ]; then
            echo "POS $i $(tput setaf 2)(PASSED)$(tput sgr0)"
        fi
    else
        if [ "$silent" -eq 0 ]; then
            echo "POS $i $(tput setaf 1)(FAILED)$(tput sgr0)"
        fi

        pos_failed=$((pos_failed+1))
    fi

    i=${i#0}
    i=$((i+1))
done



i=1
while true
do
    if [ $i -lt 10 ]; then
        i=0$i
    fi

    input_file="$dir"/../data/neg_${i}_in.txt
    output_file="$dir"/../data/neg_${i}_out.txt
    args_file="$dir"/../data/neg_${i}_args.txt

    if [ ! -f "$input_file" ]; then
        i=$((i-1))
        total=$((total+i))
        if [ "$silent" -eq 0 ]; then
            if [ "$i" -ne 0 ]; then
                i="${i#0}"
            fi
            echo "total negative tests: ${i}"
        fi
        break
    fi
    
    if "$dir"/neg_case.sh "$input_file" "$args_file"; then
        if [ "$silent" -eq 0 ]; then
            echo "NEG $i $(tput setaf 2)(PASSED)$(tput sgr0)"
        fi
    else
        if [ "$silent" -eq 0 ]; then
            echo "NEG $i $(tput setaf 1)(FAILED)$(tput sgr0)"
        fi

        neg_failed=$((neg_failed+1))
    fi

    i=${i#0}
    i=$((i+1))
done

total_failed=$((neg_failed+pos_failed))
exit $total_failed