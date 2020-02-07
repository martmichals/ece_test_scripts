declare -a prompts=("22+="
                    "23*="
                    "22+4+55++="
                    "1 2 +     ="
                    "7 4 *="
                    "42/="
                    "12/="
                    "53+4/3^1*="
                    "512+4*+3-="
                    "22^2^="
                    "20^11++="
                    "00^="
                    "02^="
                    "35-3^="
                    "14-2/="
                    "11-8-="
                    "34642/*-^="
                    "000*^="
                    "33+6-0+0-0*="
                    "10*=")   

declare -a answers=("0004"
                    "0006"
                    "0012"
                    "0003"
                    "001C"
                    "0002"
                    "0000"
                    "0008"
                    "000E"
                    "0010"
                    "0003"
                    "0001"
                    "0000"
                    "FFF8"
                    "FFFF"
                    "FFF8"
                    "0003"
                    "0001"
                    "0000"
                    "0000")
# Initializing a counter variable
declare -i number_correct=0

# Loop to iterate over all the test cases and check if they match
for i in "${!prompts[@]}"
    do 

        ./run.sh "${prompts[$i]}" | grep R5 > output
        line=`awk 'NR==2,/R5/{print $line}' output`
        OUT=$(echo $line | cut -d ' ' -f 6)
        assembled="R5=x${answers[$i]}"

        if [ "$assembled" == "$OUT" ]
        then 
            echo "${prompts[$i]} ${answers[$i]} Correct."
            number_correct=$(( number_correct + 1))
        else
            user_ans=`echo $OUT | cut -c5-8`
            echo "${prompts[$i]} $user_ans Does not match."
        fi
       
    done

# Printing of the test results
echo ""
echo "Result: $number_correct/${#prompts[@]}"
if [ "$number_correct" == "${#prompts[@]}" ]
then 
    echo "Congrats! Your program passed all the test cases."
fi
echo ""
