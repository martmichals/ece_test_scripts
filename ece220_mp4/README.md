# Test Scripts for MP 4

<h2>Description</h2>
A test script to test all required cases in MP 4. Make sure to have the exact prompt as in the MP description, as well as properly formatted output.

<h2>Getting Started</h2>

Cloning this repo:<br>
```shell
git clone "https://github.com/martmichals/ece_test_scripts/"
```

<h2>Setup & Use</h2>

Navigate into the ece220_mp4 submodule:
```shell
cd ece_test_scripts/ece220_mp4/
```

Copy over mp4.c into the repo:
```shell
cp ~/PATH_TO_YOUR_MP4_DIRECTORY/m4.c ./
```

Run this command to allow the script to run.
```shell
chmod 755 test_script.sh
```

<h2>Running the script</h2>

The script has two modes. Random mode selects 250 random test cases:
```shell
./test_script.sh random
```

All mode runs through all possible test cases (~15mins):
```shell
./test_script.sh all
```

<h2>DISCLAIMER</h2>
I am by no means a course TA/Instructor. I wrote these to ease the testing process for me and a couple of friends.  
