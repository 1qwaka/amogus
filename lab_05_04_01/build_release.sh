#!/bin/bash

gcc -std=gnu99 -Wall -Wvla -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -c *.c
gcc -o app.exe ./*.o -lm