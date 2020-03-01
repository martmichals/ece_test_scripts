#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prog5.h"

// This program generates images used for testing the program
int main(int argc, char* argv[]){
    char* seed_string = argv[1];
    int seed;

    sscanf(seed_string, "%d", &seed);
    srand(seed);
    start_game();


    for(int i = 2; i < argc; i++){
        int ret = make_guess(argv[i]);

        printf("Variables\n");
        printf("%d\n", ret);
        printf("%d\n", max_score);
    }

    return 0;
}
