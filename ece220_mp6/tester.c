// Standard libraries in C
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

// File user's file
#include "updateBoard.h"

// Function prototypes
int test_neighbors(int* board, int row, int column, int numRows, int numCols, int golden_response, char* spawn_file);

// Struct used to create linked list to store all the filenames
typedef struct filename{
    char name[20];
    struct filename* next;
}filename_t;

/* Function to check whether the user's check neighbor function is working correctly
 * @return: 0 if the user's function matches the proper number of neighbors
 *          1: if the user's function does not match the proper number of neighbors
 */
int test_neighbors(int* board, int row, int column, int numRows, int numCols, int golden_response, char* spawn_file){
    int result = countLiveNeighbor(board, numRows, numCols, row, column);

    if(result == golden_response)
        return 0;

    printf("\nError in countLiveNeighbor()\nInput File: ");

    int c;
    printf("%c", spawn_file[0]);
    for (c = 1; spawn_file[c] != '.'; c++)
        printf("%c", spawn_file[c]);

    printf("%s\n", ".in");
    printf("Row: %d\n", row);
    printf("Column: %d\n\n", column);
    printf("Expected Return: %d\n", golden_response);
    printf("Your Return: %d\n\n", result);

    return 1;
}

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
                rows--;
                cols--;

                int* game_board = malloc(rows*cols*sizeof(int));
                int i, j;
                for(i = 0; i < rows; i++){
                    for(j = 0; j < cols; j++){
                        fscanf(fp, "%d", &game_board[cols*i+j]);
                    }
                }
                // Iterate through and test the neighbors function
                strcpy(buffer, "./txt_boards/");
                strcat(buffer, filename);
                strcat(buffer, ".neighbors");

                FILE* neighbor_ptr;
                neighbor_ptr = fopen(buffer, "r");
                //int rr, cc;
                //for(rr = 0; rr < rows; rr++){
                //    for(cc = 0; cc < cols; cc++){
                //       printf("%d ", game_board[cols*rr+cc]);
                //    }
                //    printf("\n");
                //}
                printf("Testing neighbors against %s\n", buffer);
                if(neighbor_ptr){
                    int r_in, c_in, proper_out;
                    while(fscanf(neighbor_ptr, "%d, %d, %d\n", &r_in, &c_in, &proper_out) != EOF){
                        int test_failure = test_neighbors(game_board, r_in, c_in, rows, cols, proper_out, buffer);
                        if(test_failure)
                            return 0; 
                    }
                }else{
                    printf("Error opening %s.\nTerminating the program.", buffer);
                    return 1;
                }
                fclose(neighbor_ptr);

                // Freeing up the dynamic memory used by game_board
                free(game_board);
            }else{
                printf("Error opening %s.\nTerminating the program.", buffer);
                return 1;
            }
            fclose(fp);

            free(top_ptr);
            top_ptr = top_ptr->next;
        }while(top_ptr != NULL);
        free(top_ptr);
    }
    return 0;
}
