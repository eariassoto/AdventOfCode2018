#!/bin/sh
file=`cat input.txt | sort | cut -c16-17,19- | sed "s/[0-9][0-9] Guard #/+/g" | sed "s/[a-zA-z ]//g"`
echo "$file"