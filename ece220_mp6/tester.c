// Standard libraries in C
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

// File user's file
#include "updateBoard.h"

// Function prototypes
int test_neighbors(int* board, int row, int column, int numRows, int numCols);

// Struct used to create linked list to store all the filenames
typedef struct filename{
    char name[20];
    struct filename* next;
}filename_t;

/* Function to check whether the user's check neighbor function is working correctly
 * @return: 0 if the user's function matches the proper number of neighbors
 *          1: if the user's function does not match the proper number of neighbors
 */
int test_neighbors(int* board, int row, int column, int numRows, int numCols){
    return 0;
}

// TODO: Make sure to deallocate all the space used for storing file names
int main(int argc, char const *argv[]){

    // Pull all the file names and store into an linked list
    FILE* fp;
    fp = fopen("files.txt", "r");

    filename_t* top_ptr = (filename_t*) malloc(sizeof(filename_t));
    char buffer[50];
    if(fp){
        fscanf(fp, "%s", top_ptr->name);
        top_ptr->next = NULL;                                           // This will signify the end of the linked list

        while(fscanf(fp, "%s", buffer) != EOF){
            filename_t* new_top = (filename_t*) malloc(sizeof(filename_t));
            strcpy(new_top->name, buffer);
            new_top->next = top_ptr;
            top_ptr = new_top;
        }
        fclose(fp);
    }else{
        printf("Error opening the input file.\nTerminating the program.");
        return 1;
    }

    // Iteration over the linked list
    if(top_ptr == NULL){
        printf("Error in parsing the linked list in test script.\nTerminating the program");
        return 1;
    }else{
        do{
            char* filename = top_ptr->name;

            strcpy(buffer, "./txt_boards/");
            strcat(buffer, filename);
            strcat(buffer, ".in");

            // Open the input file and read in the intial board
            FILE* fp;
            fp = fopen(buffer, "r");

            // Grab metadata and board contents
            int rows, cols;
            if(fp){
                fscanf(fp, "%d", &rows);
                fscanf(fp, "%d", &cols);
                //printf("The file %s has %d rows and %d columns\n",buffer ,rows, cols);
                int* game_board = malloc(rows*cols*sizeof(int));
                int* fill_ptr = game_board;
                int i, j;
                for(i = 0; i < cols; i++){
                    for(j = 0; j < rows; j++){
                        fscanf(fp, "%d", fill_ptr);
                        fill_ptr++;
                    }
                }
            }else{
                printf("Error opening %s.\nTerminating the program.", buffer);
            }
            fclose(fp);


            //free(game_board);
            free(top_ptr);

            top_ptr = top_ptr->next;
        }while(top_ptr != NULL);
        free(top_ptr);
    }

    return 0;
}
