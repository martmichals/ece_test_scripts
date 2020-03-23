#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//user file(s)
#include "sudoku.h"

//initialize test valid functions
int test_row(const int val, const int i, const int sudoku[9][9], int gold_response);
int test_col(const int val, const int j, const int sudoku[9][9], int gold_response);
int test_sect(const int val, const int i, const int j, const int sudoku[9][9], int gold_response);


int file_count = 1;

/* check if is_val_in_row function is correct
 * if correct response, return 0
 * if incorrect, return 1
 */

int test_row(const int val, const int i, const int sudoku[9][9], int gold_response){
	int check = is_val_in_row(val, i, sudoku);
	if(check == gold_response)
	  return 0;
	
	
	printf("Error in is_val_in_row function\n");
	printf("Row: %d\n", i);
	printf("Column: %d\n\n", j);
	printf("Expected value: %d\n", gold_response);
	printf("Your value: %d\n", check);
	return 1;
}


/* check if is_col_in_row function is correct
 * if correct response, return 0
 * if incorrect, return 1
 */
int test_col(const int val, const int j, const int sudoku[9][9], int gold_response){
	int check = is_val_in_col(val, j, sudoku);
	if(check == gold_response)
	  return 0;
	
	
	printf("Error in is_val_in_col function\n");
	printf("Row: %d\n", i);
	printf("Column: %d\n\n", j);
	printf("Expected value: %d\n", gold_response);
	printf("Your value: %d\n", check);
	return 1;
}

/* check if is_col_in_row function is correct
 * if correct response, return 0
 * if incorrect, return 1
 */

int test_sect(const int val, const int sect, const int sudoku[9][9], int gold_response){
	int i = (sect/3)*3;
	int j = (sect%3)*3;

	int check = is_val_in_3x3_zone(val, i, j, sudoku);
	if(check == gold_response)
	  return 0;
	
	printf("Error in is_val_in_3x3_zone function\n");
	printf("Row: %d\n", i);
	printf("Column: %d\n\n", j);
	printf("Expected value: %d\n", gold_response);
	printf("Your value: %d\n", check);
	return 1;
}


int main(int argc, char const *argv[]){
	//pulling files
	filename = ("board%d", file_count);
	char buffer[50];
	char board_dir[] = "./test_images/";
	FILE* fp;
	strcpy(buffer, board_dir);
	strcat(buffer, filename);
	strcat(buffer, ".in");

	fp = fopen(buffer, "r");
	if(fp = NULL){
	  printf("Error opening input file.\nTerminating Program");
	  return 1;
	}

	// Iteration over each file
	int correct = 0;

	do{

		//get board content
		int sudoku[9][9];
		strcpy(buffer, board_dir);
		strcat(buffer, filename);
		strcat(buffer, ".in");

		fp = fopen(buffer, "r");
		
		//using mp7's parse function to create board
		parse_sudoku(buffer, sudoku);	
		
		// Iterate through valid check functions
		char* filename = top_ptr->name;
		char board_dir[] = "./test_images/";
		strcpy(buffer, board_dir);
		strcat(buffer, filename);
		strcat(buffer, ".series");
		
	
		//checking valid row function	
		FILE* row_ptr;
		row_ptr = fopen(buffer, "r");
		

		printf("Testing is_val_in_row against %s\n", buffer);
		if(row_ptr){
			char garbage[];
			int val, row, proper_out;
			//while(fscanf(row_ptr, "%s", garbage)
			  //continue;
			while(fscanf(row_ptr, "%d, %d, %d\n", &row, &val, &proper_out) != EOF){
			  int row_check = test_row(val, row, sudoku, proper_out);
			  if(row_check)
			  return 0;
			}


		}else{
		  printf("Error opening %s.\nTerminating Program.", buffer);
		  return 1;
		}
		
		
		//checking valid column function
		FILE* col_ptr;
		col_ptr = row_ptr;
		
		if(col_ptr){i
			char garbage[];
			int val, col, proper_out;
			//while(fscanf(col_ptr, "%s", garbage)
			 // continue;
			while(fscanf(col_ptr, "%d, %d, %d\n", &col, &val, &proper_out) != EOF){
			int col_check = test_col(val, col, sudoku, proper_out);
			if(col_check)
			  return 0;
			}


		}else{
		  printf("Error opening %s.\nTerminating Program.", buffer);
		  return 1;
		}
	

		//checking valid sector function
		FILE* sect_ptr;
		sect_ptr = col_ptr;
		
		if(sect_ptr){
			char garbage[];
			int val, sect, proper_out;
		/*	while(fscanf(sect_ptr, "%s", garbage)
			  continue;
			
			not a valid way to skip string text, need to figure different way
		 */
			while(fscanf(sect_ptr, "%d, %d, %d\n", &sect, &val, &proper_out) != EOF){
			int sect_check; test_sect(val, sect, sudoku, proper_out);
			if(sect_check)
			  return 0;
			}


		}else{
		  printf("Error opening %s.\nTerminating Program.", buffer);
		  return 1;
		}
		correct++
		file_count++;
		
	}while(fp != NULL);
}
	return 0;
}		
