python3 setup_dir_structure.py
gcc -Wall -g -I include/ -L lib/ tester.c updateBoard.c -o tester -lncurses
python gen_file_list.py > files.txt

./tester
