#!/bin/bash

real=${1}
expect=${2}

real_nums=$(grep -oE "[+-]?[0-9][0-9]*\.?[0-9]*" "$real")
expect_nums=$(grep -oE "[+-]?[0-9][0-9]*\.?[0-9]*" "$expect")

if [ "$real_nums" == "$expect_nums" ]; then
    exit 0
else
    exit 1
fi

