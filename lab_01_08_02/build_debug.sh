#!/bin/bash

gcc -std=c99 -g3 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -o main.o -c main.c
gcc -o app.exe main.o -lm