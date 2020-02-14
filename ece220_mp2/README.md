# Test Scripts for MP 2

<h2>Getting Started</h2>

Installation of required packages<br>

```shell
apt-get install except
```

<h2>Setup & Use</h2>

Run these commands in the cloned repository to enable the scripts to run.
```shell
chmod 755 run.sh
chmod 755 test_script.sh
```

Copy over the scripts to the directory w/prog2.asm
```shell
cp run.sh MP_WORKING_DIRECTORY
cp test_script.sh MP_WORKING_DIRECTORY
```

To run the script:
```shell
cd MP_WORKING_DIRECTORY
./test_script.sh
```
IMPORTANT: Your prompt must end with ">" for these scripts to work. See below for example.
```shell
Enter a postfix expression >
```

<h4>To modify test cases:</h4><br>
1) Open test_script.sh in an editor<br>
2) Modify one of values in prompts<br>
3) Modify the corresponding value in answers to the answer of the prompt

<h2>DISCLAIMER + LIMITATIONS</h2>
The scripts written only work to test valid expressions. Will not work to test program functionality for invalid expressions. I am by no means a course TA/Instructor. I just wrote these to ease the testing process for me and a couple of friends.  
