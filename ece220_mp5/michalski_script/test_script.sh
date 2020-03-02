cd michalski_script

gcc -g -std=c99 -Wall -Werror prog5.c c_runner.c -o c_runner
echo "Running the test script!"

python python_grader.py

cd ..
