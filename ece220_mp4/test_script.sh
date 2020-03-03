#!/bin/bash

file="mp4.c"
out=$(gcc -Wall -g "$file" -std=c99 -o mp4)

if [ $? -ne 0 ]; then
    echo $file " compiled with errors. Halting test."
    exit
else
    echo $file " compiled successfully. Continuing."
    row=1
    successful=0
    total=0
    
    input_file="alltestcases"
    proper_out="semiprime_outputall.txt"
    if [[ "$1" ==  "all" ]]; then
        while read line; do
            desired_output=$(sed -n "$row"p "$proper_out")
            mp4_output=$(echo "$line" | ./mp4)
            echo "Input: $line"

            if [[ "$desired_output" == "$mp4_output" ]]; then
                echo "Test passed."
                echo
                successful=$((successful + 1))
            elif [[ "$desired_output" == "$mp4_output " ]]; then
                echo "Test passed."
                echo
                successful=$((successful + 1))
            else
                echo "Test failed."
                echo "Your output: $mp4_output"
                echo "Desired output: $desired_output"
                echo 
            fi

            row=$((row + 1))
            total=$((total + 1))
        done < "$input_file"

    elif [[ "$1" == random ]]; then
        rando_count=0
        while [ $rando_count -ne 250 ]
        do
            line_num=$(shuf -i 1-20100 -n 1)

            desired_output=$(sed -n "$line_num"p "$proper_out")
            in=$(sed -n "$line_num"p "$input_file")
            mp4_output=$(echo "$in" | ./mp4)
            echo "Input: $in"

            if [[ "$desired_output" == "$mp4_output" ]]; then
                echo "Test passed."
                echo
                successful=$((successful + 1))
            elif [[ "$desired_output" == "$mp4_output " ]]; then
                echo "Test passed."
                echo
                successful=$((successful + 1))
            else
                echo "Test failed."
                echo "Your output: $mp4_output"
                echo "Desired output: $desired_output"
                echo 
            fi

            rando_count=$((rando_count+1))
            total=$((total + 1))
        done

    else
        echo "Invalid argument $1"
        exit
    fi

    echo "Test results: $successful/$total passed."
fi


