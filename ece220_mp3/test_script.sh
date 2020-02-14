file="mp3.c"
out=$(gcc -Wall -g "$file" -std=c99 -o mp3)

if [ $? -ne 0 ]; then
    echo $file " compiled with errors. Halting test."
    exit
else
    echo $file " compiled successfully. Continuing."
   
    row=0
    tests_passed=0
    while IFS= read -r line;
    do
        ./mp3 <<< "$row\n" > out
        row=$((row + 1))

        prog_out=$(head -n 1 out)
        prog_out=${prog_out:19}

        if [[ "$line" == "$prog_out" ]]; then
            echo "Test passed."
            tests_passed=$((tests_passed + 1))
        else
            echo ""
            echo "Test Failed."
            echo "Program output: $prog_out"
            echo "Proper output: $line"
            echo "Test Number: $row"
            echo ""
        fi
    done < "pascal40"
    echo ""
    echo "Test complete. $tests_passed/$row cases passed."
fi


