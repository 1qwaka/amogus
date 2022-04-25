#!/bin/bash

gcc -std=c99 -Wall -Wvla -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -o main.o -c main.c
gcc -o app.exe main.o -lm