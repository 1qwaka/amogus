#!/bin/bash

gcc -std=gnu99 -g3 -Wall -Wvla -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -o main.o -c main.c
gcc -std=gnu99 -g3 -Wall -Wvla -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -o utils.o -c utils.c
gcc -o app.exe main.o utils.o -lm