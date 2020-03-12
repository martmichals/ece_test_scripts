// Standard libraries in C
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// File user's file
#include "updateBoard.h"

// Number of file counter
int file_count = 1;

// Function prototypes
int test_neighbors(int* board, int row, int column, int numRows, int numCols, int golden_response, char* spawn_file);
int test_update(int* golden_board, int* user_board, int numRows, int numCols, int iteration);
int test_alive(int * board, int numRows, int numCols, int expected, int iteration);
void print_board(int* board, int boardRowSize, int boardColSize);

// Struct used to create linked list to store all the filenames
typedef struct filename{
    char name[20];
    struct filename* next;
}filename_t;

/* Function to check whether the user's check neighbor function is working correctly
 * @return: 0: if the user's function matches the proper number of neighbors
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
    
    printf("\n");
    int rr, cc;
    for(rr = 0; rr < numRows; rr++){
        for(cc = 0; cc < numCols; cc++){
           printf("%d ", board[numCols*rr+cc]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Row: %d\n", row);
    printf("Column: %d\n\n", column);
    printf("Expected Return: %d\n", golden_response);
    printf("Your Return: %d\n\n", result);

    return 1;
}

/* Function to check whether the user's updateBoard function is working properly
 * @return: 0: if the user's function matches the golden board
 *          1: if the user's function does not match the golden board
 */
int test_update(int* golden_board, int* user_board, int numRows, int numCols, int iteration){
    updateBoard(user_board, numRows, numCols);

    int r, c;
    for(r = 0; r < numRows; r++){
        for(c = 0; c < numCols; c++){
            if(user_board[r*numCols+c] != golden_board[r*numCols+c]){
                printf("When testing updateBoard(), an error occured.\n");
                printf("\nThe error occured on iteration %d for the tested file.\n", iteration);
                printf("Mismatched (row, column): (%d, %d)\n", r, c);
                printf("Proper value: %d\n", golden_board[r*numCols+c]);
                printf("Your value: %d\n\n", user_board[r*numCols+c]);
                char in;
                scanf("Display full boards? (y/N): %c", &in);
                if(in == 'y' || in == 'Y'){
                    printf("User board\n");
                    print_board(user_board, numRows, numCols);
                    printf("Golden board\n");
                    print_board(golden_board, numRows, numCols);
                }
                return 1;
            }
        }
    }
    return 0;
}
 
/* Function to check whether the user's stayAlive function is working properly
 * @return: 0: if the user's function is correct
 *          1: if the user's function is not correct
 */
int test_alive(int* board, int numRows, int numCols, int expected, int iteration){
    int testee_res = aliveStable(board, numRows, numCols);
    if(!testee_res == expected){
        printf("When testing aliveStable(), an error occured\n");
        printf("\nThe error occured on iteration %d for the tested file\n", iteration);
        printf("Proper return value: %d\n", expected);
        printf("Your return value: %d\n\n", testee_res);
        return 1;
    }
    return 0;
}
/*
 * Helper function to printout a full board in Xs and .s
 */
void print_board(int* board, int boardRowSize, int boardColSize){
    for(int r = 0; r < boardRowSize; r++){
        for(int c = 0; c < boardColSize; c++){
            board[r * boardColSize + c] ? printf("X ") : printf(". ");
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]){

    // Pull all the file names and store into an linked list
    FILE* fp;
    fp = fopen("files.txt", "r");

    filename_t* top_ptr = (filename_t*) malloc(sizeof(filename_t));
    char buffer[50];
    if(fp){
        fscanf(fp, "%s", top_ptr->name);
        top_ptr->next = NULL;                             

        while(fscanf(fp, "%s", buffer) != EOF){
            filename_t* new_top = (filename_t*) malloc(sizeof(filename_t));
            strcpy(new_top->name, buffer);
            new_top->next = top_ptr;
            top_ptr = new_top;
            file_count++;
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
        int correct = 0;
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

                int* game_board = malloc(rows*cols*sizeof(int));
                int* golden_board = malloc(rows*cols*sizeof(int));
                int i, j, temp_b;
                for(i = 0; i < rows; i++){
                    for(j = 0; j < cols; j++){
                        fscanf(fp, "%d", &temp_b);
                        game_board[cols*i+j] = temp_b;
                        golden_board[cols*i+j] = temp_b;
                    }
                }
                // Iterate through and test the neighbors function
                strcpy(buffer, "./txt_boards/");
                strcat(buffer, filename);
                strcat(buffer, ".neighbors");
                FILE* neighbor_ptr;
                neighbor_ptr = fopen(buffer, "r");

                printf("Testing countLiveNeighbor() against %s\n", buffer);
                if(neighbor_ptr){
                    int r_in, c_in, proper_out;
                    while(fscanf(neighbor_ptr, "%d, %d, %d\n", &r_in, &c_in, &proper_out) != EOF){
                        int test_failure = test_neighbors(game_board, r_in, c_in, rows, cols, proper_out, buffer);
                        if(test_failure)
                            return 0; 
                    }
                    correct++;
                }else{
                    printf("Error opening %s.\nTerminating the program.", buffer);
                    return 1;
                }
                fclose(neighbor_ptr);

                // Iterate through and test the board as it changes
                strcpy(buffer, "./txt_boards/");
                strcat(buffer, filename);
                strcat(buffer, ".changes");
                FILE* changes_ptr;
                changes_ptr = fopen(buffer, "r");
                int iterations = 0;
                if(changes_ptr){
                    int index = 0;
                    char line_buffer[50];
                    char let = getc(changes_ptr);
                    while(let != EOF){
                        index = 0;
                        // Fill the buffer
                        while(let != '\n'){
                            line_buffer[index]=let;
                            let = getc(changes_ptr);
                            index++;
                        }
                        let = getc(changes_ptr);
                        line_buffer[index]='\0';
                        
                        int r, c, new_val, test_res, str_flag;
                        int scan_res = sscanf(line_buffer, "%d,%d,%d", &r, &c, &new_val);
                        if(scan_res != 3 && iterations != 0 && !(line_buffer[0] == 's')){
                            test_res = test_update(golden_board, game_board, rows, cols, iterations);
                            if(test_res == 1)
                                return 1;

                            str_flag = 1;
                            iterations++;
                        }else if(line_buffer[0] == 's'){
                            // Ensure that the board is stable
                            test_res = test_alive(golden_board, rows, cols, 1, iterations); 
                            if(test_res == 1)
                                return 1;
                        }else if(iterations==0){
                            printf("Testing aliveStable(), updateBoard() against %s\n", buffer);
                            iterations++;
                        }else{
                            if(str_flag){
                                // Check to ensure that the board is in an unstable state
                                test_res = test_alive(golden_board, rows, cols, 0, iterations); 
                                if(test_res == 1)
                                    return 1;
                                str_flag = 0;
                            }
                            golden_board[r*cols+c] = new_val;
                        }

                        // Clear the buffer
                        int h;
                        for(h = 0; h < 50; h++){
                            buffer[h] = '\0';
                        }
                    }


                }else{
                    printf("Error opening %s.\nTerminating the program.", buffer);
                    return 1;
                }
                printf("Test progress: %d/%d\n\n", correct, file_count);
                fclose(changes_ptr);

                free(game_board);
                free(golden_board);
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
