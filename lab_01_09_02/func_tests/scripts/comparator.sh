#!/bin/bash

real=${1}
expect=${2}

real_text=$(cat "$real")
expect_text=$(cat "$expect")

if [ "${real_text#*Result: }" == "${expect_text#*Result: }" ]; then
    exit 0
else
    exit 1
fi