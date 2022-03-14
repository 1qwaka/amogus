#!/bin/bash

dir=$(dirname "${0}")
stream_in="${1}"
out_expect="${2}"
args_file="${3}"

if [ -f "$args_file" ]; then
    args=$(cat "$args_file")
else
    args=""
fi

set -f
if [ -z "$(printenv USE_VALGRIND)" ]; then
    "$dir"/../../app.exe $args < "$stream_in" > out.txt
else 
    valgrind "$dir"/../../app.exe $args < "$stream_in" > out.txt
fi
return_code="$?"
set +f

if "$dir"/comparator.sh out.txt "$out_expect" && [ "$return_code" -eq 0 ]; then
    exit 0
else
    exit 1
fi
